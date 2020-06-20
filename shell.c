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
        char* refined = strtok_r(line,"|",&line);
        if((int)strlen(line) > 1) {
        printf("\nSize: %d",(int)strlen(refined));
	    printf("You entered: %s. Size = %d.\n", refined, (int)strlen(refined));
	    /* Check if user is quitting the microshell. If not, call function to filter and run input. */
//	    create_argv(refined);   
	    }
	}    
}

/* Rather than have a loop for tolower() and use strcmp, simply check each letter to get any combination of upper- and lower-case letters in the word exit (e.g. Exit, EXIT, exit, exIt) */
int check_exit(char *input) {
    int is_exit = strncmp(input,"exit",4) == 0 || strncmp(input,"EXIT",4) == 0;
    return !is_exit;
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
