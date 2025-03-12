/*******************************************************************************************************************
  
 * movement.c

 * AUTHOR: PRASHANTHA FERNANDO
 
 * LAST EDITED: 19/09/23
 
 * DESCRIPTION: C file that contains functions which handle player & car movemement logic and collision logic
 
*******************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "movement.h"

/* Extern reference to the cars' data */
extern int **cars; 

/* Update temporary position of player based on user's input */
void updateTmpPos(char input, int *fRow, int *fCol, int pRow, int pCol) 
{
    if (input == 'w') 
    {
        (*fRow)--;
    } 
    else if (input == 's') 
    {
        (*fRow)++;
    } 
    else if (input == 'a') 
    {
        (*fCol)--;
    } 
    else if (input == 'd') 
    {
        (*fCol)++;
    }
}

/* Move player P on the game map */
void movePlayer(char **map, int rows, int cols, int fRow, int fCol, int pRow, int pCol) 
{
    if (pRow % 2 == 1) 
    {
        map[pRow][pCol] = '.';
    } 
    else 
    {
        map[pRow][pCol] = ' ';
    }
    
    map[fRow][fCol] = 'P';
}

/* Move cars on the game map */
void moveCars(char **map, int rows, int cols, int pRow, int pCol)
{
    int carCount, row, col, direction;
    int i;
    
    carCount = rows / 2; /* Number of cars is half the rows (every alternate row) */
    
    /* Iterate through all the cars */
    for (i = 0; i < carCount; i++) 
    {
        row = cars[i][0];
        col = cars[i][1];
        direction = cars[i][2];
        
        map[row][col] = '.'; /* Clear the current position of the car on the map */

        /* Check car's direction to determine its movement */
        if (direction == 0) /* If car is moving to the right */
        {
            col++; /* Increment column to move to the right */
            
            if (col == cols - 1) /* If car reaches the last column */
            {
                direction = 1; /* Change direction to left */
                
                if(map[row][col] != 'P') /* Check if player is not at the current position */
                {
                    map[row][col] = '<'; /* Update car's icon to indicate its direction */
                }
            } 
            else 
            {
                if(map[row][col] != 'P')
                {
                    map[row][col] = '>'; /* Update car's icon to indicate its direction */
                }
            }
        } 
        else /* If car is moving to the left */
        {
            col--; /* Decrement column to move to the left */
            
            if (col == 0) /* If car reaches the first column */
            {
                direction = 0; /* Change direction to right */
                
                if(map[row][col] != 'P')
                {
                    map[row][col] = '>'; /* Update car's icon to indicate its direction */
                }
            } 
            else 
            {
                if(map[row][col] != 'P')
                {
                    map[row][col] = '<'; /* Update car's icon to indicate its direction */
                }
            }
        }

        cars[i][1] = col; /* Update car's current column position */
        cars[i][2] = direction; /* Update car's current direction */
    }
    
    map[pRow][pCol] = 'P'; /* Ensure P remains on map if car passes over its position */
}

/* Check for collisions or winning conditions */
int checkCollision(int pRow, int pCol, int gRow, int gCol, int **cars) 
{
    int collisionResult = 0; /* Will return 0 if neither winning nor losing conditions are met */
    int carRow;
    
    if (pRow == gRow && pCol == gCol) 
    {
        collisionResult = 1; /* If player reaches goal, return 1 (win) */
    } 
    else if (pRow % 2 != 0) /* If player is on an odd row (on the road) */
    {
        carRow = (pRow - 1) / 2; /* Calculate equivalent car's row in the car array */
        
        /* If car's column matches player's column, a collision has occurred */
        if (cars[carRow][1] == pCol) 
        {
            collisionResult = 2; /* If player collides with a car, return 2 (loss) */
        }
    }
    
    return collisionResult; 
}
