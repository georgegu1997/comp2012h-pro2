#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
  QApplication tetris_app(argc, argv);

  MainWindow w;
  w.show();

  return tetris_app.exec();
}
