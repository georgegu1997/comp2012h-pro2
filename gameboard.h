#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include "constants.h"

class GameBoard
{
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
  void clearBoard();
  void gen_rand_block();
  void gen_current_block();
  void after_move();
  void add_block_to_board();
  void static_board_to_board();
  int check_move(int direction);
  int check_rotate(int next_state);
};

#endif
