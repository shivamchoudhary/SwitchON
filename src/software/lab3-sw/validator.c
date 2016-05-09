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
int received[VGA_LED_DIGITS], packets[VGA_LED_DIGITS];

/* Write the contents of the array to the display */
int main()
{
    vga_led_arg_t vla;
    int i,j,k,total_packets = 0;
    static const char filename[] = "/dev/vga_led";
    printf(" Start Userspace Validation\n");
    if ( (vga_led_fd = open(filename, O_RDWR)) == -1) {
        fprintf(stderr, "could not open %s\n", filename);
        return -1;
    }
    for(i=0; i<VGA_LED_DIGITS; i++){
        received[i] = 0;
        packets[i] = 0;
    }
    // Output Ram's count
    for(i=1; i<VGA_LED_DIGITS; i++){
        vla.digit = 12+i;
        if (ioctl(vga_led_fd, VGA_LED_READ_DIGIT, &vla)) {
            perror("ioctl(VGA_LED_READ_DIGIT) failed");
            return;
        }
        received[i] = vla.segments;
        printf("RAM%i COUNT: %i\n", i, received[i]);
        
    }
    for(i = 1; i<VGA_LED_DIGITS; i++){
        // Start extracting values from the Output Rams
        vla.digit = i;
        for(j=0; j<received[i]; j++){
            // Extract the values from the rams. 
            if (ioctl(vga_led_fd, VGA_LED_READ_DIGIT, &vla)) {
                perror("ioctl(VGA_LED_READ_DIGIT) failed");
                return;
            }
//            if(vla.segments == 0)
//                continue;
            unsigned int seedMask = 65280;
            int length = vla.segments;
            int seed = length;
            int dport = seed;
            length = length>>16;
            seed = ((seed & seedMask)>>8);
            dport = dport%4;
            if(!(dport==i || dport==0 && i==2)){
                printf("Invalid RAM location and dport from packet header\n");
                exit(1);
            }
            srand(seed);
            for(k=1; k<length; k++){
                if (ioctl(vga_led_fd, VGA_LED_READ_DIGIT, &vla)) {
                    perror("ioctl(VGA_LED_READ_DIGIT) failed");
                    return;
                }
                if(k<length-1){
                    int a = rand() + 1;
                    if(vla.segments != a){
                        printf("Packet value does not match: %i, %i\n", a, vla.segments);
                        exit(1);
                    }
                } else if(k == length-1 && vla.segments != 0){
                    printf("Length of packet reached but 0 not received.\n");
                    exit(1);
                }
                j++;                
            }
        packets[i]++;
        total_packets++;
        }
    }
    printf("Total Packets: %i\n", total_packets);
    printf("Individual ram packets:\n");
    for(i = 1; i < 4; i++)
        printf("RAM %i Packet count: %i\n", i, packets[i]);
    vla.digit = 0;
    if (ioctl(vga_led_fd, VGA_LED_READ_DIGIT, &vla)) {
        perror("ioctl(VGA_LED_READ_DIGIT) failed");
        return;
    }
    printf("Number of cycles required for transfer: %i", vla.segments);
    return 0;
}

