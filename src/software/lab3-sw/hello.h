/*
 * hello headers: 
 * Contains various headers defining packet parameters.  
 * 
 * Team SwitchON
 * Columbia University
 */
#include <stdint.h>
#ifndef __HELLO_H__
#define __HELLO_H__

/*Packet parameters */
//Packet Structure (all length in bytes)
//      |Seed|LENGTH|LENGTH|DPORT|
//          1    1      1      1
// Destination port parameters
#define MIN_PKT_LENGTH 4
#define MIN_DPORT 1 // Minimum dst port that must be generated
#define DPORT_BITS 256 //8 Bytes
#define NUM_PACKETS 64 // Generate number of packets
#define SEED_BITS 256 // Keep the seed of 1 bytes
#define MIN_LEN 1

void mkpkt(char input[4]);
