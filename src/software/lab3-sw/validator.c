#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vga_led.h"
#include <sys/ioctl>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
int vga_led_fd;
int sent[VGA_LED_DIGITS], received[VGA_LED_DIGITS];

/* Write the contents of the array to the display */
int main()
{
    vga_led_arg_t vla;
    int i,j;
    static const char filename[] = "/dev/vga_led";
    printf(" Start Userspace Validation\n");
    if ( (vga_led_fd = open(filename, O_RDWR)) == -1) {
        fprintf(stderr, "could not open %s\n", filename);
        return -1;
    }
    for (i=0;i<VGA_LED_DIGITS;i++){
        received[i] = 0;
    }
    for (i=1;i<VGA_LED_DIGITS;i++){
        vla.digit = 10+i;
        if (ioctl(vga_led_fd,VGA_LED_READ_DIGIT,&vla)){
            perror("ioctl(VGA_LED_READ_DIGIT) failed");
            return -1;
        }
        received[i] = vla.segments;
        printf("%i\n",received[i]);
    }
    return 0;
}

