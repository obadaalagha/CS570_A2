#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    
    int row = sizeof(argv) / sizeof(argv[0]);
    int column = sizeof(argv[0])/sizeof(argv[0][0]);

    int i, j;
    for(i = 0; i < argc; i++) {
	//for(j = 0; j < column; j++) {
	    printf("%c", argv[i]);
	//}
    }
    /*
    char input[100];

    printf("\ntype something: %s", "here:");
    fgets(input, 100, stdin);
    printf("len: %d\n", (int)strlen(input));
    */
    return 0;
}
