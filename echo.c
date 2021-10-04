#include "headers.h"
#include "echo.h"

void echo_command(char *argv[], int output_flag, int input_flag, char* output_path, char *input_path){
	if(argv[1]==NULL){
        if(input_flag){
            FILE *in_file  = fopen(input_path, "r");
            char *echo_string;
            fscanf(in_file, "%s", &echo_string);  
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