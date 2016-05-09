/*
 * Userspace program that generates packets with random contents 
 * Headers are defined in packetgen.h 
 * Define the function prototypes in the packetgen.h headers
 */

#include <stdlib.h>
#include "packetgen.h"
#include "vga_led.h"
#include <stdio.h>

char* mkpkt(){
        char* input = (char *) malloc(4);
        input[0] = rand()%DPORT_BITS;  // LSB 8 bits destination port.
        input[1] = rand()%SEED_BITS;  // Seed for the data. 
        input[2] = rand()%250+5; // Length of the packet.
        input[3] = 0; // Length of packet  MSB
        return input;
}
void write_segments(int vga_led_fd, int* packet, int sport, int len)
{
    vga_led_arg_t vla;
    int i;
    vla.digit = sport;
    for (i = 0 ; i < len; i++) {
        vla.segments = packet[i];
        if (ioctl(vga_led_fd, VGA_LED_WRITE_DIGIT, &vla)) {
            perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
            return;
        }
        printf("%i ", packet[i]);
    }
    printf("\n");
}
int* generate(char packet_info[4]){
    int i = 0;
    int len = (int) packet_info[2];
    int* input = (int *) malloc(len);
    input[0] = (packet_info[3]<<24)|(packet_info[2]<<16)|
                (packet_info[1]<<8)|(packet_info[0]);
    srand((unsigned)(packet_info[1]));
    for (i=1; i < len-1; i++){
        input[i] = rand() + 1;
    }
    input[len-1] = 0;
    return input;
}
