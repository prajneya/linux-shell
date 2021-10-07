#include "headers.h"
#include "bg.h"

void bg(char *argv[]){
    
    if(argv[1]==NULL){
        printf("No argument for bg provided!\n");
    }
    else{
        int job_num = atoi(argv[1]);

        if(job_num-1 > process_count || job_num<=0){
            fprintf(stderr, "NO JOB FOUND\n");
            return;
        }

        struct job curr = jobs[job_num-1];

        pid_t toBg = curr.pid;

        if(kill(toBg, SIGCONT))
            perror("bg");

    }

	return;
}