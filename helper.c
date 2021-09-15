#include "headers.h"
#include "helper.h"
#include "cd.h"
#include "echo.h"
#include "pwd.h"
#include "ls.h"

void c_shell(){

	
	getcwd(home_dir, sizeof(home_dir));
	while(1){
		// get the command from user
		get_command(home_dir);

		// bypass empty commands
		if(!strcmp("", cmd)) continue;

		// check for "exit" command
                if(!strcmp("exit", cmd)) break;

		// fit the command into *argv[]
		convert_command();

		// fork and execute the command
		pid = fork();
		if(pid < 0){
			printf("failed to create a child\n");
		}
		else if(pid == 0){
			// printf("hello from child\n");
			// execute a command
			// int test = execvp(argv[0], argv);
			// printf("%d", test);
			// printf("%s", argv[1]);
			exit(0);

		}
		else{
			// printf("hello from parent\n");
			// wait for the command to finish if "&" is not present

			check_command();
			if(argv[i]==NULL) waitpid(pid, NULL, 0);
		}
	}
}

void get_command(){
	// get command from user
	// NEED TO ADD ERROR HANDLING
	char hostname[HOST_NAME_MAX];
	char username[LOGIN_NAME_MAX];
	char cwd[PATH_MAX];
	gethostname(hostname, HOST_NAME_MAX);
	getlogin_r(username, LOGIN_NAME_MAX);
	getcwd(cwd, sizeof(cwd));

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
		char wd[PATH_MAX];
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

void check_command(char cwd[]){
	// printf("CHECKING COMMAND %s", argv[0]);
	if(!strcmp(argv[0], "cd")){
		char prev_dir[PATH_MAX];
		change_directory(argv, prev_dir);
	}
	else if(!strcmp(argv[0], "echo")){
		echo_command(argv);
	}
	else if(!strcmp(argv[0], "pwd")){
		pwd_command(argv);
	}
	else if(!strcmp(argv[0], "ls")){
		list_files(argv);
	}
}

void log_handle(int sig){
	//printf("[LOG] child proccess terminated.\n");
	FILE *pFile;
    pFile = fopen("log.txt", "a");
    if(pFile==NULL) perror("Error opening file.");
    else fprintf(pFile, "[LOG] child proccess terminated.\n");
    fclose(pFile);
}