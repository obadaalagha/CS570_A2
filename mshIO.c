#include "msh.h"

void begin_shell(int argc, char **argv) {
    printf("Number of ags: %d\n", argc);
    printf("argv[1]: %s\n", argv[1]);

    // int rc; /* Check return value for errors in making thread */
    //rc = pthread_create();
    //if(rc) {
    //    printf("ERROR: Return code from pthread_create() is: %d\n", rc);
    //}
    printf("Current username: %s\n", getlogin());
}
