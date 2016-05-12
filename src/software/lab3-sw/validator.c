/*
 * Switch ON validator,after main has completed sending the packets, this  * connects to the vga_led device and extracts all the information about t * he current status of the RAM's,based on which it extracts the packet fr * om each RAM. Now it also locally seeds itself with the encoded packet's * seed and then matches the information one by one till EOP((End of packe * t), at which stage it resets it's seed and waits for another packet.
 *
 */
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
#include <math.h>
#include "packetgen.h"
int vga_led_fd;
int received[VGA_LED_DIGITS], packets[VGA_LED_DIGITS];

int main()
{
    vga_led_arg_t vla;
    int i,j,k,total_packets = 0,transferred_data=0;
    static const char filename[] = "/dev/vga_led";
    printf(" Userspace Validation of sent data \n");
    if ( (vga_led_fd = open(filename, O_RDWR)) == -1) {
        fprintf(stderr, "could not open %s\n", filename);
        return -1;
    }
    for(i=0; i<VGA_LED_DIGITS; i++){
        received[i] = 0;
        packets[i] = 0;
    }
    // Output Ram's count
    for(i=0; i<VGA_LED_DIGITS; i++){
        vla.digit = 12+i;
        if (ioctl(vga_led_fd, VGA_LED_READ_DIGIT, &vla)) {
            perror("ioctl(VGA_LED_READ_DIGIT) failed");
            return;
        }
        received[i] = vla.segments;
        printf("RAM %i (32 Bits Transferred,includes all 4) : %i\n", i, received[i]);
        transferred_data = transferred_data + received[i];
    }
    printf("Transferred Data (Bytes) : %i\n",transferred_data*4); 
    for(i=0; i<VGA_LED_DIGITS; i++){
        vla.digit = 8+i;
        if (ioctl(vga_led_fd, VGA_LED_READ_DIGIT, &vla)) {
            perror("ioctl(VGA_LED_READ_DIGIT) failed");
            return;
        }
    }
    for(i = 0; i<VGA_LED_DIGITS; i++){
        // Start extracting values from the Output Rams
        printf("Validating from RAM: %i\n", i);
        vla.digit = i;
        for(j=0; j<received[i]; j++){
            // Extract the values from the rams. 
            if (ioctl(vga_led_fd, VGA_LED_READ_DIGIT, &vla)) {
                perror("ioctl(VGA_LED_READ_DIGIT) failed");
                return;
            }
            if(vla.segments == 0){
                printf("Received 0");
                continue;
            }
            unsigned int seedMask = 65280; // Extract the middle bits
            int length = vla.segments;
            int seed = length;
            int dport = seed;
            length = length>>16;
            seed = ((seed & seedMask)>>8); // Extracts the seed from packet
            dport = dport%4;
            if(dport!=i){
                printf("Invalid RAM location and dport from packet header\n");
                exit(1);
            }
            srand(seed);
            // Do some error handling.
            for(k=1; k<length; k++){
                if (ioctl(vga_led_fd, VGA_LED_READ_DIGIT, &vla)) {
                    perror("ioctl(VGA_LED_READ_DIGIT) failed");
                    return;
                }
                if(k<length-1){
                    int a = rand() + 1;
                    if(vla.segments != a){
                        printf("Packet value does not match: %i, %i\n", a, vla.segments);
                        exit(1);
                    }
                } else if(k == length-1 && vla.segments != 0){
                    printf("Length of packet reached but 0 not received.\n");
                    exit(1);
                }
                j++;                
            }
        packets[i]++;
        total_packets++; // Increment the total packet sent counter.
        }
    }
    printf("All RAM's have passed Validation!! \n");
    printf("Total Packets Sent : %i\n", total_packets);
    for(i = 0; i < 4; i++){
        printf("Output RAM: %i Packet Count: %i\n", i, packets[i]);
    }
    vla.digit = 7;
    if (ioctl(vga_led_fd, VGA_LED_READ_DIGIT, &vla)) {
        perror("ioctl(VGA_LED_READ_DIGIT) failed");
        return;
    }
    int num_clock_cycles = 0; // Number of clock cycles it took in total
    num_clock_cycles = vla.segments;
    printf("Number of cycles required for transfer: %i\n", num_clock_cycles);
    float var = 20E-9; // Assuming FPGA runs on 50 MHZ clock.
    printf("Speed through the Switch is:%f (in Mbits/s) \n",(transferred_data*4*8)/(var*1024*1024*num_clock_cycles));
    return 0;
}

