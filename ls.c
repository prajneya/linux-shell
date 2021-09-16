#include "headers.h"
#include "ls.h"

void print_ls(char path[], int flag_a, int flag_l){
    // printf("%s %d %d\n", path, flag_a, flag_l);
    struct dirent *d;
    DIR *dh = opendir(path);
    if (!dh){
        if (errno = ENOENT){
            perror("Directory doesn't exist");
        }
        else{
            perror("Unable to read directory");
        }
    }

    unsigned long size = 0;

    unsigned long tot_size = 0;

    while((d = readdir(dh)) != NULL){
        if (!flag_a && d->d_name[0] == '.')
            continue;

        char fileName[PATH_MAX] = { '\0' };
        fileName[0] = 0;

        strcpy(fileName, path);
        strcat(fileName, "/");
        strcat(fileName, d->d_name);

        struct stat st;
        lstat(fileName, &st);

        unsigned long size = st.st_blocks;
        // printf("%ld\n", size);
        tot_size += size;
    }

    if(flag_l)
        printf("total %ld\n", tot_size >> 1);

    // printf("%s\n", path);
    struct dirent *d_i;
    DIR *dh_i = opendir(path);
    while((d_i = readdir(dh_i)) != NULL){
        // printf("%s %d %d\n", path, flag_a, flag_l);
        if (!flag_a && d_i->d_name[0] == '.')
            continue;
        if(!flag_l){
            printf("%s  ", d_i->d_name);
        }
        else{
            // printf("ABVD");
            char fileName[PATH_MAX] = { '\0' };
            fileName[0] = 0;

            strcpy(fileName, path);
            strcat(fileName, "/");
            strcat(fileName, d_i->d_name);

            struct stat st;
            if(lstat(fileName, &st) < 0) {
                perror(path);
                return;
            }

            char perm[11] = { '\0' };

            perm[10] = 0;
            perm[0] = '-';

            // printf("%s  ", perm);

            if(S_ISDIR(st.st_mode))
                perm[0] = 'd';
            if(S_ISLNK(st.st_mode))
                perm[0] = 'l';
            if(S_ISCHR(st.st_mode))
                perm[0] = 'c';
            if(S_ISSOCK(st.st_mode))
                perm[0] = 's';

            perm[1] = !!(st.st_mode & S_IRUSR) ? 'r' : '-';
            perm[2] = !!(st.st_mode & S_IWUSR) ? 'w' : '-';
            perm[3] = !!(st.st_mode & S_IXUSR) ? 'x' : '-';

            perm[4] = !!(st.st_mode & S_IRGRP) ? 'r' : '-';
            perm[5] = !!(st.st_mode & S_IWGRP) ? 'w' : '-';
            perm[6] = !!(st.st_mode & S_IXGRP) ? 'x' : '-';

            perm[7] = !!(st.st_mode & S_IROTH) ? 'r' : '-';
            perm[8] = !!(st.st_mode & S_IWOTH) ? 'w' : '-';
            perm[9] = !!(st.st_mode & S_IXOTH) ? 'x' : '-';

            char time[17] = { '\0' };

            ctime_r(&st.st_mtime, time);
            time[16] = 0;

            printf("%s %3ld %8s %8s %10ld %s %s\n", perm, st.st_nlink, getpwuid(st.st_uid)->pw_name,
                getgrgid(st.st_gid)->gr_name, st.st_size, time + 4, d_i->d_name);
        }
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
        char path[PATH_MAX] = { '\0' };

        // printf("%ld\n", strlen(path));
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
                // printf("\n%ld", strlen(path));
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
