#include <string.h>
#include <stdlib.h>

char *concat(char *s1, char *s2){
        char *output = malloc(strlen(s1)+strlen(s2)+1); //1 for zero terminator.
        if (output==NULL){
                printf("MALLOC FALIED FOR %s and %s",s1,s2);
                exit(-1);
        }
        strcpy(output,s1);
        strcat(output,s2);
        return output;
}
