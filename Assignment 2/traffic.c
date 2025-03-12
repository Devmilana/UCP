/*******************************************************************************************************************
  
 * traffic.c

 * AUTHOR: PRASHANTHA FERNANDO
 
 * LAST EDITED: 22/10/23
 
 * DESCRIPTION: Main c file of traffic game that contains game loop and calls upon all other files for 
 		        game functionality execution
 
*******************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "game_structures.h"
#include "linked_list.h"
#include "movement.h"
#include "terminal.h"
#include "file_io.h"
#include "map.h"

/* Main traffic game function */
int main(int argc, char **argv) 
{
    char *error;
    char **map;
    char **backgroundMap;
    char input;
    int mapRows, mapCols, i, j;
    int isGameOver = 0;
    GameCharacters gameCharacters;
    GameState *initialState;

    /* Initialise linkedlist to track player moves */
    LinkedList *movesList = initialiseLinkedList();

    /* Checks for the correct number of command line arguments */
    if (argc != 2) 
    {
        printf("\nInvalid parameters entered for running game!\n");
        printf("\nUsage: ./traffic <map_file_name>\n");
        printf("\nExample usage execution: ./traffic game_1.txt\n\n");
        return 1;
    }

    map = NULL;
    backgroundMap = NULL;

    /* Reads map file */
    error = readMapFile(argv[1], &mapRows, &mapCols, &map, &backgroundMap, &gameCharacters);
    if (error != NULL) 
    {
        printf("\n");
        printf("%s\n\n", error);
        free(error);
        return 1;
    }

    /* Displays the initial game map */
    printMap(map, backgroundMap, mapRows, mapCols);
    
    /* Allocate memory saves initial game state */
    initialState = (GameState *)malloc(sizeof(GameState));
    initialState->player = gameCharacters.player;
    initialState->car = gameCharacters.car;
    initialState->map = allocateMap(mapRows, mapCols);
    for (i = 0; i < mapRows; i++) 
    {
        for (j = 0; j < mapCols; j++) 
        {
            initialState->map[i][j] = map[i][j];
        }
    }

    insertFirst(movesList, initialState); /* Store the initial game state in the moves list */

    /* Main game loop */
    while (!isGameOver)
    {
        disableBuffer(); 
        scanf(" %c", &input); /* Get player's movement input */
        enableBuffer();

        /* Check for valid movement key entry */
        if (input == 'w' || input == 'a' || input == 's' || input == 'd') 
        {
            /* Move the car and player */
            moveCar(&gameCharacters.car, map, mapRows, mapCols);
            movePlayer(input, &gameCharacters.player, map, backgroundMap, mapRows, mapCols, gameCharacters.car, movesList);

            /* Checks for collisions or if player reached the goal */
            if (checkCollision(gameCharacters.player, gameCharacters.car))
            {
                printMap(map, backgroundMap, mapRows, mapCols);
                printf("You lose!\n");
                isGameOver = 1;
            }
            else if (gameCharacters.player.row == gameCharacters.goal.row && gameCharacters.player.col == gameCharacters.goal.col)
            {
                printMap(map, backgroundMap, mapRows, mapCols);
                printf("You win!\n");
                isGameOver = 1;
            }
            else
            { 
                printMap(map, backgroundMap, mapRows, mapCols);
            }
        }
        /* Checks if the player pressed the undo key */
        else if (input == 'u') 
        {
            /* Reverts game characters and map to previous state */
            undoLastMove(movesList, &gameCharacters, &map, mapRows, mapCols); 
            printMap(map, backgroundMap, mapRows, mapCols); 
	    }
    }
    
    /* Free up allocated memory */
    freeMap(backgroundMap, mapRows);
    freeMap(map, mapRows);
    
    /* Free up the linkedlist */
    while (movesList->count > 0) 
    {
	    GameState *state = (GameState *)removeFirst(movesList);
	    for (i = 0; i < mapRows; i++) 
        {
		    free(state->map[i]);
	    }
	    free(state->map);
	    free(state);
    }
    freeLinkedList(movesList, &free);
    
    return 0;
}
