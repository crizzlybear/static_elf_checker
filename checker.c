#include "commonHeaders.h"
#include "modules.h"

int main(int argc, char *argv[]){
    char *binaryName;
    int leaveMenu=0;
    char inputBuffer[2];
    int menuOption;
    
   

    //Program arguments
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