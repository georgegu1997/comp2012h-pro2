#include <unistd.h>
#include <QApplication>
#include <QtGui>
#include <QLabel>
#include <iostream>
#include "mainwindow.h"
#include "gameboard.h"
#include "constants.h"

void MainWindow::drawBoard(int board[][20]) {
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

  mainBoard.setPixmap(QPixmap::fromImage(backgroundImage));
  mainBoard.show();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
  if(event->key() == Qt::Key_Left){
    gameBoard.moveLeft();
    drawBoard(gameBoard.board);
  }else if(event->key() == Qt::Key_Right){
    gameBoard.moveRight();
    drawBoard(gameBoard.board);
  }else if(event->key() == Qt::Key_Up){
    gameBoard.game_start();
    drawBoard(gameBoard.board);
  }else if(event->key() == Qt::Key_Down) {
    gameBoard.moveDown();
    drawBoard(gameBoard.board);
  }else if(event->key() == Qt::Key_Z) {
    gameBoard.rotateLeft();
    drawBoard(gameBoard.board);
  }else if(event->key() == Qt::Key_X) {
    gameBoard.rotateRight();
    drawBoard(gameBoard.board);
  }
}
