#include "headers.h"
#include "ls.h"

void print_ls(char path[], int flag_a, int flag_l){
    struct dirent *d;
    DIR *dh = opendir(path);
    if (!dh){
        if (errno = ENOENT){
            perror("Directory doesn't exist");
        }
        else{
            perror("Unable to read directory");
        }
        exit(0);
    }

    while ((d = readdir(dh)) != NULL){
        if (!flag_a && d->d_name[0] == '.')
            continue;
        printf("%s  ", d->d_name);
        if(flag_l) printf("\n");
    }

    if(!flag_l)
        printf("\n");
    return;
}

void list_files(char *argv[]){
    if(argv[1]==NULL){
        print_ls(".", 0, 0);
    }
    else{
        int flag_a = 0, flag_l = 0;

        int arg_index = 0;
        while(argv[arg_index]!=NULL){
            if(!strcmp(argv[arg_index], "-a") || !strcmp(argv[arg_index], "-al") || !strcmp(argv[arg_index], "-la"))
                flag_a = 1;
            if(!strcmp(argv[arg_index], "-l") || !strcmp(argv[arg_index], "-al") || !strcmp(argv[arg_index], "-la"))
                flag_l = 1;
            arg_index++;
        }

        arg_index = 1;
        char path[PATH_MAX];

        while(argv[arg_index]!=NULL){
            if(strcmp(argv[arg_index], "-l") && strcmp(argv[arg_index], "-a") && strcmp(argv[arg_index], "-al") && strcmp(argv[arg_index], "-la")){
                for(i = 0; i<strlen(argv[arg_index]); i++){
                    path[i] = argv[arg_index][i];
                }
                // printf("\n%s %ld %d", argv[arg_index], strlen(argv[arg_index]), arg_index);
            }
            arg_index++;
        }

        if(strlen(path)!=0){
            if(path[0]=='~'){
                char newpath[PATH_MAX];
                // printf("%s\n", newpath);
                for(i = 0; i<strlen(home_dir); i++){
                    newpath[i] = home_dir[i];
                    // printf("%c", newpath[i]);
                }
                printf("\n%ld", strlen(path));
                for(int j = 1; j<strlen(path); j++, i++){
                    newpath[i] = path[j];
                    // printf("%c", newpath[i]);
                }
                print_ls(newpath, flag_a, flag_l);
            }
            else{
                print_ls(path, flag_a, flag_l);
            }    
        }       
        else
            print_ls(".", flag_a, flag_l);
    }
}
