#include "validator.h"
#include <pthread.h>
#include <semaphore.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

char* path = "../../output/"; 

void *run(void *port)
{
    DIR *dir;
    struct dirent *ent;
    char* dirPath = concatStrings(concatStrings(path, (char*)port), "/");
    if ((dir = opendir (dirPath)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            char* filePath = concatStrings(dirPath, ent->d_name); 
            printf("%s\n", filePath);
            readFileAndValidate(filePath);
        }
        closedir (dir);
    } 

}

int readFileAndValidate(char* fileName){
    FILE *fp;
    char* buff;

    if(fp = fopen(fileName, "r")){
        fscanf(fp, "%s", buff);
        printf("%s\n", buff);
        fclose(fp);
    }
}

char* concatStrings(char* s1, char* s2){
    char* s3 = (char *) malloc(1 + strlen(s1) + strlen(s2));
    strcpy(s3, s1);
    strcat(s3, s2);
    return s3;
}

void main(int argc, char *ports[])
{
    pthread_t threads[argc-1];
    int i;

    for(i=1; i<argc; i++){
        pthread_create(&threads[i], NULL, run, ports[i]);
    }

    for(i=1; i<argc; i++){
        pthread_join(threads[i], NULL);
    }
}
