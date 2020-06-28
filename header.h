/*******************************************************************************
 * Obada Alagha cssc2115 819 852 274
 * Amiel Nava   cssc2124 824 264 864
 * CS570 Summer 2020
 * Project:    Assignment #2, msh microshell
 * Filename:   header.h
 * Notes:      This is the header file used to include libraries, define
 *             constants, global variables, structures, and function prototypes
 *             in order to get the program running.
 *             LAYOUT BY OBADA, ADDITIONS BY AMIEL AS NEEDED.
 ******************************************************************************/

#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>     /* For standard I/O */
#include <stdlib.h>    /* To use standard library functions */
#include <string.h>    /* To use string manipulation functions */
#include <unistd.h>    /* To use getlogin(), gethostname(), and getcwd() */
#include <sys/wait.h>  /* To use the function wait() */

#define BUFFER_LENGTH 384 /* Length of the input buffer */
#define MAX_ARGS 64       /* Maximum length of arguments */
#define READ 0            /* For pipes */
#define WRITE 1           /* For pipes */

/*******************************************************************************
 * Structure to store string arguments and argument count for each executable
 * the user enters in a pipe or enters a single executable. This structure will
 * hold the list needed to call exec functions to the system.
 ******************************************************************************/
struct executable {
    char *arg_list[MAX_ARGS];
    int arg_count;
};

/*                      Function prototype declarations                       */

/*                                 Shell.c                                    */
/*******************************************************************************
 * Function: begin_shell
 * Notes:    If user inputted something when launching the program, remind them
 *           to input it within the program itself. Otherwise, declare flags and
 *           buffers to store relevant data such as the user input, the hostname
 *           and current directory, and provide a working shell which takes in
 *           the user input. Done within a do-while loop that calls the
 *           parse_input method which parses input for proper handling.
 *           WRITTEN BY OBADA AND AMIEL.
 ******************************************************************************/
void begin_shell(int argc);

/*******************************************************************************
 * Function: parse_input
 * Notes:    Takes in the input given passed by begin_shell and processes it.
 *           Declares struct that holds the list and total number of arguments
 *           of each individual token (a command and its arguments before a
 *           pipe). Removes symbols after tokenization. Finally, checks if user
 *           inputted a third inbuilt command (debug), and, if not, sends
 *           input for proper processing.
 *           WRITTEN BY AMIEL AND OBADA.
 ******************************************************************************/
int parse_input(char* line);

/*******************************************************************************
 * Function: check_exit
 * Notes:    Checks if the user entered "exit" by checking both the actual
 *           string and making sure that they typed exit, not exit0, for
 *           instance. If yes, returns 0.
 *           WRITTEN BY OBADA AND AMIEL.
 ******************************************************************************/
int check_exit(char *input);

/*******************************************************************************
 * Function: debug
 * Notes:    Debugger.
 *           WRITTEN BY OBADA AND AMIEL.
 ******************************************************************************/
void debug(struct executable* exec, int numArgs, int numExecs);

/*                               Processes.c                                  */
/*******************************************************************************
 * Function: process_execs
 * Notes:    Process the executables. Check if the number of executables within
 *           the given input is one or greater. If one, we can begin a new
 *           process by passing to the run_exec method after some error
 *           checking. If more than one (and ergo needing pipes), we send to
 *           process_pipes to handle the piping.
 *           WRITTEN BY AMIEL.
 ******************************************************************************/
void process_execs(struct executable *exec, int );

/*******************************************************************************
 * Function: process_pipes
 * Notes:    Begin by error checking and mkaing sure processes can be run
 *           properly. Fork a child process. If successful, replace stdout with
 *           the write end of a pipe. After error checking and getting the
 *           proper number of pipes, call run_exec to run the process. Make sure
 *           to open the read end, and, eventually close both ends of the pipe.
 *           WRITTEN BY AMIEL.
 ******************************************************************************/
void process_pipes(struct executable *exec, int numExecs);

/*******************************************************************************
 * Function: run_exec
 * Notes:    Run the singular executable received from process_execs. If it
 *           fails to fork, throw an error and quit attempting to run it.
 *           WRITTEN BY AMIEL AND OBADA.
 ******************************************************************************/
void run_exec(struct executable *exec, int index);

#endif
