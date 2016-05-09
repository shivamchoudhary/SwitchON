/*
 * packetgen headers: 
 * Contains various headers defining packet parameters.  
 * 
 * Team SwitchON
 * Columbia University
 */
#include <stdint.h>
#ifndef __PACKETGEN_H__
#define __PACKETGEN_H__

/*Packet parameters */

//Crossbar Architecture
/*
        -1 -|-|-|
        -2 -|-|-|
        -3 -|-|-|
            1 2 3
*/
//Packet Structure (all length in bytes)
//      |LENGTH|LENGTH|SEED|DPORT|
//        1      1      1      1
// Destination port parameters
#define MIN_DPORT 1 // Minimum dst port that must be generated
#define DPORT_BITS 256 //1 Byte
#define NUM_PACKETS 10 // Total Packets to be sent.
#define SEED_BITS 256 // Keep the seed of 1 byte
#define WRITE_ENABLE_SCHEDULER 15 // Write Enable the scheduler.
#define READ_ENABLE_SCHEDULER 14 // Read Enable the Ouput Rams. 
#define NUM_RAMS 4 // Define the number of RAMS.

typedef struct{
        unsigned char seed; /* The seed for the packet */
        uint16_t length; /* Length of the packet 16 bits */
        char dport; /* Destination port of the packet*/
}packet_t;
char* mkpkt();
#endif

void write_segments(int vga_led_fd, int* input, int sport, int len);
int * generate();
