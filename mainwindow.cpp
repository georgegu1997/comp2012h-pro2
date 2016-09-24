#include <unistd.h>
#include <QApplication>
#include <QtGui>
#include <QLabel>
#include "mainwindow.h"
#include "constants.h"

void MainWindow::drawBoard() {
  backgroundImage.load("background.bmp");
  QPainter qPainter(&backgroundImage);
  qPainter.setBrush(Qt::blue);
  qPainter.setPen(Qt::black);
  qPainter.drawRect(SQUARE_SIZE,SQUARE_SIZE,SQUARE_SIZE,SQUARE_SIZE);
  mainBoard.setPixmap(QPixmap::fromImage(backgroundImage));
  mainBoard.show();
}
