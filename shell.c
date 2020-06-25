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
    /* Variables to end for loop and buffer for the command line input.       */
    int not_exit;   /* Flag to see if user entered exit                       */
    char *usr_id = getlogin();  /* get user id                                */
    char input[BUFFER_LENGTH];  /* input storage                              */

    /* Do while loop which runs the actual command line.                      */
    do{
	    /* Display current user name                                          */
        printf("%s%c ",usr_id,'%');
	    /* Get user input  */
	    fgets(input, BUFFER_LENGTH, stdin);/* fgets() includes  \n            */
        input[strlen(input)-1] = '\0';    /* Flush out the new line           */
        not_exit = process_line(input); /* Ret 1 if user did not entered exit */
    }while(not_exit);                   /* Prompts until user enters exit     */

}

int process_line(char* line){
    int not_exit = check_exit(line); /* check if user entered exit            */
    /* Skip line inspection if user entered exit                              */
    if(not_exit){
        int argc = 0;                   /* Count the num of args              */
        int index = 0; /* To use with our structure array of executables      */
        int num_of_exec = 1;       /* To count num of executables             */
        char *ptr = line;   /* ptr to line so we can use ptr again            */
        
        /* Search in input and get the number of executables for our struct   */
        while(*ptr++ != '\0'){
            if(*ptr == '|') /* Pipe found                                     */
                num_of_exec++;
        }
        ptr = NULL; /* Disregard our pointer since we are done with it        */
        
        /* Initiate our structure with the number of executables found        */
        struct executable exec[num_of_exec];

        /* Parse the line input                                               */ 
        while(*line != '\0'){
            /* Remove all leading spaces (trim) & pipe symbols                */
            while(*line == ' ' || *line == '\t' || *line == '|'){
                /* If pipe encountered, reset arg counter and increment index */
                if(*line == '|'){
                    exec[index].arg_list[argc] = '\0';  /* Mark end           */
                    argc = 0;
                    index++;
                }
                *line++ = '\0'; /* End string when a space/pipe is encountered*/
            }
            /* Store argument's data into our structure                       */
            exec[index].arg_list[argc] = line;
            argc++;
            exec[index].arg_count = argc;

            /* Move through each character in a word  until the next word     */
            while(*line != '\0' && *line != ' ' && *line != '\t' && *line != '|'){
                line++;
            }
        }
        /* Mark the end of the list to be used with our exec function         */
        exec[index].arg_list[argc] = '\0';
        
        /******************************* DEBUG ********************************/
        printf("Num of executables:%d\n",num_of_exec);
        int i,j,num_of_args;
        for(i=0; i < num_of_exec; i++){
            num_of_args = exec[i].arg_count;
            printf("Num of args: %d\n",num_of_args);
            for(j=0;j<num_of_args;j++){
                printf("%s ",exec[i].arg_list[j]);
            }
            printf("\n");
        }
        /**********************************************************************/

        // Uncomment when function takes struct arg
        // You can use exec[index].arg_list for now 
        // Example:" a | ls -l | c" to run ls -l send exec[1].arg_list
        // process_execs(exec[0].arg_list);/* Process executable arguments    */
    }
    return not_exit;
}

/* Rather than have a loop for tolower(),  use strcmp, simply check each      *
 * letter to get any combination of upper- and lower-case letters in the word *
 * exit (e.g. Exit, EXIT, exit, exIt)                                         */
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
