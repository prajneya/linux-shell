#ifndef __HELPER_H
#define __HELPER_H

void get_command();								// get command string from the user
void convert_command();						// convert the command string to the required format by execvp()
int check_command(char *cmd[], int n_args, int output_flag, int input_flag, char* output_path, char *input_path);
void c_shell();								// to start the shell
void log_handle(int sig);			// signal handler to add log statements

#endif