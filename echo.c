#include "headers.h"
#include "echo.h"

void echo_command(char *argv[]){
    // printf("%d%d\n", output_flag, input_flag);
	if(argv[1]==NULL){
        if(input_flag){
            // printf("%s\n ", input_path);
            FILE *in_file  = fopen(input_path, "r");
            if(in_file==NULL) perror("Error opening file.");
            char echo_string[MAX_SIZE_CMD];

            char ch =fgetc(in_file);
            int e_i = 0;
            while(ch!=EOF && e_i<MAX_SIZE_CMD){
                echo_string[e_i] = ch;
                e_i++;
                ch=fgetc(in_file);
            }

            fclose(in_file);
            // printf("%s ", echo_string);
            if(output_flag==1){
                FILE *pFile;
                pFile = fopen(output_path, "w+");
                if(pFile==NULL) perror("Error opening file.");
                else fprintf(pFile, "%s ", echo_string);
                fclose(pFile);
            }
            else if(output_flag==2){
                FILE *pFile;
                pFile = fopen(output_path, "a+");
                if(pFile==NULL) perror("Error opening file.");
                else fprintf(pFile, "%s ", echo_string);
                fclose(pFile);
            }
            else
                printf("%s ", echo_string);
        }
        
		printf("\n");
	}
	else{
        FILE *pFile;
        if(output_flag==1){
            pFile = fopen(output_path, "w+");
            fprintf(pFile, "");
            fclose(pFile);
        }
        for(int ii = 1; argv[ii]!=NULL; ii++){
            if(argv[ii]){
                if(output_flag==1){
                    pFile = fopen(output_path, "a+");
                    if(pFile==NULL) perror("Error opening file.");
                    else fprintf(pFile, "%s ", argv[ii]);
                    fclose(pFile);
                }
                else if(output_flag==2){
                    pFile = fopen(output_path, "a+");
                    if(pFile==NULL) perror("Error opening file.");
                    else fprintf(pFile, "%s ", argv[ii]);
                    fclose(pFile);
                }
                else
                    printf("%s ", argv[ii]);
            }
        }
        printf("\n");    
    }   
	return;
}