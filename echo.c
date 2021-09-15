#include "headers.h"
#include "echo.h"

void echo_command(char *argv[]){
	if(argv[1]==NULL){
		printf("\n");
	}
	else{
        for(i = 1; argv[i]!=NULL; i++){
            if(argv[i]){
                printf("%s ", argv[i]);
            }
        }
        printf("\n");    
    }   
	return;
}