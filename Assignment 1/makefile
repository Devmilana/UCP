# MAKEFILE FOR COMPILING CODE FILES OF TRAFFIC GAME
# AUTHOR: PRASHANTHA FERNANDO
# LAST EDITED: 19/09/23

# MAKEFILE VARIABLES
CC = gcc
EXEC = traffic
CFLAGS = -Wall -ansi -pedantic -Werror
OBJ = traffic.o validation.o map.o movement.o terminal.o random.o newSleep.o

# BINARY FILE
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# OBJECT FILES
traffic.o: traffic.c validation.h map.h movement.h terminal.h random.h newSleep.h
	$(CC) $(CFLAGS) traffic.c -c
	
validation.o: validation.c validation.h 
	$(CC) $(CFLAGS) validation.c -c
	
map.o: map.c map.h movement.h random.h
	$(CC) $(CFLAGS) map.c -c
	
movement.o: movement.c movement.h
	$(CC) $(CFLAGS) movement.c -c
	
terminal.o: terminal.c terminal.h 
	$(CC) $(CFLAGS) terminal.c -c
	
random.o: random.c random.h 
	$(CC) $(CFLAGS) random.c -c
		
newSleep.o: newSleep.c newSleep.h 
	$(CC) $(CFLAGS) newSleep.c -c

# CLEAN BINARY AND OBJECT FILES	
clean:
	rm $(EXEC) $(OBJ)
