#include <unistd.h>
#include <stdio.h>
#include <QApplication>
#include <QtGui>
#include <QLabel>
#include <iostream>
#include "mainwindow.h"
#include "gameboard.h"


MainWindow::MainWindow(QWidget *parent) : QWidget(parent){
  mainLayout.addWidget(&mainBoard);
  rightLayout.addWidget(&preview_board);
  preview_board.setAttribute(Qt::WA_PaintOutsidePaintEvent);
  rightLayout.addWidget(&score_board);
  mainLayout.addLayout(&rightLayout);
  setLayout(&mainLayout);
  gameBoard = new GameBoard();
  gameBoard->getmainwindow(this);
  drawBoard(gameBoard->board);
  drawPreview(gameBoard->get_next_type());
}

void MainWindow::drawPreview(int type) {
  int i,x,y;
  QImage preview_background(150,200,QImage::Format_RGB32);
  QPainter preview_painter(&preview_background);
  preview_painter.setBrush(Qt::white);
  preview_painter.drawRect(0,0,150,200);
  preview_painter.setPen(Qt::black);
  if (type != EMPTY) {
    if(type == RED) {preview_painter.setBrush(Qt::red);}
    else if(type == GREEN) {preview_painter.setBrush(Qt::green);}
    else if(type == BLUE) {preview_painter.setBrush(Qt::blue);}
    else if(type == YELLOW) {preview_painter.setBrush(Qt::yellow);}
    else if(type == CYAN) {preview_painter.setBrush(Qt::cyan);}
    else if(type == ORANGE) {preview_painter.setBrush(Qt::darkYellow);}
    else if(type == PURPLE) {preview_painter.setBrush(Qt::magenta);}
    for (i = 0; i < 4; i++){
      x = EXPAND[type][i][0];
      y = EXPAND[type][i][1];
      preview_painter.drawRect(x*SQUARE_SIZE +75, (-y)*SQUARE_SIZE+100, SQUARE_SIZE, SQUARE_SIZE);
    }
  }

  preview_board.setPixmap(QPixmap::fromImage(preview_background));
  preview_board.show();

}

void MainWindow::drawBoard(int board[][20]) {
  int i, j;
  char score_text[64];
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

  sprintf(score_text, "Level: %d \n Score: %d", gameBoard->get_level(), gameBoard->get_score());
  score_board.setText(score_text);

  drawPreview(gameBoard->get_next_type());
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
  if(event->key() == Qt::Key_Left){
    gameBoard->moveLeft();
    //drawBoard(gameBoard.board);
  }else if(event->key() == Qt::Key_Right){
    gameBoard->moveRight();
    //drawBoard(gameBoard.board);
  }else if(event->key() == Qt::Key_Up){
    gameBoard->game_start();
    //drawBoard(gameBoard.board);
  }else if(event->key() == Qt::Key_Down) {
    gameBoard->moveDown();
    //drawBoard(gameBoard.board);
  }else if(event->key() == Qt::Key_Z) {
    gameBoard->rotateLeft();
    //drawBoard(gameBoard.board);
  }else if(event->key() == Qt::Key_X) {
    gameBoard->rotateRight();
    //drawBoard(gameBoard.board);
  }
}
