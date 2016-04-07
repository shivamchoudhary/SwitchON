#include <stdlib.h>
#include <time.h>
#include "packetgen.h"
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

void write_packet(const unsigned char *segs, int length, int src_port)
{
    vga_led_arg_t vla;
    int i;
    for(i=0; i<length; i++){
        vla.digit = src_port;
        vla.segments = segs[i];
        printf("%i ", segs[i]);
//        if (ioctl(vga_led_fd, VGA_LED_WRITE_DIGIT, &vla)) {
        if(0){
            perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
            return;
        }
    }
}

char* generate_packet(int length, char seed, char port){
    char* packet = (char *) malloc(length);
    int i;
    packet[0] = seed;
    packet[1] = port;
    srand((unsigned) seed);
    for(i=2; i<length; i++){
        packet[i] = rand()%256;
    }
    return packet;
}

int main()
{
    time_t t;
    srand((unsigned) time(&t));
    int i;
    static const char filename[] = "/dev/vga_led";

    printf("VGA LED Userspace program started\n");
    if ( (vga_led_fd = open(filename, O_RDWR)) == -1) {
        fprintf(stderr, "could not open %s\n", filename);
        return -1;
    }

    static char *input;
    for (i = 0 ; i < NUM_PACKETS ; i++) {
        int length = rand()%96 + 5;
        char seed = rand()%256;
        char dest_port = rand()%4;
        char src_port = rand()%4;
        input = generate_packet(length, seed, dest_port);
        printf("New packet of length: %i, at port %i\n", length, src_port);
        write_packet(input, length, src_port);
        printf("\n");
        usleep(400000);
    }
    printf("VGA LED Userspace program terminating\n");
    return 0;
}
