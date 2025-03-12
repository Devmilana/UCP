#ifndef GAME_STRUCTURES_H
#define GAME_STRUCTURES_H

typedef struct
{
    int row;
    int col;
} Position;

typedef struct 
{
    Position player;
    Position goal;
    Position car;
} GameCharacters;

typedef struct 
{
    Position player;
    Position car;
    char **map;
} GameState;

#endif
