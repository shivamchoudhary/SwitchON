# Packet Generator
----

### Makefile
List all your dependencies on the Makefile and add proper directives for 
generating the executables. Read the comments in the makefile to understand more.


### Compile
## To compile:
        Type make. It will generate the executable. Run it by ./main 

All Targets have their own executables. The name of the executable is same as 
directive. Also we compile with -Wall so all warnings will be treated as errors.

**Warning: If you don't list your dependencies properly it might so occur that
the executables will not be generated in proper order.


The main executable is main.o which is the entry point to the code.


To illustrate what we aim to solve,consider the following scenario.

|Buffer         | Location 0    | Location 1    | Location 2        |
|-------        | ------------- |:-------------:| -----:|
|Input 1        | 2             | 1             |   1   |
|Input 2        | 1             | 0             |   2   |
|Input 3        | 2             | 2             |   0   |

Assumptions:
1. We have a 3*3 cross bar switch
2. We have 3 input buffers which can store 3 packets
3. Packets are not exactly IP packets but simple bits of the type 10000011
   (8 Bits each) and the last two bits denote which output port it has to go to.
4. Once generated the scheduling algorithm would output the matrix in such a way
   that throughput is maximized.
 
Where Input(i) denotes the input queue. So in the above scenario it can be seen

So for iteration 1 the scheduling algorithm should output:- 

|Buffer         | Location 0    | Location 1    | Location 2 |
|-------        | ------------- |:-------------:| -----:|
|Input 1        | 2             | 1             |   1   |
|Input 2        | 1             | 2             |   2   |
|Input 3        | 0             | 2             |   0   |

For iteration  2 the scheduling algorithm should output:-

|Buffer          | Location 1    | Location 2 |
|-------         |:-------------:| -----:|
|Input 1         | 1             |   1   |
|Input 2         | 2             |   2   |
|Input 3         | 0             |   2   |

And finally we need two clock cycles for the last iteration as there is no better
way to schedule them. 

##Links 
[This](http://www.cs.columbia.edu/~hgs/research/projects/newudpl/) is the link 
for the proxy emulator which can change the packet contents. We will be using 
this as a reference for the project.

## Files
Convention:
Include the files with  appropriate header files. Discuss if we really need to 
include the file.

List the use of your files here:-

1) Makefile: Contains directives to compile all the executables. Generates a
single output main which serves as entry point.

2) packetgen.c : To generate random packets with (OPT:specified headers)
        packetgen.h: Contains the header files for the same.
