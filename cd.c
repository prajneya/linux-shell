#include "headers.h"
#include "cd.h"

void change_directory(char *argv[], char prev_dir[]){
    char cwd[PATH_MAX] = { '\0' };
    getcwd(cwd, sizeof(cwd));
    // printf("%s %s\n", cwd, prev_dir);

	if(argv[1]==NULL){
		printf("No argument for cd provided! Changing directory to HOME!\n");
        
        if(chdir(home_dir) != 0){
            perror("Error");
        }
        else{
            for(i = 0; i<strlen(cwd) || i<strlen(prev_dir); i++){
                prev_dir[i] = cwd[i];
            }
        }
	}
	else if(argv[2]!=NULL){
		printf("cd: too many arguments!\n");
	}
	else if(!strcmp(argv[1], "~")){
        if(chdir(home_dir) != 0){
            perror("Error");
        }
        else{
            for(int ii = 0; ii<strlen(cwd) || ii<strlen(prev_dir); ii++){
                prev_dir[ii] = cwd[ii];
            }
        }
    }
    else if(!strcmp(argv[1], "-")){
        printf("%s\n", prev_dir);
        if(chdir(prev_dir) != 0){
            perror("Error");
        }
        else{
            for(int ii = 0; ii<strlen(cwd) || ii<strlen(prev_dir); ii++){
                prev_dir[ii] = cwd[ii];
            }
        }
    }
    else{
        // printf("\n%s", argv[1]);
        if(chdir(argv[1]) != 0){
            perror("Error");
        }
        else{
            for(int ii = 0; ii<strlen(cwd) || ii<strlen(prev_dir); ii++){
                prev_dir[ii] = cwd[ii];
            }
            getcwd(cwd, sizeof(cwd));
            // printf("AFTER UPDATING\n%s %s\n", cwd, prev_dir);
        }
        // else{
        //     printf("CHANGED DIRECTORY");
        //     char twd[PATH_MAX];
        //     getcwd(twd, sizeof(twd));
        //     printf("%s", twd);
        // }
    } 
    return;

}
