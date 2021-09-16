#include "headers.h"
#include "pwd.h"

void pwd_command(char *argv[]){
	if(argv[1]!=NULL){
		printf("Too many arguments!\n");
	}
	else{
        char cwd[PATH_MAX] = { '\0' };
        getcwd(cwd, sizeof(cwd));

        // int ii;
        // for(ii = 0; ii<strlen(cwd) && ii<strlen(home_dir); ii++){
        //     if(cwd[ii]!=home_dir[ii]){
        //         break;
        //     }
        // }
        
        // int cwd_len = strlen(cwd);
        // int home_len = strlen(home_dir);

        // if(cwd_len>=home_len){
        //     char wd[PATH_MAX] = { '\0' };
        //     int k = 0;
        //     for(int j = ii; j<strlen(cwd) || k<strlen(wd); j++){
        //         wd[k] = cwd[j];
        //         k++;
        //     }
        //     if(k==0){
        //         printf("~\n");
        //     }
        //     else{
        //         printf("~%s\n", wd);
        //     }
            
        // }
        // else{
            printf("%s\n", cwd);
        // } 
    }   
	return;
}