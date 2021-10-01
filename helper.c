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

		int check = check_command(argv);

		if(!check){
			// fork and execute the command
			pid = fork();
			// printf("FORKING\n");
			if(pid < 0){
				printf("failed to create a child\n");
			}
			else if(pid == 0){
				// printf("hello from child\n");
				// execute a command
				// int test = execvp(argv[0], argv);
				// printf("%d", test);
				// printf("%s", argv[1]);
				setpgid(0, 0);
				int exec_return = execvp(argv[0], argv);
				if (exec_return < 0) // if invalid command, print its invalid and exit
        		{
		            printf("Command \"%s\" not found.\n", argv[0]);
		            exit(0);
        		}
				// else{
				// 	_exit(0);
				// }
				// printf("CHILD EXITING\n");
				// _exit(0);

			}
			else{
				// printf("hello from parent\n");
				// wait for the command to finish if "&" is not present
				if(argv[i]==NULL){
					// check_command(argv);
					// printf("WAITING\n");
					// waitpid(-1, NULL, WUNTRACED);
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
				// printf("PARENT EXITING\n");
				// printf("\n");
				// exit(0);
			}
		}
	}
}

void get_command(){
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

int check_command(char *cmd[]){
	// printf("CHECKING COMMAND %s", argv[0]);
	if(!strcmp(cmd[0], "cd")){
		change_directory(cmd);
		return 1;
	}
	else if(!strcmp(cmd[0], "echo")){
		echo_command(cmd);
		return 1;
	}
	else if(!strcmp(cmd[0], "pwd")){
		pwd_command(cmd);
		return 1;
	}
	else if(!strcmp(cmd[0], "ls")){
		list_files(cmd);
		return 1;
	}
	else if(!strcmp(cmd[0], "pinfo")){
		pinfo(cmd);
		return 1;
	}
	else if(!strcmp(cmd[0], "repeat")){
		repeat_command(cmd);
		return 1;
	}
	else if(!strcmp(cmd[0], "history")){
		show_history(cmd);
		return 1;
	}
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
	    }
	}
	// get_command();
}