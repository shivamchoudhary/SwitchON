#include <stdlib.h>
#include <time.h>
#include "packetgen.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vga_led.h"
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int vga_led_fd;

void write_packet(const unsigned char *segs, int length, int src_port)
{
    vga_led_arg_t vla;
    int i;
    for(i=0; i<length; i++){
        vla.digit = src_port;
        vla.segments = segs[i];
        printf("%i ", segs[i]);
        if(0){
            perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
            return;
        }
    }
}

// Send the pointer to the packet.
void mkpkt(packet_t *pkt){
        /*time_t t;*/
        srand((rand()));
        pkt->seed =rand()%SEED_BITS;
        pkt->dport=rand()%DPORT_BITS;
        pkt->length = rand()%250- MIN_PKT_LENGTH;
}
int main()
{
    time_t t;
    srand((unsigned) time(&t));
    int i;
    static const char filename[] = "/dev/vga_led";
    printf("Packet Generator\n");
    printf("MIN_PKT_LENGTH:%i \n",MIN_PKT_LENGTH);
    for (i = 0 ; i < NUM_PACKETS ; i++) {
        // Define a new struct for packet.
        packet_t newpkt;
        mkpkt(&newpkt);
        printf("seed:%c,dport:%c,length:%c\n",newpkt.seed,newpkt.dport
                        ,newpkt.length);
    }
    printf("Packet Generation Complete!\n");
    return 0;
}
