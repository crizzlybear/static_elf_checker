#include "commonHeaders.h"
#include "modules.h"
void getFileType(char *binaryName){
    pid_t p;
    int fd[2];
    int nbytes;
    int status = 0;
    pipe(fd);
     pid_t wpid;

    p = fork();
    if(p<0){
        perror("fork failed\n");
        exit(1);
    }else if(p==0){
        printf("child exe\n");
        
        if(execlp("/usr/bin/file", "file", binaryName,(char*)NULL) ==-1){
            printf("execlp error %s\n", strerror(errno));
        } 
        exit(0);
        
    }else{
        while ((wpid = wait(&status)) > 0); // the parent waits for all the child processes 
        printf("Waited\n");
    }
}