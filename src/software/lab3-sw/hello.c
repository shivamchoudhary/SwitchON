/*
 * Userspace program that communicates with the led_vga device driver
 * primarily through ioctls
 *
 * Stephen A. Edwards
 * Columbia University
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
int vga_led_fd;

/* Read and print the segment values */
void print_segment_info() {
  vga_led_arg_t vla;
  int i;

  for (i = 0 ; i < VGA_LED_DIGITS ; i++) {
    vla.digit = i;
    if (ioctl(vga_led_fd, VGA_LED_READ_DIGIT, &vla)) {
      perror("ioctl(VGA_LED_READ_DIGIT) failed");
      return;
    }
    printf("%02x ", vla.segments);
  }
  printf("\n");
}

/* Write the contents of the array to the display */
void write_segments(const unsigned char segs[24])
{
  vga_led_arg_t vla;
  int i;
  for (i = 0 ; i < VGA_LED_DIGITS ; i++) {
    vla.digit = i;
    vla.segments = segs[i];
    if (ioctl(vga_led_fd, VGA_LED_WRITE_DIGIT, &vla)) {
      perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
      return;
    }
  }
}

char* generate(){
	int i = 0;
	static char input[4];
        time_t t;
        srand((unsigned) time(&t));
        for (i=0; i<4; i++){
                input[i] = rand()%4;
		printf("%i ",input[i]);
        }
	printf("\n");
        return input;
}

int main()
{
  vga_led_arg_t vla;
  int i;
  static const char filename[] = "/dev/vga_led";

  static unsigned char message[8] = { 0x39, 0x6D, 0x79, 0x79,
				      0x66, 0x7F, 0x66, 0x3F };

  printf("VGA LED Userspace program started\n");

  if ( (vga_led_fd = open(filename, O_RDWR)) == -1) {
    fprintf(stderr, "could not open %s\n", filename);
    return -1;
  }

  printf("initial state: ");
  print_segment_info();

//  write_segments(generate());
  static char *input;
  input = generate();
  write_segments(input);

  printf("current state: ");
  print_segment_info();

  for (i = 0 ; i < 32 ; i++) {
   input = generate();
//    unsigned char c0 = *(input);
//    memmove(input, input+1, VGA_LED_DIGITS - 1);
//    input[VGA_LED_DIGITS - 1] = c0;
    write_segments(input);
    usleep(1600000);}
    printf("VGA LED Userspace program terminating\n");
  return 0;
}

