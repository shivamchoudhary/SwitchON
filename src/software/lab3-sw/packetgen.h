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
//      |Not Used|Seed|LENGTH|DPORT|
//          1        1    1      1
// Destination port parameters
#define MIN_PKT_LENGTH 4
#define MIN_DPORT 1 // Minimum dst port that must be generated
#define DPORT_BITS 256 //8 Bytes
#define NUM_PACKETS 64 // Generate number of packets
#define SEED_BITS 256 // Keep the seed of 1 bytes
#define MIN_LEN 1

typedef struct{
        unsigned char seed; /* The seed for the packet */
        uint16_t length; /* Length of the packet 16 bits */
        char dport; /* Destination port of the packet*/
}packet_t;
void mkpkt(char input[4]);


#endif

void write_packet(const unsigned char *, int length,int src_port);
char *generate_packet(int length,char seed,char port);
