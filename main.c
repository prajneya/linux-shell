#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>

#define	MAX_SIZE_CMD	256
#define	MAX_SIZE_ARG	16

char cmd[MAX_SIZE_CMD];				// string holder for the command
char *argv[MAX_SIZE_ARG];			// an array for command and arguments
pid_t pid;										// global variable for the child process ID
char i;												// global for loop counter

void get_command();								// get command string from the user
void convert_command();						// convert the command string to the required format by execvp()
void c_shell();								// to start the shell
void log_handle(int sig);			// signal handler to add log statements

int main(){
	// tie the handler to the SGNCHLD signal
	signal(SIGCHLD, log_handle);

	// start the shell
	c_shell();

	return 0;
}

void c_shell(){

	char home_dir[PATH_MAX];
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
			// execvp(argv[0], argv);
			printf("%s", argv[1]);

		}
		else{
			// printf("hello from parent\n");
			// wait for the command to finish if "&" is not present
			if(argv[i]==NULL) waitpid(pid, NULL, 0);
		}
	}
}

void get_command(char home_dir[]){
	// get command from user
	// NEED TO ADD ERROR HANDLING
	char hostname[HOST_NAME_MAX];
	char username[LOGIN_NAME_MAX];
	char cwd[PATH_MAX];
	gethostname(hostname, HOST_NAME_MAX);
	getlogin_r(username, LOGIN_NAME_MAX);
	getcwd(cwd, sizeof(cwd));

	int ii;
	for(ii = 0; ii<PATH_MAX; ii++){
		// printf("%c%c", cwd[ii], home_dir[ii]);
		if(cwd[ii]!=home_dir[ii]){
			break;
		}
	}
	// printf("%d", ii);

	if(i!=0){
		char wd[PATH_MAX];
		int k = 0;
		for(int j = ii; j<PATH_MAX; j++){
			wd[k] = cwd[j];
			k++;
		}
		printf("%s@%s~:%s>", username, hostname, wd);
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
	ptr = strtok(cmd, " ");
	while(ptr != NULL){
		//printf("%s\n", ptr);
		argv[i] = ptr;
		i++;
		ptr = strtok(NULL, " ");
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

void log_handle(int sig){
	//printf("[LOG] child proccess terminated.\n");
	FILE *pFile;
    pFile = fopen("log.txt", "a");
    if(pFile==NULL) perror("Error opening file.");
    else fprintf(pFile, "[LOG] child proccess terminated.\n");
    fclose(pFile);
}