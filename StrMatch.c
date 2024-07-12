#include "commonHeaders.h"
#include "modules.h"
void strMatch(char **funcList, int funcListLen, char *msg, char**returnList){
    int i=0;
    char *match;
    int j=0;
    char *token;
    char * token2;
    char *saved = msg;
    char *saved2;
    char * res;
    char * saved3;
    //printf("ws msg %s\n", msg);
    
    while((token = strtok_r(saved, "\n", &saved))!=NULL){
        for(i=0; i<funcListLen; i++){//when passing the array, you also need to pass the size
            //strtok funcList[i] to remove the extra characters
            saved2 = funcList[i];
            token2 = strtok_r(saved2,"\n\r",&saved2);
            match = strstr(token, token2);
            
            // printf(">>match:%s <<token:%s funcList %d: %s len:%ld \n", match, token, i, token2, strlen(token2));
            if(match){
                // printf("MATCH\n");
                free(returnList[j]);
                saved3=token;
                res = strtok_r(saved3," ",&saved);//remove whitespace
                returnList[j]=strndup(saved3, strlen(saved3));//something here is causing a mem leak, probably token
                //printf("found!\n");
                //j++;
            }
        }
    }
}