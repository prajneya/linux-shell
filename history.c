#include "headers.h"
#include "history.h"

void save_command(char *argv[]){
    FILE *fptr;
    fptr = fopen("/home/prajneya/os/shell/history.txt", "a+");

    if(fptr == NULL){
      printf("Error in saving history!");   
      exit(1);             
    }

    int history_count = 0;
    char ch =fgetc(fptr);
    // printf("%c\n", ch);
    // printf("%d\n", ch==EOF);
    while(ch!=EOF){
        // printf("A%c", ch);
        if(ch=='\n')
            history_count++;
        ch=fgetc(fptr);
    }

    // printf("%d %d\n", history_count, MAX_HISTORY_COUNT);

    if(history_count<MAX_HISTORY_COUNT){
        fseek(fptr, 0, SEEK_END);
        for(int ii = 0; argv[ii]!=NULL; ii++)
            fprintf(fptr,"%s ",argv[ii]);
        fprintf(fptr,"\n");
    }
    else{
        // printf("MORE THAN 20 HISTORY COMMANDS!\n");

        FILE *fptr_temp;
        fptr_temp = fopen("/home/prajneya/os/shell/history_temp.txt", "a+");

        if(fptr_temp == NULL){
            printf("Error in saving history!");   
            exit(1);             
        }
        fseek(fptr, 0, SEEK_SET);

        char c = fgetc(fptr);
        
        int line_number = 0;

        if(c!=EOF){
            line_number=1;
        }
        while(1){
            if(c =='\n') line_number++;
            if(c == EOF) break;
            if(line_number != 1){
                if(line_number == 2 && c=='\n'){
                    c = fgetc(fptr);
                }
                else{
                    // printf("%d %c", line_number, c);
                    fprintf(fptr_temp ,"%c",c);
                    c = fgetc(fptr);
                }
            }
            else{
                c = fgetc(fptr);
            }
        }

        fseek(fptr_temp, 0, SEEK_END);
        for(int ii = 0; argv[ii]!=NULL; ii++)
            fprintf(fptr_temp,"%s ",argv[ii]);
        fprintf(fptr_temp,"\n");

        remove("/home/prajneya/os/shell/history.txt");
        rename("/home/prajneya/os/shell/history_temp.txt", "/home/prajneya/os/shell/history.txt");

        fclose(fptr_temp);
    }
    

    fclose(fptr);

	return;
}

void show_history(char *argv[]){

    int num_commands = 10;

    if(argv[1]!=NULL){
        sscanf(argv[1], "%d", &num_commands);
        if(num_commands>10){
            num_commands = 10;
        }
    }

    FILE *fptr;
    fptr = fopen("/home/prajneya/os/shell/history.txt", "r");

    char line[MAX_SIZE_ARG];

    int history_count = 0;
    while(history_count!=num_commands){
        printf("%d ", history_count+1);
        fseek(fptr, 0, SEEK_SET);
        int line_count = 0;
        while (fgets(line, sizeof line, fptr) != NULL){
            if (line_count == MAX_HISTORY_COUNT - history_count){
                printf("%s", line);
                break;
            }
            else{
                line_count++;
            }
        } 
        history_count++;
    }
    

    fclose(fptr);

}

void print_history(){
    FILE *fptr;
    fptr = fopen("/home/prajneya/os/shell/history.txt", "r");

    char line[MAX_SIZE_ARG];
    int line_count = 0;
    while (fgets(line, sizeof line, fptr) != NULL){
        if (line_count == MAX_HISTORY_COUNT - up_history){
            write(0, line, sizeof(line));
            break;
        }
        else{
            line_count++;
        }
    } 
}