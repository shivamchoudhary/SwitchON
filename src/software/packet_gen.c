#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <time.h>
#include <string.h>
#include "packet_gen.h"
int main(int argc, char *argv[]){
        time_t t;
        srand((unsigned) time(&t));
        for (int i=START_PORT; i<START_PORT+NUM_PACKETS; i++){
                printf("%i\n",rand()%255);
                
        }
        return 0;
}

