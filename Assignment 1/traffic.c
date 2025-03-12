/*******************************************************************************************************************
  
 * traffic.c

 * AUTHOR: PRASHANTHA FERNANDO
 
 * LAST EDITED: 19/09/23
 
 * DESCRIPTION: Main c file of traffic game that contains game loop, calling upon all other files for execution
 
*******************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "validation.h"
#include "map.h"
#include "movement.h"
#include "terminal.h"
#include "random.h"
#include "newSleep.h"

/* Global array storing cars' data */
int **cars;

/* Main */
int main(int argc, char **argv)
{
    /* Variable for checking argument validation */
    int checkValidation; 
    
    /* Flag to keep track if the game is still being played */
    int playing = 1;

    /* Character to store user's movement input */
    char input;

    /* Map dimensions */
    int mapCols;
    int mapRows;
    char **map = NULL;

    /* Player's current position */
    int pRow;
    int pCol;

    /* Temporary position data to store next move */
    int fRow;
    int fCol;

    /* Goal position data */
    int gRow;
    int gCol;
    
    int collisionCondition; /* Stores the result of collision checks */
    int i;

    /* Argument validation */
    checkValidation = validateArguments(argc, argv);
    if (checkValidation == 0)
    {
    	return 1; /* Exit program if arguments are invalid */
    }

    initRandom(); /* Initialize random number generator */

    /* Set map dimensions */
    mapRows = atoi(argv[1]);
    mapCols = atoi(argv[2]);

    /* Set initial player and goal positions */
    createPlayerGoalPos(&pRow, &pCol, &gRow, &gCol, mapRows, mapCols);

    /* Allocate memory for map and initialize it */
    map = (char **)malloc(sizeof(char *) * mapRows);
    createMap(map, mapRows, mapCols, pRow, pCol, gRow, gCol);
    
    /* Place cars randomly on the map */
    placeRandomCars(map, mapRows, mapCols); 

    /* Store cars data after they've been placed */
    initialiseCarsData(map, mapRows, mapCols);

    /* Display initial map state */
    printMap(map, mapRows, mapCols);

    /* Main game loop */
    while (playing)
    {
        disableBuffer(); 
        scanf(" %c", &input); /* Get player's movement input */
        enableBuffer();
        
        newSleep(0.1); /* Sleep game for pacing */

        /* Store current player position in temporary variables */
        fRow = pRow;
        fCol = pCol;

        /* Update temporary position of player based on user's input */
        updateTmpPos(input, &fRow, &fCol, pRow, pCol);

        /* Check if the updated player position is within playable boundaries */
        if (fRow >= 0 && fCol >= 0 && fRow < mapRows && fCol < mapCols)
        {
            /* Check for valid movement input to update map, player and car movement */
            if (input == 'w' || input == 'a' || input == 's' || input == 'd')
            {                
                /* Move player to the new position */
                movePlayer(map, mapRows, mapCols, fRow, fCol, pRow, pCol);
                
                /* Update the player's actual position with the new position */
                pRow = fRow;
                pCol = fCol;
                
                /* Move cars on the map */
                moveCars(map, mapRows, mapCols, pRow, pCol);
            }
    
            /* Check for car collision or game win conditions */
            collisionCondition = checkCollision(pRow, pCol, gRow, gCol, cars);
            
            /* Display the updated map state */
            printMap(map, mapRows, mapCols);
            
            /* Update playing flag based on collision condition */
            if (collisionCondition == 1 || collisionCondition == 2) 
            {
                playing = 0;
            } 
        }
    }
        
    /* Print result based on collision condition */
    if (collisionCondition == 1) 
    {
        printf("You Win!\n");
    } 
    else if (collisionCondition == 2) 
    {
        printf("You lose!\n");
    }

    /* Free allocated memory */
    freeMap(map, mapRows);
    for (i = 0; i < mapRows / 2; i++) 
    {
        free(cars[i]);
    }
    free(cars);    

    return 0;
}
