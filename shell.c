#include "header.h"

void begin_shell(int argc) {
    /* User inputted args when launching the microshell. Let them know where to properly put args. */
    if (argc > 1) {
	printf("%s\n\n", "Please input your command line arguments within the program.");
    }

    /* Variables to end for loop and buffer for the command line input. */
    int condition = 1;
    char input[BUFFER_LENGTH];

    /* While loop which runs the actual command line. */
    while(condition == 1) {
	/* Display current user name (currently logged into edoras) and specificy you're running msh */
	printf("%s@pam-msh$ ", getlogin());

	/* Get user input. Cut off extra length from buffer ONLY if the user typed something. */
	fgets(input, BUFFER_LENGTH, stdin);

	if((int)strlen(input) > 1) {
	    char *refined = strtok(input, "\n");

	    printf("You entered: %s. Size = %d.\n", refined, (int)strlen(refined));

	    /* Check if user is quitting the microshell. If not, call function to filter and run input. */
	    checkExit(refined);
	    create_argv(refined);   
	}
    }
}


/* Rather than have a loop for tolower() and use strcmp, simply check each letter to get any combination of upper- and lower-case letters in the word exit (e.g. Exit, EXIT, exit, exIt) */
void checkExit(char *input) {
    if(((input[0] == 'e') || (input[0] == 'E')) 
    && ((input[1] == 'x') || (input[1] == 'X'))
    && ((input[2] == 'i') || (input[2] == 'I')) 
    && ((input[3] == 't') || (input[3] == 'T')) 
    && ((int)strlen(input) == 4)) {
        printf("%s\n", "You have exited the msh microshell. Goodbye.");
	exit(0);
    }
}

void create_argv(char *input) {
    /* Declare argc & longest. Argc is 1 by default, since there is at least one argument. Longest is to declare argv */
    int argc = 1;
    int longest = 0;
    
    int i;
    for(i = 0; i < (int)strlen(input); i++) {
	if(input[i] == ' ') {
	    argc++;
	    if ((i - longest) > longest) {
		longest = i;
	    }
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
	    argv[i][j] = token[j];
	}
	//printf("%s\n", argv[i]);
    }

    printf("%s\n", "Before passing");
    /* Pass results into create_process */
    create_process(argc, argv);
}
