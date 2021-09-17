#include "headers.h"
#include "pinfo.h"

void print_pinfo(char process_id[]){
    char process_directory[PATH_MAX] = { '\0' };

    char buffer[PATH_MAX];

    strcpy(process_directory, "/proc/");
    strcat(process_directory, process_id);
    strcat(process_directory, "/");

    char process_file[PATH_MAX] = { '\0' };
    process_file[0] = 0;

    strcat(process_file, process_directory);
    strcat(process_file, "stat");


    int fd = open(process_file, O_RDONLY);
    read(fd, buffer, 1024);

    if(fd < 0) {
        printf("Process with pid %s not found\n", process_id);
        return;
    }

    if(!strcmp(process_id, "self")) {
        printf("pid -- %d\n", getpid());
    }

    else {
        printf("pid -- %s\n", process_id);
    }

    strtok(buffer, " ");
    strtok(NULL, " ");
    char * status = strtok(NULL, " ");
    
    printf("Process status: %s\n", status);

    close(fd);

    // Memory
    char process_file_mem[PATH_MAX] = { '\0' };
    process_file_mem[0] = 0;

    strcat(process_file_mem, process_directory);
    strcat(process_file_mem, "statm");


    fd = open(process_file_mem, O_RDONLY);
    read(fd, buffer, 1024);

    char * memory = strtok(buffer, " ");
    printf("Memory -- %s\n", memory);

    close(fd);

    // Executable Path
    strcat(process_directory, "exe");

    int l = readlink(process_directory, buffer, 1024);
    buffer[l] = 0;

    printf("Executable path -- %s\n", buffer);

}

void pinfo(char *argv[]){
    if(argv[1]==NULL){
        print_pinfo("self");
    }
    else if(argv[2]!=NULL){
        printf("pinfo: too many arguments!\n");
    }
    else{
        print_pinfo(argv[1]);
    }
    return;
}
