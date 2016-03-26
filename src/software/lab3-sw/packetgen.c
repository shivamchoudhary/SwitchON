#include <stdlib.h>
#include <time.h>
#include "packetgen.h"

char[] generate(){
        time_t t;
        srand((unsigned) time(&t));
	int i = 0;
	char input[NUM_PACKETS];
        for (i=START_PORT; i<START_PORT+NUM_PACKETS; i++){
                input[i] = rand()%255;
        }
        return input;
}
