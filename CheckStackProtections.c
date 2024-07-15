#include "commonHeaders.h"
#include "modules.h"
void checkStackProtections(char *binaryName){
    pid_t p;
    int fd[2];//for child to parent pipe

    int nbytes;
    int status = 0;
    pipe(fd);
     pid_t wpid;

    p = fork();
    if(p<0){
        perror("fork failed\n");
        exit(1);
    }else if(p==0){
        close(fd[0]);
        // printf("child exe\n");
        if(dup2(fd[1], fileno(stdout))==-1){//stdout redirect to fd[1]
            perror("checkSyscalls(): dup2 failed for stdout\n");
        }    
        close(fd[1]);
        if(execlp("./myChecksec.sh","./myChecksec.sh", binaryName,(char*)NULL) ==-1){
            printf("execlp error %s\n", strerror(errno));
        }
        exit(0);
        
    }else{
        close(fd[1]);
        int maxSize=5000;
        char * msg = (char*)malloc(maxSize * sizeof(char));
        int i=0;
    
        //Parent waits for all the child processes 
        while ((wpid = wait(&status)) > 0); 
        // printf("Waited\n");
        //Read from child
        nbytes = read(fd[0], msg, maxSize);
        // printf("This is parent: %s\n", binaryName);
        printf("%s\n", msg);
        free(msg);  
        // printf("freed\n");
    }
}