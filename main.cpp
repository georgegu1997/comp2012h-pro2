#include <QApplication>
#include "mainwindow.h"
#include "constants.h"

int main(int argc, char *argv[])
{
  QApplication tetris_app(argc, argv);

  MainWindow w;
  w.show();

  return tetris_app.exec();
}
