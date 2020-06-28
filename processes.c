/*******************************************************************************
 * Obada Alagha cssc2115 819 852 274
 * Amiel Nava   cssc2124 824 264 864
 * CS570 Summer 2020
 * Project:    Assignment #2, msh microshell
 * Filename:   processes.c
 * Notes:      Contains methods that receive the filtered input from shell.c to
 *             launch processes and/or handle pipes.
 ******************************************************************************/

#include "header.h"

/*******************************************************************************
 * Function: process_execs
 * Notes:    Process the executables. Check if the number of executables within
 *           the given input is one or greater. If one, we can begin a new
 *           process by passing to the run_exec method after some error
 *           checking. If more than one (and ergo needing pipes), we send to
 *           process_pipes to handle the piping.
 *           WRITTEN BY AMIEL.
 ******************************************************************************/
void process_execs(struct executable *exec, int numExecs) {
    if(numExecs == 1) {
        pid_t pid;
        int status;
        /* Fork a child process                                               */
        if ((pid = fork()) < 0) {
            perror("*** ERROR: Failed to fork child process.\n");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            run_exec(exec, 0);
        } else {
            while(wait(&status) != pid);
        }
    } else {
        process_pipes(exec, numExecs);
    }
}

/*******************************************************************************
 * Function: process_pipes
 * Notes:    Begin by error checking and mkaing sure processes can be run
 *           properly. Fork a child process. If successful, replace stdout with
 *           the write end of a pipe. After error checking and getting the
 *           proper number of pipes, call run_exec to run the process. Make sure
 *           to open the read end, and, eventually close both ends of the pipe.
 *           WRITTEN BY AMIEL.
 ******************************************************************************/
void process_pipes(struct executable *exec, int numExecs) {
    int pipefd[2];      /* file descriptor to read from pipe write(1)/read(0) */
    pid_t pid;          /* Process id                                         */
    int fd_in = 0;      /* File descriptor input                              */
    int exe_num = 0;    /* The current exec handling in the array str of exec */
    int status;         /* Status is set to NULL for the wait function        */


    while(exe_num < numExecs) {
        /* Pass the file descriptor to the pipe */
        if(pipe(pipefd) < 0) {
            perror("*** ERROR: failed to create pipe.\n");
            exit(EXIT_FAILURE);
        }
        if((pid = fork()) < 0) {
            perror("*** ERROR: failed to fork child process.\n");
            exit(EXIT_FAILURE);
        }
        /* Child Process                                                      */
        else if(pid == 0) {
            /* Replace stdout w/ the write end of the pipe                    */
            if(dup2(fd_in, STDIN_FILENO) < 0) {
                perror("Error occur in dup2()");
                exit(EXIT_FAILURE);
            }
            /* If we have not reached the end of the pipe                     */
            if((exe_num + 1) != numExecs) {
                /* Replace stdin w/ the read end of the pipe                  */
                if(dup2(pipefd[WRITE], STDOUT_FILENO) < 0) {
                    perror("Error occur in dup2()");
                    exit(EXIT_FAILURE);
                }
            }
            close(pipefd[READ]);   /* Close read to pipe in child             */
            run_exec(exec, exe_num);
        }
        /* Parent Process                                                     */
        else {
            wait(&status);      /* Waits until one of its children terminates */
            close(pipefd[WRITE]);   /* Close write to pipe in parent          */
            fd_in = pipefd[READ];  /* Get file descriptor input of read       */
            exe_num++;       /* Go the next executable when this exec id done */
        }
    }
}

/*******************************************************************************
 * Function: run_exec
 * Notes:    Run the the executable using execvp. If it fails to start, throw an
 *           error and quit attempting to run it.
 *           WRITTEN BY AMIEL AND OBADA.
 ******************************************************************************/
void run_exec(struct executable *exec, int index) {
        if(execvp(*exec[index].arg_list, exec[index].arg_list) < 0) {
            perror("***ERROR: exec failed.\n");
            exit(EXIT_FAILURE);
        }
}
