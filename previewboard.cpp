#include <QLabel>
#include <QPainter>
#include "constants.h"
#include "previewboard.h"

PreviewBoard::PreviewBoard() {
  QImage preview_background(150,200,QImage::Format_RGB32);
  QPainter preview_painter(&preview_background);
  preview_painter.setBrush(Qt::white);
  preview_painter.drawRect(0,0,150,200);
  this->setPixmap(QPixmap::fromImage(preview_background));
  this->show();
}

void PreviewBoard::set_type(int type){
  this->type = type;
  draw_board();
}

void PreviewBoard::draw_board() {
  int i, x, y;
  QImage preview_background(150,200,QImage::Format_RGB32);
  QPainter preview_painter(&preview_background);
  preview_painter.setBrush(Qt::white);
  preview_painter.drawRect(0,0,150,200);
  preview_painter.setPen(Qt::black);
  if (type != EMPTY) {
    if(type == RED) {preview_painter.setBrush(Qt::red);}
    else if(type == GREEN) {preview_painter.setBrush(Qt::green);}
    else if(type == BLUE) {preview_painter.setBrush(Qt::blue);}
    else if(type == YELLOW) {preview_painter.setBrush(Qt::yellow);}
    else if(type == CYAN) {preview_painter.setBrush(Qt::cyan);}
    else if(type == ORANGE) {preview_painter.setBrush(Qt::darkYellow);}
    else if(type == PURPLE) {preview_painter.setBrush(Qt::magenta);}
    for (i = 0; i < 4; i++){
      x = EXPAND[type][i][0];
      y = EXPAND[type][i][1];
      preview_painter.drawRect(x*SQUARE_SIZE +75, (-y)*SQUARE_SIZE+100, SQUARE_SIZE, SQUARE_SIZE);
    }
  }

  this->setPixmap(QPixmap::fromImage(preview_background));
  this->show();
}
