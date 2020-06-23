/****************************************************************************** 
 * Obada Alagha cssc2115 819 852 274
 * Amiel Nava   cssc2124 824 264 864
 * CS570 Summer 2020
 * Project:    Assignment #2, msh microshell
 * Filename:   a1.h
 * Notes:      This is the header file used to define every library, constants,
 *             global variables, structures, and functions in order to have the
 *             program running.
 ******************************************************************************/

#ifndef MSH_H
#define MSH_H
#include <stdio.h>     /* For standard I/O */
#include <stdlib.h>    /* To use standard library functions */
#include <string.h>    /* To use string manipulation functions */
#include <unistd.h>    /* To use getlogin() */

#define BUFFER_LENGTH 100 /* Length of the input buffer */

/* Function prototype declarations */

void begin_shell(int argc);

int process_line(char* line);

void check_exit(char *input);

void create_argv(char *input);

void create_process(int argc, char **argv, int numPipes, int pipeLocs);

#endif
