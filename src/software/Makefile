#Add dependencies for packet_generator.
CC=gcc
CFLAGS=-Wall
#Define Targets here

packet_gen: packet_gen.c packet_gen.h config.h
	$(CC) $(CFLAGS) packet_gen.c -o packet_gen

.PHONY: clean

clean:
	rm -f *.0 core main
.PHONY: all

all: clean main
