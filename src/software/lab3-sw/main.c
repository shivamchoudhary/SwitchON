/*
 * Userspace program that communicates with the led_vga device driver
 * primarily through ioctls
 * Based on Stephen Edwards's Code.
 * Specific Words(see packetgen.h) reserved for RAM/Scheduler control.
 * Architecuture of the Switch
        |Address|       |Status|
            15          write_enable // Kicks the Scheduler into motion.
            14          read_enable //  Kicks the output RAMS.
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
#include "packetgen.h"

int vga_led_fd;
int sent[VGA_LED_DIGITS], received[VGA_LED_DIGITS];

int main()
{
    vga_led_arg_t vla;
    int i;
    time_t t; // Use the system time to seed the pseudo random generator
    srand((unsigned) time(&t));
    static const char filename[] = "/dev/vga_led";

    printf("Switch ON Packet Generator started\n");
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
        write_segments(vga_led_fd, input);
    }
    printf("Done Sending Packets, terminating\n");
    for(i=1; i<NUM_PACKETS; i++){
        vla.digit = 12+i;
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

