# MAKEFILE FOR COMPILING CODE FILES OF TRAFFIC GAME
# AUTHOR: PRASHANTHA FERNANDO
# LAST EDITED: 22/10/23

# MAKEFILE VARIABLES
CC = gcc
EXEC = traffic
CFLAGS = -Wall -ansi -pedantic -Werror
OBJ = traffic.o file_io.o map.o movement.o linked_list.o terminal.o

# BINARY FILE
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# OBJECT FILES
traffic.o: traffic.c game_structures.h file_io.h map.h movement.h linked_list.h terminal.h
	$(CC) $(CFLAGS) traffic.c -c
	
file_io.o: file_io.c game_structures.h file_io.h map.h
	$(CC) $(CFLAGS) file_io.c -c

map.o: map.c game_structures.h map.h
	$(CC) $(CFLAGS) map.c -c
	
movement.o: movement.c game_structures.h map.h movement.h linked_list.h
	$(CC) $(CFLAGS) movement.c -c
	
linked_list.o: linked_list.h
	$(CC) $(CFLAGS) linked_list.c -c
	
terminal.o: terminal.c terminal.h
	$(CC) $(CFLAGS) terminal.c -c

# CLEAN BINARY AND OBJECT FILES	
clean:
	rm $(EXEC) $(OBJ)
