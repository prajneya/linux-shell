#include "headers.h"
#include "helper.h"
#include "cd.h"
#include "echo.h"
#include "pwd.h"
#include "ls.h"
#include "pinfo.h"
#include "repeat.h"
#include "history.h"

void del_process(int id){
	int flag = 0;
	for (int ii = 1; ii <= process_count; ii++){
	  if (jobs[ii].pid == id){
	    flag = 1;
	    for (int j = i; j < process_count; j++)
	      jobs[j] = jobs[j + 1];
	    process_count--;
	  }
	}
}

void c_shell(){

	getcwd(home_dir, sizeof(home_dir));
	while(1){
		// printf("LOOPING!\n");
		// get the command from user
		get_command(home_dir);


		// bypass empty commands
		if(!strcmp("", cmd)) continue;

		//check for "exit" command
        if(!strcmp("exit", cmd)){
        	kill(0, SIGKILL);
        	break;
        }

		// fit the command into *argv[]
		convert_command();
		save_command(argv);

		int check = check_command(argv, i);

		if(!check){
			// fork and execute the command
			pid = fork();
			// printf("FORKING\n");
			if(pid < 0){
				printf("failed to create a child\n");
			}
			else if(pid == 0){
				// printf("hello from child\n");
				setpgid(0, 0);
				if(output_flag==1){
					int out_file = open(output_path, O_RDWR|O_CREAT, 0644);
					if(out_file < 0) perror("Error opening output file.");
				    int dup_err = dup2(out_file, 1);
				    if(dup_err<0) perror("Error changing stdout.");
				    close(out_file);
				}
				else if(output_flag==2){
					int out_file = open(output_path, O_RDWR|O_CREAT|O_APPEND, 0644);
					if(out_file < 0) perror("Error opening output file.");
					
				    int dup_err = dup2(out_file, 1);
				    if(dup_err<0) perror("Error changing stdout.");
				    close(out_file);
				}

				int exec_return;
				// printf("%d%d\n", output_flag, input_flag);
				if(input_flag){
		            int in_file = open(input_path, O_RDONLY);
		            if(in_file<0) perror("Error opening input file.");
				    dup2(in_file, 0);
				    char *file_argv[MAX_SIZE_CMD];

		            file_argv[0] = malloc(MAX_SIZE_ARG);
		            strcpy(file_argv[0], argv[0]);
		            file_argv[1] = NULL;
					exec_return = execvp(argv[0], file_argv);
				}
				else{
					exec_return = execvp(argv[0], argv);
				}
				if (exec_return < 0){
		            printf("Command \"%s\" not found.\n", argv[0]);
		            exit(0);
        		}

			}
			else{
				// printf("hello from parent\n");
				// wait for the command to finish if "&" is not present
				if(argv[i]==NULL){
					signal(SIGTTIN, SIG_IGN);
            		signal(SIGTTOU, SIG_IGN);

					tcsetpgrp(STDIN_FILENO, pid);
		            int wstatus;
		            waitpid(-1, &wstatus, WUNTRACED);
		            tcsetpgrp(STDIN_FILENO, getpgrp());

		            signal(SIGTTIN, SIG_DFL);
            		signal(SIGTTOU, SIG_DFL);
				}
				else{
					printf("%d\n", pid);
					process_count++;
					jobs[process_count].pid = pid;
					strcpy(jobs[process_count].job_name, argv[0]);
				}
			}
		}
	}
}

void get_command(){

	dup2(saved_stdout, 1);
	close(saved_stdout);

	dup2(saved_stdin, 0);
	close(saved_stdin);

	saved_stdout = dup(1);
	saved_stdin = dup(0);

	input_flag = 0;
	output_flag = 0;
	strcpy(input_path, "");
	strcpy(output_path, "");

	// get command from user
	// NEED TO ADD ERROR HANDLING
	char hostname[HOST_NAME_MAX]  = { '\0' };
	char username[LOGIN_NAME_MAX]  = { '\0' };
	char cwd[PATH_MAX]  = { '\0' };
	gethostname(hostname, HOST_NAME_MAX);
	getlogin_r(username, LOGIN_NAME_MAX);
	getcwd(cwd, sizeof(cwd));

	// printf("PRINTING\n%s\n", cwd);

	int ii;
	for(ii = 0; ii<strlen(cwd) && ii<strlen(home_dir); ii++){
		// printf("%c%c", cwd[ii], home_dir[ii]);
		if(cwd[ii]!=home_dir[ii]){
			// printf("DIFF %c%c", cwd[ii], home_dir[ii]);
			break;
		}
		// printf("%c%c", cwd[ii], home_dir[ii]);
	}
	
	int cwd_len = strlen(cwd);
	int home_len = strlen(home_dir);

	if(cwd_len>=home_len){
		// printf("%d %d, %d", cwd_len, home_len, cwd_len<home_len);
		char wd[PATH_MAX] = { '\0' };
		int k = 0;
		for(int j = ii; j<strlen(cwd) || k<strlen(wd); j++){
			wd[k] = cwd[j];
			k++;
		}
		if(k==0){
			printf("%s@%s:~>", username, hostname);
		}
		else{
			printf("%s@%s:~%s>", username, hostname, wd);
		}
		
	}
	else{
		// printf("%d", i);
		printf("%s@%s:%s>", username, hostname, cwd);
	}

	// print_history();
	// up_history++;

	up_history = 0;

	fgets(cmd, MAX_SIZE_CMD, stdin);
	// remove trailing newline
	if ((strlen(cmd) > 0) && (cmd[strlen (cmd) - 1] == '\n'))
        	cmd[strlen (cmd) - 1] = '\0';
	//printf("%s\n", cmd);
}

void convert_command(){
	// split string into argv
	char *ptr;
	i = 0;
	ptr = strtok(cmd, " \t\r\n\a");
	while(ptr != NULL){
		//printf("%s\n", ptr);
		argv[i] = ptr;
		i++;
		ptr = strtok(NULL, " \t\r\n\a");
	}

	// check for "&"
	if(!strcmp("&", argv[i-1])){
	argv[i-1] = NULL;
	argv[i] = "&";
	}else{
	argv[i] = NULL;
	}
	//printf("%d\n", i);
}

int check_command(char *cmd[], int n_args){
	// printf("CHECKING COMMAND %s", cmd[0]);

	int cmd_flag = 0;

	for(int ii = n_args-1; ii>=0; ii--){
		if(!strcmp(cmd[ii], ">")){
			char *command_to_run[MAX_SIZE_ARG];
			int zz = 0;
			for(zz = 0; zz<ii; zz++){
				command_to_run[zz] = strdup(cmd[zz]);
			}
			command_to_run[zz] = NULL;
			output_flag = 1;
			strcpy(output_path, strdup(cmd[zz+1]));	
			check_command(command_to_run, zz);
			cmd_flag = 1;
			break;
		}
		else if(!strcmp(cmd[ii], ">>")){
			char *command_to_run[MAX_SIZE_ARG];
			int zz = 0;
			for(zz = 0; zz<ii; zz++){
				command_to_run[zz] = strdup(cmd[zz]);
			}
			command_to_run[zz] = NULL;
			output_flag = 2;
			strcpy(output_path, strdup(cmd[zz+1]));
			check_command(command_to_run, zz);
			cmd_flag = 1;
			break;
		}
		else if(!strcmp(cmd[ii], "<")){
			char *command_to_run[MAX_SIZE_ARG];
			int zz = 0;
			for(zz = 0; zz<ii; zz++){
				command_to_run[zz] = strdup(cmd[zz]);
			}
			command_to_run[zz] = NULL;
			input_flag = 1;
			strcpy(input_path, strdup(cmd[zz+1]));
			check_command(command_to_run, zz);
			cmd_flag = 1;
			break;
		}
	}

	if(!strcmp(cmd[0], "cd")){
		if(cmd_flag==0)
			change_directory(cmd);
		return 1;
	}
	else if(!strcmp(cmd[0], "echo")){
		if(cmd_flag==0)
			echo_command(cmd);
		return 1;
	}
	else if(!strcmp(cmd[0], "pwd")){
		if(cmd_flag==0)
			pwd_command(cmd);
		return 1;
	}
	else if(!strcmp(cmd[0], "ls")){
		if(cmd_flag==0)
			list_files(cmd);
		return 1;
	}
	else if(!strcmp(cmd[0], "pinfo")){
		if(cmd_flag==0)
			pinfo(cmd);
		return 1;
	}
	// else if(!strcmp(cmd[0], "repeat")){
	// 	repeat_command(cmd);
	// 	return 1;
	// }
	// else if(!strcmp(cmd[0], "history")){
	// 	show_history(cmd);
	// 	return 1;
	// }
	else{
		return 0;
	}
}

void log_handle(int sig){
	//printf("[LOG] child proccess terminated.\n");
	FILE *pFile;
    pFile = fopen("log.txt", "a");
    if(pFile==NULL) perror("Error opening file.");
    else fprintf(pFile, "[LOG] child proccess terminated.\n");
    fclose(pFile);


	for(int ii = 0; ii<=process_count; ii++){
		int status;
			pid_t p = waitpid(-1, &status, WNOHANG);
			if (p < 0){
	      perror("\nwaitpid failed\n");
	    }
	    const int exit = WEXITSTATUS(status);
	    // printf("%d %d %s %d\n", p, jobs[ii].pid, jobs[ii].job_name, exit);
	    if ((WIFEXITED(status) && p == jobs[ii].pid)){
	      if (exit == 0)
	        printf("\n%s with pid %d exited normally with exit status: %d\n", jobs[ii].job_name, jobs[ii].pid, exit);
	      else
	        printf("\n%s with pid %d exited abnormally\n", jobs[ii].job_name, jobs[ii].pid);
	      del_process(p);
	      get_command();
	    }
	}
	// get_command();
}