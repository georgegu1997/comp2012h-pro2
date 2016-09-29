#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include "constants.h"
#include <QApplication>
#include <QTimer>

class GameBoard: public QObject
{
Q_OBJECT
public slots:
  //  void fall_loop();
public:
  GameBoard();
  void moveLeft();
  void moveRight();
  void moveDown();
  void rotateLeft();
  void rotateRight();
  void game_start();
  int board[BOARD_WIDTH][BOARD_HEIGHT];
private:
  int staticBoard[BOARD_WIDTH][BOARD_HEIGHT];
  struct block {
    int center_pos[2];
    int state;
    int type;
  } current_block, next_block;
  int current_level, fall_interval;
  void clearBoard();
  void gen_rand_block();
  void gen_current_block();
  void after_move();
  void add_block_to_board();
  void static_board_to_board();
  int check_move(int direction);
  int check_rotate(int next_state);
  void get_square_pos (int &x,int &y, int center_x, int center_y, int rel_x, int rel_y, int state);
};

#endif
