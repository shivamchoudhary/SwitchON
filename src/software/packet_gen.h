#define PACKET_LEN 8192
#define NUM_PACKETS 2
struct ipheader {
 unsigned short int chksum;
 unsigned int       src;
 unsigned int       dst;
 unsigned int       srcport;
 unsigned int       dstport;
};
