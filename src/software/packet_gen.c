#include "packet_gen.h"
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>

void makePacket(int srcip,int dstip,int srcport, int dstport){
        struct ipheader ipheader_t;
        ipheader_t.src = srcip;
        ipheader_t.dst = dstip;
        ipheader_t.srcport = srcport;
        ipheader_t.dstport = dstport;
}


int main(int argc, char *argv[]){
        return 0;
}
