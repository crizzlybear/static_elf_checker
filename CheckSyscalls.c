#include "commonHeaders.h"
#include "modules.h"
void checkSyscalls(char *binaryName){
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
        /*char msg[] = "Hello from child\n";
        close(fd[0]);
        write(fd[1],msg,sizeof(msg));
        printf("This is child %s \n", binaryName);*/

      
        printf("child exe\n");
        
        if(execlp("/usr/bin/objdump","objdump","-d",binaryName,(char*)NULL) ==-1){
            printf("execlp error %s\n", strerror(errno));
        }
        
        exit(0);
        
    }else{
        /*close(fd[1]);
        char * msg;
        nbytes = read(fd[0],msg,sizeof(char)*18);
        printf("This is parent %s string %s\n", binaryName,msg);*/
        //wait for child to terminate
        //this might be the cause of the timing issue
        int n = 10; //number of items in array
        int i=0;
        char **funcList = (char**)malloc((n+1)*sizeof(char));
        for(i=0;i<n;i++){
            funcList[i] = (char*)malloc(50*sizeof(char));
        }
        while ((wpid = wait(&status)) > 0); // the parent waits for all the child processes 
        printf("Waited\n");
        readFileToArray("unsafe_functions.txt", funcList);
        for(i=0;i<n;i++){
            printf("%s\n", funcList[i]);
            
        }
        for(i=0;i<n;i++){
            free(funcList[i]);
        }
        free(funcList);
        printf("freed\n");
    }
}