/*
 * Userspace program that generates packets with random contents 
 * Headers are defined in packetgen.h 
 * Define the function prototypes in the packetgen.h headers
 */

#include <stdlib.h>
#include "packetgen.h"
#include "vga_led.h"
#include <stdio.h>

void mkpkt(char input[4]){
        srand((rand()));
        input[0] = rand()%DPORT_BITS;  // LSB 8 bits destination port.
        input[1] = rand()%SEED_BITS;  // Seed for the data. 
        input[2] = rand()%250+5; // Length of the packet.
        input[3] = rand()%250+5; // Length of packet  MSB
}
void write_segments(static const char filename[], int segs[4])
{
    vga_led_arg_t vla;
    int i;
    for (i = 1 ; i < NUM_RAMS; i++) {
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
        input[i] = rand() + 1;
    }
    return input;
}


