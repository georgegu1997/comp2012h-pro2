#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include "constants.h"
#include <QApplication>
#include <QObject>
#include <QTimer>

class MainWindow;
class GameBoard: public QObject{
  Q_OBJECT
public:
  GameBoard();
  void getmainwindow(MainWindow * arg);
  void moveLeft();
  void moveRight();
  void moveDown();
  void rotateLeft();
  void rotateRight();
  void game_start();
  int board[BOARD_WIDTH][BOARD_HEIGHT];
  int get_score();
  int get_next_type();
  int get_level();
public slots:
  void main_loop();
private:
  MainWindow *mainwindow;
  int staticBoard[BOARD_WIDTH][BOARD_HEIGHT];
  struct block {
    int center_pos[2];
    int state;
    int type;
  } current_block, next_block;
  int current_level, fall_interval;
  int score;

  int check_fail();
  void check_eliminate();
  void eliminate_rows(int eli_start, int eli_rows);

  void clearBoard();
  void gen_rand_block();
  void gen_current_block();
  void after_move();
  void add_block_to_board(int board_type);
  void static_board_to_board();
  int check_move(int direction);
  int check_rotate(int next_state);
  void get_square_pos (int &x,int &y, int center_x, int center_y, int rel_x, int rel_y, int state);
};

#endif
