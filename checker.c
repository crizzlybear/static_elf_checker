#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>

void getFileType(char * binaryName){
    char mycmd[256];
    snprintf(mycmd,sizeof(mycmd),"%s %s", "file", binaryName);
    printf("%s\n", mycmd);
    system(mycmd);
   
}

void checkStackProtections(char * binaryName){
    char mycmd[256];
    snprintf(mycmd,sizeof(mycmd),"%s %s", "ls", binaryName);
    printf("%s\n", mycmd);//or execv("/path/to/file-cmd", args);
    system(mycmd);
   
}

void checkSyscalls(char *binaryName){
    pid_t p;
    int fd[2];
    int nbytes;
    pipe(fd);

    p = fork();
    if(p<0){
        perror("fork failed\n");
        exit(1);
    }else if(p==0){
        int parentPid;
        close(fd[1]);
        nbytes = read(fd[0],&parentPid,sizeof(pid_t));
        printf("This is child %s parent's pid=%d\n", binaryName, parentPid);
        exit(0);
        
    }else{
        int x =100;
        close(fd[0]);
        write(fd[1],&p,sizeof(p));
        printf("This is parent %s pid=%d\n", binaryName,p);
        //wait for child to terminate
        //this might be the cause of the timing issue
    }
}
int main(int argc, char *argv[]){
    char *binaryName;
    int leaveMenu=0;
    char inputBuffer[2];
    int menuOption;
    

     if(!argv[1]){
        printf("Please enter file/binary like:\n\tchecker example.exe\n");
        exit(1);
    }
    binaryName = argv[1];
    while(leaveMenu==0){
        printf("\033[0;31m");//red
        printf("1.Get File type\n2.Check stack protections by running checksec\n3.Check unsafe syscalls\n");
        printf("\033[0m");//reset 
        printf("Menu option\n:");
        fflush(stdout);
        if(fgets(inputBuffer,2,stdin)!=NULL){
            menuOption = atoi(inputBuffer);
            fgets(inputBuffer,2,stdin);
        }
        printf("\033[0;31m");//red
        printf("Menu selected: %d\n", menuOption);
        printf("\033[0m");//reset
        switch(menuOption){
            case 1://1.Get File type
                getFileType(binaryName);
                break;
            case 2://2.Check stack protections by running checksec
                checkStackProtections(binaryName);
                break;
            case 3://3.Check unsafe syscalls
                checkSyscalls(binaryName);
                break;
            default:
                printf("Goodbye!\n");
                leaveMenu=1;
                break;
        }
    }

    
    
    
    return 0;
}