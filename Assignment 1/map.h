#ifndef MAP_H
#define MAP_H

void createPlayerGoalPos(int *pRow, int *pCol, int *gRow, int *gCol, int rows, int cols);
void initialiseCarsData(char **map, int rows, int cols);
void placeRandomCars(char** map, int map_row, int map_col);
void createMap(char **map, int rows, int cols, int pRow, int pCol, int gRow, int gCol);
void printMap(char **map, int rows, int cols);
void freeMap(char **map, int rows);

#endif
