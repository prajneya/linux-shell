# Prajneya's Shell

This repository is a basic implementation of the Linux Shell, coded in C.

## Running the Shell

1. Run the ```make``` command
2. Run ```./main``` to enter the shell

## Usage

The shell includes implementation of the following functionalities:

1. ```display```: A shell prompt displaying hostname, username alongwith the working directory is displayed.

2. ```cd```: The change directory, or cd command is implemented. Includes functionalities for ```.```, ```..```, ```~```, ```-``` as well.

* ``` bash
    cd
    cd .
    cd ..
    cd ~
    cd <directory>
    ```

3. ```echo```: Prints whatever input is given after the keyword ```echo```.

* ```bash
    echo <"Hello World">
    ```

4. ```pwd```: Prints the present working directory.

5. ```ls```: Includes the implementation of the listing command, with the inclusion of -l and -a flags. Handles multiples directories as well alongwith all combinations of flags.

* ```bash
    ls
    ls -a
    ls -l
    ls -al
    ls -la
    ls <directory>
    ```

6. ```pinfo```: Used to display process stats of a process (can be self or a pid)

* ```bash
    pinfo
    pinfo <pid>
    ```

9. ```foreground processes```: Processes that require the terminal to halt until their completion. Example:

* ```bash
    vi
    gedit
    sleep
    ```

9. ```background processes```: Processes that run simultaneuosly without interrupting the terminal. Example:

 * ```bash
    sleep &
    gedit &
    firefox &
    ```

11. ```others```: All other commands are implemented using the ```execvp``` command.

12. ```Input and Output Redirection```: Using the symbols <, > and >>, the output of commands, usually written to stdout, ​can be redirected to another file, or the input taken from a file other 	than ​stdin​. Both input and output redirection can be used simultaneously.

* ```bash
    cat file1.txt > file2.txt
    sort < sort.txt > sorted.txt
    sort < sort.txt >> sorted.txt
    ```

13. ```Piping commands```: Pipes two or more commands together. Example:

* ```bash
    cat test.txt | head -2
    cat test.txt | wc | wc | wc
    ```

14. ```Piping with input output redirection```: 

* ```bash
    cat < in.txt | wc -l > lines.txt
    ```

15. ```jobs```: Prints all the jobs that are running in the background along with their status:

 * ```bash
    jobs
    ```

16. ```sig```: Sends a signal to  a particular job number

  * ```bash
    sig 1 9
    ```

17. ```fg```: Brings the running or stopped background job corresponding to ​job number​ to the foreground, and changes its state to ​running.

* ```bash
    fg 1
    ```

18. ```bg```: Changes the state of a stopped background job to running (in the background).

* ```bash
    bg 1
    ```

19. The terminal also supports

  * CTRL + Z: Pushes the running foreground process to the background and stops it.

  * CTRL + C: Stops the running foreground process

  * CTRL + D: Logs out of the shell

## File Structure

1. ```main.c```: For starting the shell

2. ```bg.c```: For handling the bg process

2. ```cd.c```: For handling the cd process

3. ```echo.c```: For handling the echo process

2. ```fg.c```: For handling the bg process

4. ```helper.c```: Utility functions to loop/display/call commands and handle I/O Redirection alongwith pipes

5. ```headers.h```: All necessary header files and global variables

6. ```history.c```: For handling history commands

2. ```jobs.c```: For handling the jobs process

7. ```ls.c```: For handling the ls command

8. ```makefile```: For compiling the program

9. ```pinfo.c```: For handling the pinfo process

10. ```pwd.c```: For handling the pwd process

11. ```repeat.c```: For handling the repeat process

2. ```sig.c```: For handling the sig (sending signal) process
