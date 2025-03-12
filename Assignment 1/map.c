/*******************************************************************************************************************
  
 * map.c

 * AUTHOR: PRASHANTHA FERNANDO
 
 * LAST EDITED: 19/09/23
 
 * DESCRIPTION: C file containing map initialisation, variable positionining and map print functions
 
*******************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "movement.h"
#include "random.h"

/* Extern reference to the cars' data */
extern int **cars; 

/* Initialize player's and goal's positions */
void createPlayerGoalPos(int *pRow, int *pCol, int *gRow, int *gCol, int rows, int cols)
{
    /* Initializing player position at the top-left corner */
    *pRow = 0;
    *pCol = 0;

    /* Initializing goal position at the bottom-right corner */
    *gRow = rows - 1;
    *gCol = cols - 1;
}

/* Store cars' data into the global array */
void initialiseCarsData(char **map, int rows, int cols) 
{   
    int carCount, carIndex;
    int i, j;
    
    carCount = rows / 2;

    cars = (int **)malloc(carCount * sizeof(int *));
    for (i = 0; i < carCount; i++) 
    {   
        cars[i] = (int *)malloc(3 * sizeof(int));
    }
    
    carIndex = 0; 
    for (i = 1; i < rows; i += 2) 
    {
        for (j = 1; j < cols - 1; j++) 
        {
            if (map[i][j] == '<' || map[i][j] == '>') 
            {
                cars[carIndex][0] = i; 
                cars[carIndex][1] = j; 
                
                if (map[i][j] == '>') 
                {
                    cars[carIndex][2] = 0;
                } 
                else 
                {
                    cars[carIndex][2] = 1;
                }
                
                carIndex++;
            }
        }
    }
}

/* Randomise car placement on the map */
void placeRandomCars(char** map, int map_row, int map_col) 
{
    int i, roadPosition;

    for (i = 1; i < map_row; i += 2) 
    {
        roadPosition = randomUCP(1, map_col - 1);
        if (randomUCP(0, 1) == 0) 
        {
            map[i][roadPosition] = '<';
        } 
        else 
        {
            map[i][roadPosition] = '>';
        }
    }
}

/* Create and initialize the game map */
void createMap(char **map, int rows, int cols, int pRow, int pCol, int gRow, int gCol)
{
    int i, j;

    /* Mallocing for each row */
    for (i = 0; i < rows; i++)
    {
        map[i] = (char *)malloc(sizeof(char) * cols);
    }

    /* Initializing map */
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (i == pRow && j == pCol)
            {
                map[i][j] = 'P';
            }
            else if (i == gRow && j == gCol)
            {
                map[i][j] = 'G';
            }
            else if (i % 2 == 1)
            {
            	map[i][j] = '.';
            }
            else 
            {
            	map[i][j] = ' ';
            }
        }
    }
}

/* Print the game map */
void printMap(char **map, int rows, int cols)
{
    int i, j;
	
    /* Refresh terminal to print map */
    system("clear");
    
    /* Prints star border around playable map area */
    for (i = 0; i < rows + 2; i++)
    {
        for (j = 0; j < cols + 2; j++)
        {
            if (i == 0 || j == 0 || i == rows + 1 || j == cols + 1)
            {
                printf("*");
            }
            else
            {
                printf("%c", map[i - 1][j - 1]);
            }
        }
        printf("\n");
    }

    /* Prints movement instruction */
    printf("Press w to move up\n");
    printf("Press s to move down\n");
    printf("Press a to move left\n");
    printf("Press d to move right\n");
}

/* Free dynamically allocated map memory */
void freeMap(char **map, int rows)
{
    int i;

    /* Freeing each row */
    for (i = 0; i < rows; i++)
    {
        free(map[i]);
    }

    /* Freeing the variable */
    free(map);
}
