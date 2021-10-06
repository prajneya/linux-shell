#ifndef __HEADERS_H
#define __HEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>
#include <dirent.h>
#include <errno.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <fcntl.h>

#define	MAX_SIZE_CMD	256
#define	MAX_SIZE_ARG	16
#define MAX_JOBS 128
#define MAX_HISTORY_COUNT 20

struct job{
	int pid;
	char job_name[MAX_SIZE_ARG];
};

extern char cmd[MAX_SIZE_CMD];				// string holder for the command
extern char *argv[MAX_SIZE_ARG];			// an array for command and arguments
extern pid_t pid;										// global variable for the child process ID
extern char i;								// global for loop counter
extern char home_dir[PATH_MAX];			// global variable for home directory
extern char prev_dir[PATH_MAX];
extern int process_count;
extern struct job jobs[MAX_JOBS];
extern int up_history;

extern int input_flag;
extern int output_flag;
extern char input_path[MAX_SIZE_CMD];
extern char output_path[MAX_SIZE_CMD];

extern int saved_stdout;
extern int saved_stdin;

extern int file_piper[2];
extern int s_file_piper[2];

#endif