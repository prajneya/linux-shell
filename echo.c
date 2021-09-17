#include "headers.h"
#include "echo.h"

void echo_command(char *argv[]){
	if(argv[1]==NULL){
		printf("\n");
	}
	else{
        for(int ii = 1; argv[ii]!=NULL; ii++){
            if(argv[ii]){
                printf("%s ", argv[ii]);
            }
        }
        printf("\n");    
    }   
	return;
}