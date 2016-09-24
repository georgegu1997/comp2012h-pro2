#include <unistd.h>
#include <QApplication>
#include <QtGui>
#include <QLabel>

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class MainWindow : public QWidget
{
public:
  MainWindow(QWidget *parent = 0) : QWidget(parent){
    mainLayout.addWidget(&mainBoard);
    setLayout(&mainLayout);
    drawBoard();
  }
  void drawBoard();

private:
  QHBoxLayout mainLayout;
  QVBoxLayout rightLayout;
  QLabel mainBoard;
  QImage backgroundImage;
};



#endif
