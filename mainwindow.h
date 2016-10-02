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
  void drawPreview(int type);

private:
  QHBoxLayout mainLayout;
  QVBoxLayout rightLayout;
  QLabel mainBoard;
  QLabel preview_board;
  QLabel score_board;
  QImage backgroundImage;
  QPainter qPainter;
  GameBoard *gameBoard;
};



#endif
