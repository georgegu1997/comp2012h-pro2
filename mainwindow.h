/*
This file define the GUI of the game.
It receive the player inputs and send them to the game controller.
It also provide a interface to receive data from the controller and update the screen.
*/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <unistd.h>
#include <iostream>
#include <QApplication>
#include <QtGui>
#include <QLabel>
#include "constants.h"
#include "gamecontroller.h"
#include "gameboard.h"
#include "previewboard.h"
#include "scoreboard.h"

class MainWindow : public QWidget
{
public:
  //the constructor constructs the layout of the window.
  //and instantialize the gamecontroller.
  MainWindow(QWidget *parent = 0);
  //handling the keypressevent
  void keyPressEvent(QKeyEvent *event);
  //public interface to update all boards.
  void update(int board[][BOARD_HEIGHT], int next_type, int score, int level);

private:
  // the layouts
  QHBoxLayout mainLayout;
  QVBoxLayout rightLayout;

  // the instants of the board classes and game controller.
  GameBoard *gameBoard;
  PreviewBoard *previewBoard;
  ScoreBoard *scoreBoard;
  GameController *gameController;
};



#endif
