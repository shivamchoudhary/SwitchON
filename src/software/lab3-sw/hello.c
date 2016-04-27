/*
 * 
 * Userspace program that communicates with the led_vga device driver
 * primarily through ioctls
 * Heavily modified by 
 * Ayush Jain Donovan Chan and Shivam Choudhary
 * Stephen A. Edwards
 * Columbia University
 */

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
int sent[VGA_LED_DIGITS], received[VGA_LED_DIGITS];

/* Write the contents of the array to the display */
void write_segments(int segs[4])
{
    vga_led_arg_t vla;
    int i;
    for (i = 1 ; i < VGA_LED_DIGITS; i++) {
        vla.digit = i;
        vla.segments = segs[i];
        if (ioctl(vga_led_fd, VGA_LED_WRITE_DIGIT, &vla)) {
            perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
            return;
        }
        printf("%i ", vla.segments);
    }
    printf("\n");
}

int* generate(){
    int i = 0;
    static int input[VGA_LED_DIGITS];
    input[0] = 0;
    for (i=1; i<VGA_LED_DIGITS; i++){
   //     input[i] = 155;
        input[i] = rand() + 1;
    }
    return input;
}

int main()
{
    vga_led_arg_t vla;
    int i;
    time_t t;
    srand((unsigned) time(&t));
    static const char filename[] = "/dev/vga_led";

    printf(" Packet Generator started\n");
    if ( (vga_led_fd = open(filename, O_RDWR)) == -1) {
        fprintf(stderr, "could not open %s\n", filename);
        return -1;
    }

    for(i=0; i<VGA_LED_DIGITS; i++){
        sent[i] = 0;
        received[i] = 0;
    }

    static int *input;
    for (i = 0 ; i < 32 ; i++) {
        input = generate();
        write_segments(input);
        //    usleep(1600000);
    }

    printf("VGA LED Userspace program terminating\n");
    for(i=1; i<VGA_LED_DIGITS; i++){
        vla.digit = 12+i;
        if (ioctl(vga_led_fd, VGA_LED_READ_DIGIT, &vla)) {
            perror("ioctl(VGA_LED_READ_DIGIT) failed");
            return;
        }
        received[i] = vla.segments;
        printf("%i:%i\n", sent[i], received[i]);
    }
    return 0;
}

