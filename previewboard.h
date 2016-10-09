#ifndef PREVIEWBOARD_H
#define PREVIEWBOARD_H

#include <QLabel>
#include <QPainter>
#include "constants.h"
#include "gamecontroller.h"

//this class define a board to preview the next block.

class PreviewBoard: public QLabel{
public:
  //initialization only initialize the QImage and the QPainter.
  PreviewBoard();
  //this interface set the type of the next block and draw it on the board
  void set_type(int type);
private:
  //this private function draw the block on the board.
  void draw_board();
  //the type current displayed on the board.
  int type;

  QImage preview_background;
  QPainter preview_painter;
}


#endif
