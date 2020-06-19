########################################################
# Obada Alagha cssc2115 819 852 274
# Amiel Nava   cssc2124 824 264 864
# CS570 Summer 2020
# Assignment #2, msh microshell
# Filename: Makefile
########################################################

EXEC = pam
FILES = main.c shell.c processes.c
CC = gcc
#LFLAGS = -o
CFLAGS = -c

OBJECTS = $(FILES:.c=.o)

$(EXEC):$(OBJECTS)
	$(CC) -o $(EXEC) $(OBJECTS)
	rm -f *.o

.c.o:
	$(CC) $(CFLAGS) $<

clean:
	rm -f *.o $(EXEC)

###################[ EOF: Makefile ]####################
