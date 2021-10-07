#include "headers.h"
#include "sig.h"

void sendSig(char *argv[]){
    
    if(argv[1]==NULL){
        printf("No argument for sig provided!\n");
    }
    else if(argv[2]==NULL){
        printf("Too less arguments for sig provided!\n");
    }
    else{
        int job_num = atoi(argv[1]);
        int sig = atoi(argv[2]);

        if(job_num-1 > process_count || job_num<=0){
            fprintf(stderr, "NO JOB FOUND\n");
            return;
        }

        struct job curr = jobs[job_num-1];

        if(curr.pid < 0){
            fprintf(stderr, "An error occured while sending signal to the job requested\n");
        } 
        else{
            if(kill(curr.pid, sig))
                perror("sig");
        }
    }

	return;
}