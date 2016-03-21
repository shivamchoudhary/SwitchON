#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <time.h>
#include "packet_gen.h"

void makePacket(int srcip,int dstip,int srcport, int dstport){
        struct ipheader ipheader_t;
        ipheader_t.src = srcip;
        ipheader_t.dst = dstip;
        ipheader_t.srcport = srcport;
        ipheader_t.dstport = dstport;
}

int main(int argc, char *argv[]){
        for (int i=0;i<NUM_PACKETS;i++){
                printf("%d\n",rand()%65536);
        }
        return 0;
}
