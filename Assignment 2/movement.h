#ifndef MOVEMENT_H
#define MOVEMENT_H

void movePlayer(char direction, Position *player, char **map, char **backgroundMap, int mapRows, int mapCols, Position car, LinkedList *movesList);
Position getNextPlayerPosition(char direction, Position player);
void handlePlayerMovement(char direction, Position *player, char **map, char **backgroundMap, int mapRows, int mapCols);
void moveCar(Position *car, char **map, int mapRows, int mapCols);
void moveCarToNewPos(Position *car, char **map, char direction);
int checkCollision(Position player, Position car);
void undoLastMove(LinkedList *movesList, GameCharacters *gameCharacters, char ***map, int mapRows, int mapCols);

#endif
