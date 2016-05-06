/*
 * Userspace program that generates packets with random contents 
 *
 * Headers are defined in packetgen.h 
 * Define the function prototypes in the packetgen.h headers
 * Ayush Donovan Shivam
 * Columbia University
 */

#include <stdlib.h>
#include "packetgen.h"

void mkpkt(char input[4]){
        srand((rand()));
        input[0] = rand()%DPORT_BITS;  // LSB 8 bits destination port.
        input[1] = rand()%SEED_BITS;  // Seed for the data. 
        input[2] = rand()%250-MIN_PKT_LENGTH; // Length of the packet.
        input[3] = rand()%250-MIN_PKT_LENGTH; // Length of packet  MSB
}
