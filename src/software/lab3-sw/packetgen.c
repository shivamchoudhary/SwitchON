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

// Send the pointer to the packet.
void mkpkt(char input[4]){
        srand((rand()));
        input[0] = rand()%DPORT_BITS;
        input[1] = rand()%SEED_BITS;
        input[2] = rand()%250-MIN_PKT_LENGTH;
        input[3] = rand()%250-MIN_PKT_LENGTH;
}
