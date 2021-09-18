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


int main(){
	// tie the handler to the SGNCHLD signal
	signal(SIGCHLD, log_handle);

	// start the shell
	c_shell();

	return 0;
}