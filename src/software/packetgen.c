#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "packetgen.h"
#include "common.h"

int generate(){
        time_t t;
        srand((unsigned) time(&t));
	int i = 0;
        for (i=START_PORT; i<START_PORT+NUM_PACKETS; i++){
                printf("%i\n",rand()%255);
                
        }
        return 0;
}
