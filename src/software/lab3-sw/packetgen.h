#ifndef __PACKETGEN_H__
#define __PACKETGEN_H__

#define MIN_PKT_LENGTH 4

#define NUM_PACKETS 64

typedef struct{
        char seed; /* The seed for the packet */
        int length; /* Length of the packet*/
        unsigned int dport; /* Destination port of the packet*/
        unsigned int sport; /* Source port of the packet */
}packet_t;


#endif
