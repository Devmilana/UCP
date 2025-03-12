/*******************************************************************************************************************
  
 * validation.c

 * AUTHOR: PRASHANTHA FERNANDO
 
 * LAST EDITED: 19/09/23
 
 * DESCRIPTION: C file containing program argument validation function
 
*******************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "validation.h"

/* Argument validation */
int validateArguments(int argc, char **argv)
{
    int isValid = 1;

    if (argc != 3) /* Argument count must be three (including program name) */
    {
        printf("\nNot enough arguments!\n");
        printf("\nUsage: ./traffic <map_rows> <map_columns>\n\n");
        isValid = 0;
    }
    else if (atoi(argv[1]) < 0 || atoi(argv[2]) < 0) /* Check if map rows and columns count is non negative */
    {
        printf("\nMap row and map column must be non-negative\n\n");
        isValid = 0;
    }
    else if (atoi(argv[1]) < 3 || atoi(argv[1]) % 2 == 0 || atoi(argv[2]) < 5) /* Check if map rows count is greater than 3 and is an odd number and map columns count is greater than 5 */
    {
        printf("\nNumber of map rows must be an odd number and cannot be less than 3\n");
        printf("Number of map columns cannot be less than 5\n\n");
        isValid = 0;
    }

    return isValid;
}
