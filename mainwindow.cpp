#include <unistd.h>
#include <stdio.h>
#include <QApplication>
#include <QtGui>
#include <QLabel>
#include <iostream>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent){
  gameController = new GameController();
  gameBoard = new GameBoard();
  previewBoard = new PreviewBoard();
  scoreBoard = new ScoreBoard();

  mainLayout.addWidget(gameBoard);
  rightLayout.addWidget(previewBoard);
  rightLayout.addWidget(scoreBoard);
  mainLayout.addLayout(&rightLayout);
  setLayout(&mainLayout);

  gameController->set_mainwindow(this);
}

void MainWindow::update(int board[][BOARD_HEIGHT], int next_type, int score, int level) {
  gameBoard->draw_board(board);
  previewBoard->set_type(next_type);
  scoreBoard->set_score_and_level(score, level);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
  if(event->key() == Qt::Key_Left){
    gameController->move_left();
  }else if(event->key() == Qt::Key_Right){
    gameController->move_right();
  }else if(event->key() == Qt::Key_Up){
    gameController->game_start();
  }else if(event->key() == Qt::Key_Down) {
    gameController->move_down();
  }else if(event->key() == Qt::Key_Z) {
    gameController->rotate_right();
  }else if(event->key() == Qt::Key_X) {
    gameController->rotate_left();
  }
}
