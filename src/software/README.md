# Packet Generator
----

### Makefile
List all your dependencies on the Makefile and add proper directives for 
generating the executables.

### Compile
All Targets have their own executables. The name of the executable is same as 
directive
For Packet Generator:
        make packet_gen  generates executable packet_gen.


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

Software related code needs to be here. This will include the packet generator 
and the validator, mostly!


