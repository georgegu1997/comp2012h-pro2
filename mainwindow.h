#include <unistd.h>
#include <QApplication>
#include <QtGui>
#include <QLabel>
#include "gameboard.h"
#include "constants.h"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class MainWindow : public QWidget
{
public:
  MainWindow(QWidget *parent = 0) : QWidget(parent){
    mainLayout.addWidget(&mainBoard);
    setLayout(&mainLayout);
    GameBoard gameBoard;
    drawBoard(gameBoard.board);
  }
  void drawBoard(int board[][BOARD_HEIGHT]);
  void keyPressEvent(QKeyEvent *event);

private:
  QHBoxLayout mainLayout;
  QVBoxLayout rightLayout;
  QLabel mainBoard;
  QImage backgroundImage;
  GameBoard gameBoard;
  QPainter qPainter;
};



#endif
