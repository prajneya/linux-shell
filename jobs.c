#include "headers.h"
#include "jobs.h"

struct job_enlist{
    int index;
    char status[MAX_SIZE_ARG];
    char job_name[MAX_SIZE_ARG];
    int pid;
};

int job_comparator(const void *v1, const void *v2){
    const struct job_enlist *p1 = (struct job_enlist *)v1;
    const struct job_enlist *p2 = (struct job_enlist *)v2;
    if (strcmp(p1->job_name, p2->job_name)<0)
        return -1;
    else if (strcmp(p1->job_name, p2->job_name)>0)
        return +1;
    else
        return 0;
}

void printJobs(char *argv[]){
    int index = 1, fd;

    char * buf = (char*) malloc(PATH_MAX);

    struct job_enlist all_jobarr[MAX_JOBS];

    for(int ii = 0; ii<=process_count; ii++){
        struct job curr = jobs[ii];
        sprintf(buf, "/proc/%d/stat", curr.pid);
        fd = open(buf, O_RDONLY);

        if(fd < 0) {
            // fprintf(stderr, "Couldn't find relevant files for pid %d\n", curr.pid);
            continue;
        }

        read(fd, buf, PATH_MAX);

        strtok(buf, " ");
        strtok(NULL, " ");
        char * status, procStat = strtok(NULL, " ")[0];

        if(procStat == 'T')
            status = "Stopped";
        else if(procStat == 'Z')
            status = "Zombie";
        else
            status = "Running";

        all_jobarr[index-1].index = index;
        strcpy(all_jobarr[index-1].status, status);
        strcpy(all_jobarr[index-1].job_name, curr.job_name);
        all_jobarr[index-1].pid = curr.pid;

        // printf("[%d] %s %s [%d]\n", index, status, curr.job_name, curr.pid);
        // printf("[%d] %s %s [%d]\n", all_jobarr[index].index, all_jobarr[index].status, all_jobarr[index].job_name, all_jobarr[index].pid);

        index++;

        close(fd);
    }

    free(buf);

    int flag_r = 0, flag_s = 0;

    int arg_index = 0;
    while(argv[arg_index]!=NULL){
        if(!strcmp(argv[arg_index], "-r") || !strcmp(argv[arg_index], "-rs") || !strcmp(argv[arg_index], "-sr"))
            flag_r = 1;
        if(!strcmp(argv[arg_index], "-s") || !strcmp(argv[arg_index], "-rs") || !strcmp(argv[arg_index], "-sr"))
            flag_s = 1;
        arg_index++;
    }

    qsort(all_jobarr, process_count+1, sizeof(struct job_enlist), job_comparator);

    for(int ii = 1; ii<=process_count; ii++){
        if(all_jobarr[ii].index == 0)
            break;
        if(flag_s)
            if(!strcmp(all_jobarr[ii].status, "Stopped"))
                printf("[%d] %s %s [%d]\n", all_jobarr[ii].index, all_jobarr[ii].status, all_jobarr[ii].job_name, all_jobarr[ii].pid);
        if(flag_r)
            if(!strcmp(all_jobarr[ii].status, "Running"))
                printf("[%d] %s %s [%d]\n", all_jobarr[ii].index, all_jobarr[ii].status, all_jobarr[ii].job_name, all_jobarr[ii].pid);

        if(!flag_r && !flag_s)
            printf("[%d] %s %s [%d]\n", all_jobarr[ii].index, all_jobarr[ii].status, all_jobarr[ii].job_name, all_jobarr[ii].pid);
    }

    return;
}
