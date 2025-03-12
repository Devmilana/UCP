/*******************************************************************************************************************
  
 * movement.c

 * AUTHOR: PRASHANTHA FERNANDO
 
 * LAST EDITED: 22/10/23
 
 * DESCRIPTION: C file that contains functions which handle player/car movemement, collision and move undo logic
 
*******************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "game_structures.h"
#include "linked_list.h"
#include "movement.h"
#include "map.h"

/* Calls player movement and checks for collisions with the car */
void movePlayer(char direction, Position *player, char **map, char **backgroundMap, int mapRows, int mapCols, Position car, LinkedList *movesList) 
{
    int i, j;

    /* Get the next position of the player */
    Position nextPlayerPos = getNextPlayerPosition(direction, *player);
    Position prevPlayerPos = *player;
    GameState *currentState;
    
    /* Move the player */
    handlePlayerMovement(direction, player, map, backgroundMap, mapRows, mapCols);
    
    /* Record current game state for undoing if needed */
    currentState = (GameState *)malloc(sizeof(GameState));
    currentState->player = *player;
    currentState->car = car;
    currentState->map = allocateMap(mapRows, mapCols);
    for (i = 0; i < mapRows; i++) 
    {
        for (j = 0; j < mapCols; j++) 
        {
            currentState->map[i][j] = map[i][j];
        }
    }
    
    /* Insert the current state into the moves list */
    insertFirst(movesList, currentState);

    /* Checks for player/car collision after moving */
    if (checkCollision(nextPlayerPos, car))
    {
        player->row = nextPlayerPos.row;
        player->col = nextPlayerPos.col;
        map[nextPlayerPos.row][nextPlayerPos.col] = 'P';
        map[prevPlayerPos.row][prevPlayerPos.col] = ' ';
        return;
    }
}

/* Returns the future position of the player based on direction without moving them */
Position getNextPlayerPosition(char direction, Position player) 
{
    Position nextPos = player;

    switch (direction) 
    {
        case 'w':
            nextPos.row -= 1;
            break;
        
        case 's':
            nextPos.row += 1;
            break;
        
        case 'a':
            nextPos.col -= 1;
            break;
        
        case 'd':
            nextPos.col += 1;
            break;
    }

    return nextPos;
}

/* Handles player movement based on input given */
void handlePlayerMovement(char direction, Position *player, char **map, char **backgroundMap, int mapRows, int mapCols) 
{
    int newRow = player->row;
    int newCol = player->col;

    /* Adjusts player's intended position based on input direction */
    switch (direction) 
    {
        case 'w':
            newRow = player->row - 1;
            break;
        
        case 's':
            newRow = player->row + 1;
            break;
        
        case 'a':
            newCol = player->col - 1;
            break;
        
        case 'd':
            newCol = player->col + 1;
            break;
    }

    /* Check for boundary conditions and valid path before moving */
    if (newRow >= 0 && newRow < mapRows && newCol >= 0 && newCol < mapCols && (map[newRow][newCol] == '.' || map[newRow][newCol] == ' ' || map[newRow][newCol] == 'G')) 
    {
        /* Clear the player's previous position on the map */
        map[player->row][player->col] = backgroundMap[player->row][player->col];
        
        /* Update player's position */
        player->row = newRow;
        player->col = newCol;

        /* Mark the new position of the player on the map */
        map[player->row][player->col] = 'P';
    }
}

/* Moves car on game map */
void moveCar(Position *car, char **map, int mapRows, int mapCols) 
{
    char currentDir = map[car->row][car->col];
    Position newCarPos = *car;

    /* Check and move car based on direction */
    switch (currentDir) 
    {
        case '>':
            newCarPos.col += 1;
            break;
        
        case '<':
            newCarPos.col -= 1;
            break;
        
        case '^':
            newCarPos.row -= 1;
            break;
        
        case 'v':
            newCarPos.row += 1;
            break;
    }

    /* Check if new position is valid */
    if (map[newCarPos.row][newCarPos.col] == '.') 
    {
        moveCarToNewPos(car, map, currentDir);
    } 
    else 
    {
        /* Change direction and move */
        if (currentDir == '>') 
        {
            if (map[car->row - 1][car->col] == '.') 
            {
                moveCarToNewPos(car, map, '^');
            } 
            else if (map[car->row + 1][car->col] == '.') 
            {
                moveCarToNewPos(car, map, 'v');
            }
        } 
        else if (currentDir == '<') 
        {
            if (map[car->row - 1][car->col] == '.') 
            {
                moveCarToNewPos(car, map, '^');
            } 
            else if (map[car->row + 1][car->col] == '.') 
            {
                moveCarToNewPos(car, map, 'v');
            }
        } 
        else if (currentDir == '^') 
        {
            if (map[car->row][car->col - 1] == '.') 
            {
                moveCarToNewPos(car, map, '<');
            } 
            else if (map[car->row][car->col + 1] == '.') 
            {
                moveCarToNewPos(car, map, '>');
            }
        } 
        else if (currentDir == 'v') 
        {
            if (map[car->row][car->col - 1] == '.') 
            {
                moveCarToNewPos(car, map, '<');
            } 
            else if (map[car->row][car->col + 1] == '.') 
            {
                moveCarToNewPos(car, map, '>');
            }
        }
    }
}

/* Helper function to move car to new position */
void moveCarToNewPos(Position *car, char **map, char direction) 
{
    map[car->row][car->col] = '.'; /* Clears car's current position */
    
    /* Adjust position based on current direction */
    switch (direction) 
    {
        case '>':
            car->col += 1;
            break;
        
        case '<':
            car->col -= 1;
            break;
        
        case '^':
            car->row -= 1;
            break;
        
        case 'v':
            car->row += 1;
            break;
    }
    
    map[car->row][car->col] = direction; /* Mark car's new position on the map */
}

/* Checks if the player and car are at the same position */
int checkCollision(Position player, Position car) 
{
    if (player.row == car.row && player.col == car.col)
    {
        return 1; /* Returns 1 if collision is detected */
    }
    return 0; /* Returns 0 if no collision is detected */
}

/* Revert player and the map to their previous state, undoing the last move */
void undoLastMove(LinkedList *movesList, GameCharacters *gameCharacters, char ***map, int mapRows, int mapCols)
{
    int i, j;
    
    if (movesList->count > 1) /* Check if there is more than one state remaining in linkedlist */
    {
        GameState *lastState = (GameState *)removeFirst(movesList); /* Retrieves and removes the latest state */
        GameState *previousState = (GameState *)movesList->head->value; /* Retrieves and removes previous state */

        /* Restore car and player to previous state */
        gameCharacters->player = previousState->player;
        gameCharacters->car = previousState->car;

        /* Restores map to previous state */
        for (i = 0; i < mapRows; i++) 
        {
            for (j = 0; j < mapCols; j++) 
            {
                (*map)[i][j] = previousState->map[i][j];
            }
        }

        /* Free up memory from latest state */
        for (i = 0; i < mapRows; i++) 
        {
            free(lastState->map[i]);
        }
        free(lastState->map);
        free(lastState);
    }
}
