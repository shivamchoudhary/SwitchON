#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vga_led.h"
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int vga_led_fd;
int received[VGA_LED_DIGITS];
int totalpackets; // Total packets recieved from Switch
int main(){
    vga_led_arg_t vla;
    int i, j;
    static const char filename[] = "/dev/vga_led";

    printf("Reading the RAMS\n");
    if ( (vga_led_fd = open(filename, O_RDWR)) == -1) {
        fprintf(stderr, "could not open %s\n", filename);
        return -1;
    }
    for(i=0; i<VGA_LED_DIGITS; i++){
        received[i] = 0;
    }
    // Read counts from Input and output RAM's	
    for(i=1; i<7; i++){
        vla.digit = 3+i; // In Buffer.sv we set the address from 4
        if (ioctl(vga_led_fd, VGA_LED_READ_DIGIT, &vla)) {
            perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
            return;
        }
        // Ram 1->3 input ram_rdaddress,Ram 1->3 input ram_wr address.
        printf("READ COUNT:%i ",vla.segments);
    }
    printf("\n");
    // Output Ram's count
    for(i=1; i<VGA_LED_DIGITS; i++){
        vla.digit = 12+i;
        if (ioctl(vga_led_fd, VGA_LED_READ_DIGIT, &vla)) {
            perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
            return;
        }
        received[i] = vla.segments;
        totalpackets = totalpackets+received[i];
        printf("%i\n", received[i]);
        
    }
    printf("Sum:%i\n",totalpackets);
    for(i=1; i<7; i++){
        vla.digit = 9+i;
        if (ioctl(vga_led_fd, VGA_LED_READ_DIGIT, &vla)) {
            perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
            return;
        }
        printf("RAM COUNT:%i ", vla.segments);	
    }
    printf("\n");
    int ram=1;
    unsigned mask;
    mask = (1<<2)-1;
    for(i = 1; i<VGA_LED_DIGITS; i++){
        // Start extracting values from the Output Rams
        for(j = 0; j<received[i]; j++){
            vla.digit = i;
            // Extract the values from the rams. 
            if (ioctl(vga_led_fd, VGA_LED_READ_DIGIT, &vla)) {
                perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
                return;
            }
            printf(" %i ",vla.segments);
            // It is supposed to get received[i] values.
            // Data from RAM1
            if (ram==1){
                printf("%u",vla.segments & mask);
            }
            // Data from RAM2
            else if (ram==2){
                printf("%u",vla.segments & mask);

            }
            // Data from RAM3
            else if (ram==3){
                printf("%u",vla.segments & mask);

            }
        }
        ram = ram+1;
        printf("\n");
    }

    for(i=1; i<VGA_LED_DIGITS; i++){
        vla.digit = 9+i;
        if (ioctl(vga_led_fd, VGA_LED_READ_DIGIT, &vla)) {
            perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
            return;
        }
        printf("READ COUNT:%i ", vla.segments);	
    }
    printf("\n");
    return 0;
}
