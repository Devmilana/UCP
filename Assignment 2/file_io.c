/*******************************************************************************************************************
  
 * file_io.c

 * AUTHOR: PRASHANTHA FERNANDO
 
 * LAST EDITED: 22/10/23
 
 * DESCRIPTION: C file that contains functions to read a text file and map its data into a playable game map
 
*******************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "game_structures.h"
#include "file_io.h"
#include "map.h"

/* Function to read a text file and use the data in it to construct a background map and game character map */
char* readMapFile(char* fileName, int* rows, int* cols, char*** map, char*** backgroundMap, GameCharacters* gameCharacters) 
{
    FILE* file;
    char* error;
    int i, j, cellValue;

    /* Allocates memory for the error string */
    error = (char*)malloc(128 * sizeof(char));
    *error = '\0';

    /* Open file in read mode */
    file = fopen(fileName, "r");

    /* Checks if file opened successfully */
    if (file == NULL) 
    {
        /* Construct error message using strerror() */
        strncpy(error, "Error in opening file: ", 24);
        strncat(error, strerror(errno), 103);
    } 
    else 
    {
        /* Read the number of rows and columns from the file */
        fscanf(file, "%d %d", rows, cols);

        /* Allocates memory for the game map and the background map */
        *map = allocateMap(*rows, *cols);
        *backgroundMap = allocateMap(*rows, *cols);

        /* Reads cell values and populate the maps depending on data read from file */
        for (i = 0; i < *rows; i++) 
        {
            for (j = 0; j < *cols; j++) 
            {
                fscanf(file, "%d", &cellValue);
                switch (cellValue) 
                {
                    /* Empty space on both maps */
                    case 0:
                        (*backgroundMap)[i][j] = ' ';
                        (*map)[i][j] = ' ';
                        break;
                    
                    /* Background has dot and game map has dot */
                    case 1:
                        (*backgroundMap)[i][j] = '.';
                        (*map)[i][j] = '.';
                        break;
                    
                    /* Background has dot and game map has car symbol. Store car's position */
                    case 2:
                        (*backgroundMap)[i][j] = '.';
                        (*map)[i][j] = '>';  
                        gameCharacters->car.row = i;
                        gameCharacters->car.col = j;
                        break;
                   
                    /* Background is empty but game map has player symbol. Store player's position */
                    case 3:
                        (*backgroundMap)[i][j] = ' ';
                        (*map)[i][j] = 'P';  
                        gameCharacters->player.row = i;
                        gameCharacters->player.col = j;
                        break;
                    
                    /* Background is empty and game map has goal symbol. Store goal's position */
                    case 4:
                        (*backgroundMap)[i][j] = ' ';
                        (*map)[i][j] = 'G';  
                        gameCharacters->goal.row = i;
                        gameCharacters->goal.col = j;
                        break;
                    
                    /* Invalid cell value encountered */
                    default:
                        strncpy(error, "Error in file content: Invalid cell value", 50);
                        break;
                }
            }
        }

        /* Close the file after reading */
        fclose(file);
    }

    /* Deallocate the error string memory if no error occurs*/
    if (*error == '\0') 
    {
        free(error);
        error = NULL;
    }

    /* Returns error statement (or NULL if no errors) */
    return error;
}
