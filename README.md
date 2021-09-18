# Prajneya's Shell

This repository is a basic implementation of the Linux Shell, coded in C.

## Running the Shell

1. Run the ```make``` command
2. Run ```./main``` to enter the shell

## Usage

The shell includes implementation of the following functionalities:

1. ```display```: A shell prompt displaying hostname, username alongwith the working directory is displayed.

2. ```cd```: The change directory, or cd command is implemented. Includes functionalities for ```.```, ```..```, ```~```, ```-``` as well.

3. ```echo```: Prints whatever input is given after the keyword ```echo```.

4. ```pwd```: Prints the present working directory.

5. ```ls```: Includes the implementation of the listing command, with the inclusion of -l and -a flags. Handles multiples directories as well alongwith all combinations of flags.

6. ```pinfo```: Used to display process stats of a process (can be self or a pid)

7. ```repeat```: Repeats any command for a specified number of times

8. ```history```: Records a history of 20 commands and can display the usage of upto past 10 commands at a time.

9. ```foreground and background processes```: runs process marked with ```&``` in the background and rest in the foreground and displays appropriate messages for the same

10. ```others```: All other commands are implemented using the ```execvp``` command.

## File Structure

1. ```main.c```: For starting the shell

2. ```cd.c```: For handling the cd process

3. ```echo.c```: For handling the echo process

4. ```helper.c```: Utility functions to loop/display/call commands

5. ```headers.h```: All necessary header files and global variables

6. ```history.c```: For handling history commands

7. ```ls.c```: For handling the ls command

8. ```makefile```: For compiling the program

9. ```pinfo.c```: For handling the pinfo process

10. ```pwd.c```: For handling the pwd process

11. ```repeat.c```: For handling the repeat process