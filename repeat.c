#include "headers.h"
#include "repeat.h"
#include "helper.h"
#include "cd.h"
#include "echo.h"
#include "pwd.h"
#include "ls.h"
#include "pinfo.h"

void repeat_command(char *argv[]){

    if(argv[1]==NULL || argv[2]==NULL){
        printf("repeat: Too less arguments!\n");
        return;
    }
    else{

        int loop;
        sscanf(argv[1], "%d", &loop);
        // printf("%d\n", loop);
        // printf("%s\n", argv[2]);
        // printf("%s\n", argv[3]);
        char *command_to_run[MAX_SIZE_ARG];

        for(int ii = 2; argv[ii]!=NULL; ii++){
            // printf("%s %s\n", argv[ii], command_to_run[ii-2]);
            command_to_run[ii-2] = strdup(argv[ii]);
            // printf("%s ", argv[ii]);
        }
        // printf("\n");
        // for(int ii = 0; command_to_run[ii]!=NULL; ii++){
        //     printf("%s ", command_to_run[ii]);
        // }
        while(loop--){
            // fork and execute the command
            pid = fork();
            if(pid < 0){
                printf("failed to create a child\n");
            }
            else if(pid == 0){
                if(!check_command(command_to_run)){
                    execvp(command_to_run[0], command_to_run);
                }
            }
            else{
                if(argv[i]==NULL){
                    waitpid(pid, NULL, 0);
                }
            }
        }
    }

	return;
}