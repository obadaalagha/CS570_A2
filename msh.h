/****************************************************************************** 
 * Obada Alagha cssc2115 819 852 274
 * Amiel Nava   cssc2124 824 264 864
 * CS570 Summer 2020
 * Project:    Assignment #2, msh microshell
 * Filename:   a1.h
 * Notes:      This is the header file used to define every library, constants,
 *             gloabal variables, structures and functions in order to have the
 *             program running.
 ******************************************************************************/

#include <stdio.h>     /* For standard I/O */
#include <stdlib.h>    /* To use standard library functions */
#include <unistd.h>    /* To use getlogin() */
//#include <pthread.h>   /* To multithread the program */
//#include <semaphore.h> /* To manage the threads of the program */

#ifndef MSH_H
#define MSH_H

/* Function prototype declarations */

void begin_shell(int argc, char **argv);

#endif