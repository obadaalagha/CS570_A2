/******************************************************************************
 * Obada Alagha cssc2115 819 852 274
 * Amiel Nava   cssc2124 824 264 864
 * CS570 Summer 2020
 * Project:    Assignment #2, msh microshell
 * Filename:   shell.c
 * Notes:      
 ******************************************************************************/

#include "header.h"

void begin_shell(int argc) {
    /* Variables to end for loop and buffer for the command line input. */
    int not_exit;   /* Flag to see if user entered exit */
    char *usr_id = getlogin();  /* get user id */
    char input[BUFFER_LENGTH];

    /* Do while loop which runs the actual command line. */
    do{
	    /* Display current user name  and specifiy you're running msh */
        printf("%s@msh%c ",usr_id,'%');
	    /* Get user input  */
	    fgets(input, BUFFER_LENGTH, stdin);
        not_exit = process_line(input); /* Returns 1 if user did not entered exit */
    }while(not_exit);                   /* Prompts until user enters exit */

}

int process_line(char* line){
    int not_exit = check_exit(line); /* check if user entered exit */
    /* Skip line inspection if user entered exit */
    if(not_exit){
        char *argv[MAX_ARGS];
        int argc = 0;                   /* Count the num of args              */
        int num_of_pipes = 0;
        char *ptr = line;
        /* Get the number of pipes to instantiate 2D array                    */
        while(*ptr++ != '\0'){
            if(*ptr == '|')
                num_of_pipes++;
        }
        ptr = NULL;
        /* Parse the line input                                               */ 
        while(*line != '\0'){
            /* Remove all white trailing spaces aka trimming & pipe symbols   */
            while(*line == ' ' || *line == '\t' || *line == '|'){
               if(*line == '|'){
                    //do something
               }
               *line++ = '\0'; /* End string when a space/pipe is encountered */
            }
            argv[argc] = line++;  /* Store trimmed argument                   */
            argc++;
            /* Move through each character in a word  until the next word     */
            while(*line != '\0' && *line != ' ' && *line != '\t' && *line != '|'){
                line++;
            }
        }
        argv[argc] = '\0';
        printf("Num of pipes:%d\n",num_of_pipes);
        process_execs(argv);
    }
    return not_exit;
}

/* Rather than have a loop for tolower() and use strcmp, simply check each letter to get any combination of upper- and lower-case letters in the word exit (e.g. Exit, EXIT, exit, exIt) */
int check_exit(char *input) {
    int is_exit = strncmp(input,"exit",4) == 0 || strncmp(input,"EXIT",4) == 0;
    return !is_exit;
}

void process_execs(char **argv){
    pid_t proc;
    int status;

    if ( (proc = fork()) < 0){
        printf("*** ERROR: forking child process failed\n");
        exit(1);
    }
    else if (proc ==0){
        if (execvp(*argv,argv) <0 ){
            printf("***ERROR: exec failed\n");
            exit(1);
        }
    }
    else {
        while(wait(&status) != proc);
    }
}


void create_argv(char *input) {
    /* Declare argc & longest. Argc is 1 by default, since there is at least one argument. Longest is to declare argv */
    int argc = 1;
    int longest = 0;

    /* For use later - the number of pipes and the locations of the pipes relative to argv */
    int numPipes = 0;
    int pipeLoc[10];

    int i;
    for(i = 0; i < (int)strlen(input); i++) {
	if(input[i] == ' ') {
	    argc++;
	    if ((i - longest) > longest) {
		longest = i;
	    }
        } else if (input[i] == ' ') {
	    numPipes++;
	    pipeLoc[numPipes] = i;
	}
    }

    /* Declare argc with values obtained prior */
    //char argv[argc][longest];
    char **argv;

    printf("%s\n", "Before making argv");
    /* Loop through and split the output into an array similar to argc */
    int j;
    char *token;
    for(i = 0; i < argc; i++) {
	token = strtok_r(input, " ", &input);
	printf("i: %d\n", i);
        for(j = 0; j < (int)strlen(token); j++) {
	    printf("j: %d\n", j);
	    //printf("%c\n", token[j]);
	    argv[i][j] = (char)token[j];
	}
	//printf("%s\n", argv[i]);
    }

    printf("%s\n", "Before passing");
    /* Pass results into create_process */
//    create_process(argc, argv, numPipes, pipeLoc);
}
