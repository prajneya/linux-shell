#ifndef __HELPER_H
#define __HELPER_H

void get_command();								// get command string from the user
void convert_command();						// convert the command string to the required format by execvp()
int check_command(char *cmd[], int n_args);
void c_shell();								// to start the shell
void log_handle(int sig);			// signal handler to add log statements
void change_output();

#endif