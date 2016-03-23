#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <time.h>
#include <string.h>
#include "packet_gen.h"
#include "common.h"

void makePacket(int srcip,int dstip,int srcport, int dstport){
        struct ipheader ipheader_t;
        ipheader_t.src = srcip;
        ipheader_t.dst = dstip;
        ipheader_t.srcport = srcport;
        ipheader_t.dstport = dstport;
}

int main(int argc, char *argv[]){
        
        time_t t;
        srand((unsigned) time(&t));
        for (int i=START_PORT; i<START_PORT+NUM_PACKETS; i++){
                char fname[100];
                sprintf(fname,"../../output/%d.pkt",i);
                FILE *fd;
                fd =fopen(fname,"w+");
                if (fd==NULL){
                        printf("Failed to open file %s",fname);
                }
                fprintf(fd,"TEST\n");
                binary(rand()%3);
        
        }
        return 0;
}
