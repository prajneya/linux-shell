#include "headers.h"
#include "fg.h"

void fg(char *argv[]){
    
    if(argv[1]==NULL){
        printf("No argument for fg provided!\n");
    }
    else{
        int job_num = atoi(argv[1]);

        struct job curr = jobs[job_num-1];

        int toFg = curr.pid;

        setpgid(toFg, getpgid(0));

        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);

        tcsetpgrp(0, toFg);

        if(kill(toFg, SIGCONT))
            perror("fg");

        int status;
        waitpid(toFg, &status, WUNTRACED);

        tcsetpgrp(0, getpgid(0));

        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
        
        int flag = 0;
        for (int ii = 1; ii <= process_count; ii++){
          if (jobs[ii].pid == toFg){
            flag = 1;
            for (int j = i; j < process_count; j++)
              jobs[j] = jobs[j + 1];
            process_count--;
          }
        }

    }

	return;
}