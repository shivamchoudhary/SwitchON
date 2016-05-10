/*
 * Userspace program that communicates with the led_vga device driver
 * primarily through ioctls
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
//#include "packetgen.h"
int vga_led_fd;
int sent[VGA_LED_DIGITS], received[VGA_LED_DIGITS];

/* Write the contents of the array to the display */
void write_segments(int segs[4])
{
    vga_led_arg_t vla;
    int i;
    for (i = 0 ; i < 4; i++) {
        vla.digit = i;
        vla.segments = segs[i];
        if (ioctl(vga_led_fd, VGA_LED_WRITE_DIGIT, &vla)) {
            perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
            return;
        }
        printf("%i ", vla.segments);
        vla.segments = segs[i];
        if (ioctl(vga_led_fd, VGA_LED_WRITE_DIGIT, &vla)) {
            perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
            return;
        }
        printf("%i ", vla.segments);
        vla.segments = 0;
        if (ioctl(vga_led_fd, VGA_LED_WRITE_DIGIT, &vla)) {
            perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
            return;
        }
    }
    printf("\n");
}

int* generate(){
    int i = 0;
    static int input[VGA_LED_DIGITS];
    input[0] = 0;
    for (i=0; i<VGA_LED_DIGITS; i++){
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

    for (i = 0 ; i < 5 ; i++) {
        input = generate();
        write_segments(input);
    }

    printf("VGA LED Userspace program terminating\n");
    for(i=0; i<VGA_LED_DIGITS; i++){
        vla.digit = 8+i;
        if (ioctl(vga_led_fd, VGA_LED_READ_DIGIT, &vla)) {
            perror("ioctl(VGA_LED_READ_DIGIT) failed");
            return;
        }
        received[i] = vla.segments;
    }

    vla.digit = 15; // For starting the Scheduler
    vla.segments = 0;
    if (ioctl(vga_led_fd, VGA_LED_WRITE_DIGIT, &vla)) {
        perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
        return;
    }
    vla.digit = 14;
    vla.segments = 0;
    if (ioctl(vga_led_fd, VGA_LED_WRITE_DIGIT, &vla)) {
        perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
        return;
    }
    return 0;
}

