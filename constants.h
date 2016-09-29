#ifndef CONSTANTS_H
#define CONSTANTS_H
// This file defines and stores all the constants used in the game.

const int BOARD_HEIGHT = 20;
const int BOARD_WIDTH = 10;

const int SQUARE_SIZE = 20;

const int FALL_TIME_INIT = 1000;
const int FALL_TIME_DES = 100;

const int MARK_BASE = 10;
const int START_LEVEL = 1;
const int MAX_LEVEL = 10;

enum Type {EMPTY=0,RED=1,GREEN=2,BLUE=3,YELLOW=4,CYAN=5,ORANGE=6,PURPLE=7};
enum State {UP=0,LEFT=1,DOWN=2,RIGHT=3};

const int TYPE_AMOUNT = 7;

const int EXPAND[8][4][2] {
  {{0,0},{0,0},{0,0},{0,0}},
  {{0,2},{0,1},{0,0},{0,-1}},
  {{0,0},{-1,0},{-1,-1},{0,-1}},
  {{0,0},{0,1},{1,0},{1,-1}},
  {{0,0},{1,0},{1,1},{0,-1}},
  {{0,0},{0,1},{0,-1},{1,-1}},
  {{0,0},{0,1},{0,-1},{-1,-1}},
  {{0,0},{1,0},{0,1},{-1,0}}
};

const int CONFLICT[8][7] {
  {0,0,0,0,0,0,0},
  {0,1,0,2,0,1,0},
  {1,1,0,0,1,1,0},
  {0,1,1,1,0,1,1},
  {0,1,1,1,0,1,1},
  {0,1,1,1,0,1,1},
  {1,1,0,1,1,1,0},
  {1,0,1,1,1,0,1}
};

#endif
