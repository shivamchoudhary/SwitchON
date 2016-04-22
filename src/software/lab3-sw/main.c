/*
 * Main program that communicates with the led_vga device driver
 * primarily through ioctls. Generates a random char packet array and sends it
 *
 * SwitchON Team
 * Columbia University
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <fcntl.h>
#include "packetgen.h"
#include "vga_led.h"
#define TOHEX(x) (x > 9 ? (x - 10 + 'A') : (x + '0'));

void write_segments(char segs[4]);
static const char filename[] = "/dev/vga_led";
vga_led_arg_t vla;
int vga_led_fd;
int main(){
        
        // Open the vga_led fd.
        /*if (open(filename,O_RDWR)==-1){*/
                /*fprintf(stderr,"Could not open device:%s\n",filename);*/
                /*return -1; //Device not open exit.*/
        /*}*/
        for (int i=0;i<NUM_PACKETS;i++){
                char packet[4];
                mkpkt(packet); //newpkt generated send to hardware.
                write_segments(packet); 
        }
}

void write_segments(char segs[4]){
        vga_led_arg_t vla;
        int i;
        for (i = 0 ; i < VGA_LED_DIGITS; i++) {
                vla.digit = i; //address
                vla.segments = segs[i]; //data
                printf("segments: %u digits: %u\n",vla.segments,vla.digit);
                /*if (ioctl(vga_led_fd, VGA_LED_WRITE_DIGIT, &vla)) {*/
                        /*perror("ioctl(VGA_LED_WRITE_DIGIT) failed");*/
                        /*return;*/
                        /*}       */
        }
}

