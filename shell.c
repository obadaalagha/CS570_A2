/*******************************************************************************
 * Obada Alagha cssc2115 819 852 274
 * Amiel Nava   cssc2124 824 264 864
 * CS570 Summer 2020
 * Project:    Assignment #2, msh microshell
 * Filename:   shell.c
 * Notes:      File that contains the methods that begin the shell and take in
 *             and filter user input, in order to pass on to functions which
 *             launch the processes in processes.c.
 ******************************************************************************/

#include "header.h"

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
void begin_shell(int argc) {
    if(argc > 1) printf("%s\n\n", "Please input your command line arguments within the program itself.");

    /* Variables to end for loop and buffer for the command line input.       */
    int not_exit;   /* Flag to see if user entered exit                       */
    char input[BUFFER_LENGTH];  /* input storage                              */
    char host[30], cwd[50];   /* Buffers for hostname and current directory   */
    gethostname(host, sizeof(host)); /* Getting hostname                      */
    getcwd(cwd, sizeof(cwd));        /* Getting current directory             */

    /* Do-while loop which runs the actual command line.                      */
    do {
	      /* Display current user name, hostname, and current directory         */
        printf("\x1B[32;1m%s@%s\x1B[0m:\x1B[34;1m%s\x1B[0m%c ", getlogin(), host, cwd, '%');
        fgets(input, BUFFER_LENGTH, stdin); /* Get user input                 */
        input[strlen(input) - 1] = '\0';    /* Flush out \n saved by fgets()  */
        not_exit = parse_input(input);      /* Return 1 if user didn't exit   */
    } while(not_exit);                      /* Prompts until user enters exit */
}

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
int parse_input(char* input) {
    int not_exit = check_exit(input); /* Check if user exited & skip if so.   */

    /* Skip input parsing if user entered exit                                */
    if(not_exit) {
        int argc = 0;        /* Count the num of args                         */
        int index = 0;       /* To use with our struct array of executables   */
        int numExecs = 1;    /* Number of executables, default is 1           */
        char *ptr = input;   /* Pointer to use to iterate input string        */

        /* Search in input and get the number of executables for our struct   */
        while(*ptr++ != '\0') {
            if(*ptr == '|') numExecs++; /* Found a pipe = than one executable */
        }
        ptr = NULL; /* Discard our pointer since we are done with it          */

        /* Initiate our structure with the number of executables found        */
        struct executable exec[numExecs];

        /* Parse the command line input                                       */
        while(*input != '\0') {
            /* Remove all leading spaces (trim) & pipe symbols                */
            while(*input == ' ' || *input == '\t' || *input == '|') {
                /* If pipe encountered, reset arg counter and increment index */
                if(*input == '|') {
                    exec[index].arg_list[argc] = '\0';  /* Mark end           */
                    argc = 0;
                    index++;
                }
                *input++ = '\0'; /* Add \0 when a space/pipe is encountered   */
            }
            /* In case the user enters spaces at the end before pressing enter*/
            if(*input != '\0') {
                /* Store argument's data into our structure                   */
                exec[index].arg_list[argc] = input;
                argc++;
                exec[index].arg_count = argc;
            }
            /* Move through each character in a word  until the next word     */
            while(*input != '\0' && *input != ' ' && *input != '\t'
                  && *input != '|') {
                input++;
            }
        }
        /* Mark the end of the list to be used with our exec function         */
        exec[index].arg_list[argc] = '\0';

        /* Print out debugging info upon user request. Else, carry on process */
        if((strncmp(input, "debug", 5) == 0) && (int)strlen(input) == 5) {
            debug(exec, argc, numExecs);
        } else {
            process_execs(exec, numExecs);
        }
    }
    return not_exit;
}

/*******************************************************************************
 * Function: check_exit
 * Notes:    Checks if the user entered "exit" by checking both the actual
 *           string and making sure that they typed exit, not exit0, for
 *           instance. If yes, returns 0.
 *           WRITTEN BY OBADA AND AMIEL.
 ******************************************************************************/
int check_exit(char *input) {
    if((strncmp(input, "exit", 4) == 0) && (int)strlen(input) == 4) return 0;
    return 1;
}

/*******************************************************************************
 * Function: debug
 * Notes:    Debugger.
 *           WRITTEN BY AMIEL AND OBADA.
 ******************************************************************************/
void debug(struct executable* exec, int numArgs, int numExecs) {
    printf("Num of executables:%d\n", numExecs);
    int i, j;
    for(i = 0; i < numExecs; i++) {
        numArgs = exec[i].arg_count;
        printf("Num of args: %d\n", numArgs);
        for(j = 0; j < numArgs; j++) {
            printf("%s ", exec[i].arg_list[j]);
        }
        printf("\n");
    }
}
