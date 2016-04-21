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
        char seed; /* The seed for the packet */
        char length; /* Length of the packet*/
        char dport; /* Destination port of the packet*/
}packet_t;


#endif
