#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QLabel>
#include <QtGui>
#include "constants.h"

class GameBoard: public QLabel{
public:
  GameBoard();
  void draw_board(int board[][20]);
private:
  QImage backgroundImage;
}

#endif
