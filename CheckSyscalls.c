#include "commonHeaders.h"
#include "modules.h"
void checkSyscalls(char *binaryName){
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
        printf("child exe\n");
        if(dup2(fd[1], fileno(stdout))==-1){//stdout redirect to fd[1]
            perror("checkSyscalls(): dup2 failed for stdout\n");
        }    
        close(fd[1]);
        if(execlp("/usr/bin/objdump","objdump","-d",binaryName,(char*)NULL) ==-1){
            printf("execlp error %s\n", strerror(errno));
        }
        exit(0);
        
    }else{
        close(fd[1]);
        char msg[1000];//not enough characters...
        int n = 10; //number of items in array
        int i=0;
        char **funcList = (char**)malloc((n+1)*sizeof(char*));

        for(i=0;i<n;i++){
            funcList[i] = (char*)malloc(50*sizeof(char));
        }

        //Parent waits for all the child processes 
        while ((wpid = wait(&status)) > 0); 
        printf("Waited\n");
        //Read from child
        nbytes = read(fd[0],msg,sizeof(msg));
        printf("This is parent: %s string: %s\n", binaryName, msg);

        //open text file to read functions
        readFileToArray("unsafe_functions.txt", funcList);
        for(i=0;i<n;i++){
            printf("%s\n", funcList[i]);
        }
        for(i=0;i<n;i++){
            free(funcList[i]);
        }
        free(funcList);//added back, issue was funcList incorrectly malloced
        printf("freed\n");
    }
}