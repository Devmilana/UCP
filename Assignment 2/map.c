/*******************************************************************************************************************
  
 * map.c

 * AUTHOR: PRASHANTHA FERNANDO
 
 * LAST EDITED: 22/10/23
 
 * DESCRIPTION: C file containing map initialisation, player/goal positionining and map print functions
 
*******************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "game_structures.h"
#include "map.h"

/* Allocates memory for the game map based on given rows and cols and returns pointer to created map */
char** allocateMap(int rows, int cols) 
{
    int i;

    /* Allocate memory for each row */
    char** map = (char**)malloc(rows * sizeof(char*));

    /* Allocate memory for each column in the rows */
    for (i = 0; i < rows; i++) 
    {
        map[i] = (char*)malloc(cols * sizeof(char));
    }

    return map;
}

/* Set player, goal, and car positions on the game map */
void createPlayerGoalCarPos(Position *player, Position *goal, Position *car, char **map) 
{
    map[player->row][player->col] = 'P'; /* Set player position as 'P' */
    map[goal->row][goal->col] = 'G'; /* Set goal position as 'G' */
    map[car->row][car->col] = '>'; /* Set car position as '>' */
}

/* Prints game map with boundaries and game elements, overlaying the background map */
void printMap(char **map, char **backgroundMap, int rows, int cols) 
{
    int i, j;
    
    system("clear");  
    
    /* Loop to print each cell of the map */
    for (i = 0; i < rows + 2; i++) 
    {
        for (j = 0; j < cols + 2; j++) 
        {
            /* Print boundaries */
            if (i == 0 || j == 0 || i == rows + 1 || j == cols + 1) 
            {
                printf("*");
            } 
            else 
            {
                if (map[i-1][j-1] != ' ' && map[i-1][j-1] != '.') 
                {
                    printf("%c", map[i-1][j-1]);  
                } 
                else 
                {
                    printf("%c", backgroundMap[i-1][j-1]);
                }
            }
        }
        printf("\n");
    }

    /* Displays instructions for the player */
    printf("Press w to move up\n");
    printf("Press s to move down\n");
    printf("Press a to move left\n");
    printf("Press d to move right\n");
    printf("Press u to undo\n");
}

/* Free allocated memory for the map */
void freeMap(char **map, int rows) 
{
    int i;

    for (i = 0; i < rows; i++) 
    {
        free(map[i]);
    }

    free(map);
}
