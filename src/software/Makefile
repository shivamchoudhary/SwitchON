
#Add dependencies for packet_generator.
packet_gen: packet_gen.c packet_gen.h
	gcc -Wall packet_gen.c -o packet_gen

.PHONY: clean

clean:
	rm -f *.0 core main
.PHONY: all
all: clean main
