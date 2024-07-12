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
        // if(execlp("/usr/bin/objdump","objdump","-t",binaryName,(char*)NULL) ==-1){//replace objdump for now and use nm instead
        if(execlp("/usr/bin/nm","nm", binaryName,(char*)NULL) ==-1){
            printf("execlp error %s\n", strerror(errno));
        }
        exit(0);
        
    }else{
        close(fd[1]);
        // char msg[1000];//not enough characters...
        int maxSize=5000;
        char * msg = (char*)malloc(maxSize * sizeof(char));
        int n = 10+1; //number of items in array
        int i=0;
        char **funcList = (char**)malloc((n)*sizeof(char*));
        char ** returnList = (char**)malloc((n)*sizeof(char*));

        for(i=0;i<n;i++){
            funcList[i] = (char*)malloc(50*sizeof(char));
           
        }


        for(i=0;i<n;i++){
            returnList[i] = (char*)malloc(50*sizeof(char));
           
        }

        //Parent waits for all the child processes 
        while ((wpid = wait(&status)) > 0); 
        printf("Waited\n");
        //Read from child
        nbytes = read(fd[0], msg, maxSize);
        printf("This is parent: %s\n", binaryName);

        //open text file to read functions
        readFileToArray("unsafe_functions.txt", funcList);
        // for(i=0;i<n;i++){
        //     printf("%s\n", funcList[i]);
        // }

        
        // if(msg!=NULL){
        //     printf("len of msg: %ld\n", strlen(msg));
        // }else{
        //     printf("msg empty\n");
        // }


        //Add wordsearch
        if(msg!=NULL){
            strMatch(funcList, n, msg, returnList );
        }else{
            printf("strmatch failed\n");
        }
        for(i=0;i<n;i++){
            if(strlen(returnList[i])>0){
                printf("Binary contains unsafe function: %s\n", returnList[i]);
            }
            
        }
        

        for(i=0;i<n;i++){
            free(returnList[i]);
        }
        free(returnList);//added back, issue was funcList incorrectly malloced



        for(i=0;i<n;i++){
            free(funcList[i]);
        }
        free(funcList);//added back, issue was funcList incorrectly malloced
        
        free(msg);

       

        printf("freed\n");
    }
}