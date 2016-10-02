#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <unistd.h>
#include <iostream>
#include <QApplication>
#include <QtGui>
#include <QLabel>
#include "constants.h"
#include "gameboard.h"

class MainWindow : public QWidget
{
public:
  MainWindow(QWidget *parent = 0);
  void drawBoard(int board[][BOARD_HEIGHT]);
  void keyPressEvent(QKeyEvent *event);

private:
  QHBoxLayout mainLayout;
  QVBoxLayout rightLayout;
  QLabel mainBoard;
  QImage backgroundImage;
  QPainter qPainter;
  GameBoard *gameBoard;
};



#endif
