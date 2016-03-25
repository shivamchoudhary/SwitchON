# Use gcc for compilation
CC = gcc

# Include extra directories
INCLUDES = 

# Compilation Options:
# -g for debugging -Wall enables all warnings
CFLAGS = -g -Wall $(INCLUDES)

# Linking Oprions:
# -g for debugging info
LDFLAGS = -g

#List of Libraries which need to be linked in LDLIBS
LDLIBS = 

# Specify Targets in a recursive way.
# We rely on make's implicit rules:
# 	$(CC) $(LDFLGAGS) <all-dependent-.o-files> $(LDLIBS)

# Main is the main target that is compiled,it contains references to other
# functions.

# The philosophy is pretty simple main depends on everything so include all the
# *.o files in main,now other files might have internal dependencies like packet_gen 
# depends on common hence it is compiled together.
#

main: main.o packetgen.o common.o  

main.o: main.c packetgen.h

packet_gen.o: packetgen.c packetgen.h common.h

common.o:common.c common.h

.PHONY: clean
clean:
	rm -f *.o a.out main core packet_gen common executable
.PHONY: all
all: clean packet_gen
