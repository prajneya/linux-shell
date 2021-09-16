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

extern char cmd[MAX_SIZE_CMD];				// string holder for the command
extern char *argv[MAX_SIZE_ARG];			// an array for command and arguments
extern pid_t pid;										// global variable for the child process ID
extern char i;								// global for loop counter
extern char home_dir[PATH_MAX];			// global variable for home directory

#endif