#include "headers.h"
#include "helper.h"

char cmd[MAX_SIZE_CMD] = { '\0' };
char *argv[MAX_SIZE_ARG] = { '\0' };
pid_t pid;
char i;
char home_dir[PATH_MAX] = { '\0' };
char prev_dir[PATH_MAX] = { '\0' };
int process_count = -1;
struct job jobs[MAX_JOBS];
int up_history = 0;

int input_flag = 0;
int output_flag = 0;
char input_path[MAX_SIZE_CMD] = { '\0' };
char output_path[MAX_SIZE_CMD] = { '\0' };

int saved_stdout = 0;
int saved_stdin = 0;

int file_piper[2];

int piping_flag = 0;

int main(){
	pipe(file_piper);

	// signal(SIGINT, ctrlcHandler);
 //    signal(SIGTSTP, ctrlzHandler);
	// tie the handler to the SGNCHLD signal
	signal(SIGCHLD, log_handle);

	saved_stdout = dup(1);
	saved_stdin = dup(0);

	// start the shell
	c_shell();

	return 0;
}