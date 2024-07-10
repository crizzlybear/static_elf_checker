#include "commonHeaders.h"
#include "modules.h"
void checkStackProtections(char * binaryName){
    char mycmd[256];
    snprintf(mycmd,sizeof(mycmd),"%s %s", "ls", binaryName);
    printf("%s\n", mycmd);//or execv("/path/to/file-cmd", args);
    system(mycmd);
   
}