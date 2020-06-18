#include "msh.h"

void begin_shell(int argc) {
    if (argc > 1) {
	printf("%s\n\n", "Please input your command line arguments within the program.");
    }

    int condition = 1;
    char input[100];

    while(condition == 1) {
	printf("%s@msh$", getlogin());
	fgets(input, 100, stdin);

	char *refined = strtok(input, "\n");

	printf("You entered: %s. Size = %d.\n", refined, (int)strlen(refined));

	checkExit(refined);

	int numArgs;
	int argv;
    }
}


/* Rather than have a loop for tolower() and use strcmp, simply check each letter to get any combination of upper- and lower-case letters in the word exit (e.g. Exit, EXIT, exit, exIt) */
void checkExit(char *input) {
    if(((input[0] == 'e') || (input[0] == 'E')) 
    && ((input[1] == 'x') || (input[1] == 'X'))
    && ((input[2] == 'i') || (input[2] == 'I')) 
    && ((input[3] == 't') || (input[3] == 'T')) 
    && ((int)strlen(input) == 4)) {
	exit(0);
    }
}
