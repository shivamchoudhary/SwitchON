/*
 * Main program that communicates with the led_vga device driver
 * primarily through ioctls. Generates a random char packet array and sends it
 *
 * SwitchON 
 * Columbia University
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <fcntl.h>
#include "packetgen.h"
#include "vga_led.h"

void write_segments(int );
static const char filename[] = "/dev/vga_led";

vga_led_arg_t vla;
int vga_led_fd;
int main(){
        
        // Open the vga_led fd.
        if ((vga_led_fd = open(filename,O_RDWR))==-1){
                fprintf(stderr,"Could not open device:%s\n",filename);
                return -1; //Device not open exit.
        }
        int i=0;
        for (i=0;i<NUM_PACKETS;i++){
                char packet[4];
                mkpkt(packet); //newpkt generated send to hardware.
                int value;
                //packet[3] and packet[2] : Length of the packet.
                //packet[1] : seed for the data.
                //packet[0] : dport.
                value  = (packet[3]<<24)|(packet[2]<<16)|(packet[1]<<8)                 |(packet[0]);
                printf("Packet: %i\n",value);
                write_segments(value); 
        }
}
// Takes the segments and then writes to the ioctl registers.
void write_segments(int segs){
        vga_led_arg_t vla;
        int i;
        for (i = 0 ; i < VGA_LED_DIGITS; i++) {
                vla.digit = i; //address
                vla.segments = segs; //data on the vla
                if (ioctl(vga_led_fd, VGA_LED_WRITE_DIGIT, &vla)) {
                        perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
                        return;
                        }    
        }
}

