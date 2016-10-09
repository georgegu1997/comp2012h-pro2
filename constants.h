/*
This file defines and stores all the constants used in the game.
*/

#ifndef CONSTANTS_H
#define CONSTANTS_H


//the width and height of the board(in square)
const int BOARD_HEIGHT = 20;
const int BOARD_WIDTH = 10;

// the side of the square )in pixel
const int SQUARE_SIZE = 20;

//the initial time interval bewteen two auto falling and the descrement in the intervalof each level
const int FALL_TIME_INIT = 1000;
const int FALL_TIME_DES = 100;

//the constabts of the score policy
const int MARK_BASE = 10;
const int START_LEVEL = 1;
const int LEVEL_STEP = 100;
const int MAX_LEVEL = 10;

//When either the top or the second top row of the game board is not empty, the game end.
const int FAIL_ROWS = 2;

//define the type(shape and color)of the block just using their color name.
enum Type {EMPTY=0,RED=1,GREEN=2,BLUE=3,YELLOW=4,CYAN=5,ORANGE=6,PURPLE=7};
enum State {UP=0,LEFT=1,DOWN=2,RIGHT=3};

//total number of types of blocks.
const int TYPE_AMOUNT = 7;

//this 3-D array define the relative position of each square to the center position.
//It stores the shape of each block.
const int EXPAND[8][4][2] = {
  {{0,0},{0,0},{0,0},{0,0}},
  {{0,2},{0,1},{0,0},{0,-1}},
  {{0,0},{-1,0},{-1,-1},{0,-1}},
  {{0,0},{0,1},{1,0},{1,-1}},
  {{0,0},{1,0},{1,1},{0,-1}},
  {{0,0},{0,1},{0,-1},{1,-1}},
  {{0,0},{0,1},{0,-1},{-1,-1}},
  {{0,0},{1,0},{0,1},{-1,0}}
};

#endif
