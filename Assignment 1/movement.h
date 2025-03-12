#ifndef MOVEMENT_H
#define MOVEMENT_H

void updateTmpPos(char input, int *fRow, int *fCol, int pRow, int pCol);
void movePlayer(char **map, int rows, int cols, int fRow, int fCol, int pRow, int pCol);
void moveCars(char **map, int rows, int cols, int pRow, int pCol);
int checkCollision(int pRow, int pCol, int gRow, int gCol, int **cars);

#endif
