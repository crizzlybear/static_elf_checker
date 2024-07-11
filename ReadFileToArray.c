#include "commonHeaders.h"
#include "modules.h"
void readFileToArray(char *filename, char **retArr){
    int i=0;
    char buffer[50];
    FILE *f = fopen(filename,"r");
    if(f==NULL){
        fprintf(stderr, "Couldn't open %s: %s\n", "unsafe_functions.txt", strerror(errno));
        exit(1);
    }
    
   while(fgets(buffer,50,f)!=NULL){
        free(retArr[i]);
        retArr[i] = strndup(buffer,50);//copy string to buffer
        i++;
    }
    fclose(f);
}