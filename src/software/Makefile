#Add dependencies for packet_generator.
CC=gcc
CFLAGS=-Wall
#Define Targets here

packet_gen: packet_gen.h
	$(CC) $(CFLAGS) packet_gen.c -o packet_gen

.PHONY: clean
clean:
	rm -f *.o core main packet_gen validator
	cd ../../output && rm *.pkt
.PHONY: all

all: clean main
