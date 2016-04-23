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

int read_size(){
    int vga_led_fd;
    vga_led_arg_t vla;
    int i;
    static const char filename[] = "/dev/vga_led";

    printf("VGA LED Userspace program started\n");

    if ( (vga_led_fd = open(filename, O_RDWR)) == -1) {
        fprintf(stderr, "could not open %s\n", filename);
        return -1;
    }

    for(i=1; i<7; i++){
        vla.digit = 14-i;
        if (ioctl(vga_led_fd, VGA_LED_READ_DIGIT, &vla)) {
            perror("ioctl(vga_led_read_digit) failed");
            return;
        }
        printf("%i\n", vla.segments);
    }
    return 0;
}

int main(){
    return read_size();
}
