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

    printf("VGA LED Userspace program started\n");
    if ( (vga_led_fd = open(filename, O_RDWR)) == -1) {
        fprintf(stderr, "could not open %s\n", filename);
        return -1;
    }
    for(i=0; i<VGA_LED_DIGITS; i++){
        received[i] = 0;
    }	

    for(i=1; i<7; i++){
        vla.digit = 3+i;
        if (ioctl(vga_led_fd, VGA_LED_READ_DIGIT, &vla)) {
            perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
            return;
        }
        printf("READ COUNT:%i ", vla.segments);	
    }
    printf("\n");
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
    for(i=1; i<VGA_LED_DIGITS; i++){
        vla.digit = 9+i;
        if (ioctl(vga_led_fd, VGA_LED_READ_DIGIT, &vla)) {
            perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
            return;
        }
        printf("READ COUNT:%i ", vla.segments);	
    }
    printf("\n");
    int ram=1;
    unsigned mask;
    mask = (1<<2)-1;
    for(i = 1; i<VGA_LED_DIGITS; i++){
        for(j = 0; j<received[i]; j++){
            vla.digit = i;
            if (ioctl(vga_led_fd, VGA_LED_READ_DIGIT, &vla)) {
                perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
                return;
            }
            if (ram==1){
                printf("%u",vla.segments & mask);
            }
            else if (ram==2){
                printf("%u",vla.segments & mask);

            }
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
