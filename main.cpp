#include <QApplication>
#include "mainwindow.h"

//this cpp just instantialize the class and start the game.
int main(int argc, char *argv[])
{
  QApplication tetris_app(argc, argv);

  MainWindow w;
  w.show();

  return tetris_app.exec();
}
