#include "constants.h"

GameBoard::GameBoard() {
  backgroundImage.load("background.bmp");

  this->setPixmap(QPixmap::fromImage(backgroundImage));
  this->show();
}

void GameBoard::draw_board(int board[][20]) {
  int i, j;
  backgroundImage.load("background.bmp");
  QPainter qPainter(&backgroundImage);
  qPainter.setPen(Qt::black);

  for (i = 0; i < BOARD_WIDTH; i++){
    for(j = 0; j < BOARD_HEIGHT; j++){
      int type = board[i][j];
      //std::cout << i << "  " << j << "  " << type << std::endl;
      if (type != EMPTY) {
        if(type == RED) {qPainter.setBrush(Qt::red);}
        else if(type == GREEN) {qPainter.setBrush(Qt::green);}
        else if(type == BLUE) {qPainter.setBrush(Qt::blue);}
        else if(type == YELLOW) {qPainter.setBrush(Qt::yellow);}
        else if(type == CYAN) {qPainter.setBrush(Qt::cyan);}
        else if(type == ORANGE) {qPainter.setBrush(Qt::darkYellow);}
        else if(type == PURPLE) {qPainter.setBrush(Qt::magenta);}
        qPainter.drawRect(i * SQUARE_SIZE, (BOARD_HEIGHT -1 - j)*SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE);
      }
    }
  }

  this->setPixmap(QPixmap::fromImage(backgroundImage));
  this->show();
}
