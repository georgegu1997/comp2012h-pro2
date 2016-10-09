#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <unistd.h>
#include <iostream>
#include <QApplication>
#include <QtGui>
#include <QLabel>
#include "constants.h"
#include "gamecontroller.h"

class MainWindow : public QWidget
{
public:
  //the constructor constructs the layout of the window.
  //and instantialize the gamecontroller.
  MainWindow(QWidget *parent = 0);
  //public interface to draw the game board.
  void drawBoard(int board[][BOARD_HEIGHT]);
  //handling the keypressevent
  void keyPressEvent(QKeyEvent *event);
  //a public interface to pass the type of next block draw the preview board
  void drawPreview(int type);

private:
  QHBoxLayout mainLayout;
  QVBoxLayout rightLayout;
  QLabel mainBoard;
  QLabel preview_board;
  QLabel score_board;
  QImage backgroundImage;
  QPainter qPainter;
  GameController *gameController;
};



#endif
