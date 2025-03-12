#ifndef MAP_H
#define MAP_H

char** allocateMap(int rows, int cols);
void createPlayerGoalCarPos(Position *player, Position *goal, Position *car, char **map);
void printMap(char **map, char **backgroundMap, int rows, int cols);
void freeMap(char **map, int rows);

#endif
