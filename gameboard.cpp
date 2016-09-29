#include "gameboard.h"
#include "constants.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <QApplication>
#include <QTimer>

GameBoard::GameBoard() {
  current_level = START_LEVEL;
  fall_interval = FALL_TIME_INIT;
  current_block.type = EMPTY;
  next_block.type = EMPTY;
  clearBoard();
}
/*
void GameBoard::fall_loop() {
  QTimer::singleShot(fall_interval, this, SLOT(fall_loop()));
  moveDown();
}
*/
void GameBoard::clearBoard() {
  int i, j;
  for (i = 0; i < BOARD_WIDTH; i++){
    for(j = 0; j < BOARD_HEIGHT; j++){
      staticBoard[i][j] = EMPTY;
      board[i][j] = EMPTY;
    };
  };
}

void GameBoard::game_start() {
  clearBoard();
  gen_rand_block();
  gen_current_block();
  //GameBoard::fall_loop();
}

void GameBoard::static_board_to_board() {
  int i, j;
  for(i = 0; i < BOARD_WIDTH; i++){
    for(j = 0; j < BOARD_HEIGHT; j++){
      board[i][j] = staticBoard[i][j];
    };
  };
}

void GameBoard::add_block_to_board() {
  int type = current_block.type;
  int i, x, y, rel_x, rel_y;
  int center_x = current_block.center_pos[0];
  int center_y = current_block.center_pos[1];
  //std::cout << current_block.center_pos[0] << current_block.center_pos[1] << "  " << std::endl;

  static_board_to_board();

  for (i = 0; i < 4; i++){
    rel_x = EXPAND[current_block.type][i][0];
    rel_y = EXPAND[current_block.type][i][1];
    get_square_pos(x, y, center_x, center_y, rel_x, rel_y, current_block.state);

    if (x >= 0 && x <= BOARD_WIDTH - 1 && y >= 0 &&  y <= BOARD_HEIGHT - 1) {
      //std::cout << x << "  " << y << std::endl;
      board[x][y] = type;
    }
  }
}

void GameBoard::after_move() {
  add_block_to_board();
}

void GameBoard::gen_rand_block() {
  srand((unsigned int)(time(NULL)));
  next_block.type = (rand() % (TYPE_AMOUNT)) + 1;
  next_block.center_pos[0] = BOARD_WIDTH / 2;
  next_block.center_pos[1] = BOARD_HEIGHT;
  next_block.state = UP;
}

void GameBoard::gen_current_block() {
  current_block = next_block;
  gen_rand_block();
}

void GameBoard::rotateLeft() {
  if (current_block.type == EMPTY) return;
  switch (current_block.state) {
    case UP: if(check_rotate(LEFT)) return;current_block.state = LEFT; break;
    case LEFT: if(check_rotate(DOWN)) return;current_block.state = DOWN; break;
    case DOWN: if(check_rotate(RIGHT)) return;current_block.state = RIGHT; break;
    case RIGHT: if(check_rotate(UP)) return;current_block.state = UP; break;
  }
  after_move();
}

void GameBoard::rotateRight() {
  if (current_block.type == EMPTY) return;
  switch (current_block.state) {
    case UP: if(check_rotate(RIGHT)) return;current_block.state = RIGHT; break;
    case RIGHT: if(check_rotate(DOWN)) return;current_block.state = DOWN; break;
    case DOWN: if(check_rotate(LEFT)) return;current_block.state = LEFT; break;
    case LEFT: if(check_rotate(UP)) return;current_block.state = UP; break;
  }
  after_move();
}

void GameBoard::moveRight() {
  if (current_block.type == EMPTY) return;
  if (check_move(RIGHT)) return;
  current_block.center_pos[0]++;
  after_move();
}

void GameBoard::moveLeft() {
  if (current_block.type == EMPTY) return;
  if (check_move(LEFT)) return;
  current_block.center_pos[0]--;
  after_move();
}

void GameBoard::moveDown() {
  if (current_block.type == EMPTY) return;
  if (check_move(DOWN)) return;
  current_block.center_pos[1]--;
  after_move();
}

int GameBoard::check_move(int direction) {
  int i, rel_x, rel_y;
  int result = 0;
  //result == 0:no collide with other square
  //result == 1: collide with other square
  //result == 2: touch to the bottom
  int center_x = current_block.center_pos[0];
  int center_y = current_block.center_pos[1];

  //std::cout << center_x << "  " << center_y << std::endl;

  switch (direction) {
    case DOWN: center_y--;break;
    case LEFT: center_x--;break;
    case RIGHT: center_x++;break;
  }

  for (i = 0; i < 4; i++){
    rel_x = EXPAND[current_block.type][i][0];
    rel_y = EXPAND[current_block.type][i][1];
    get_square_pos(x, y, center_x, center_y, rel_x, rel_y, current_block.state);
    //std::cout << "square position:" << x << " " << y << std::endl;

    if (x < 0 || x > BOARD_WIDTH -1  || y < 0 || staticBoard[x][y] != EMPTY) {
      result = 1;
    }
  }

  return result;
}

int GameBoard::check_rotate(int next_state) {
  int i, x, y, rel_x, rel_y;
  int result = 0;
  int center_x = current_block.center_pos[0];
  int center_y = current_block.center_pos[1];

  for (i = 0; i < 4; i++){
    rel_x = EXPAND[current_block.type][i][0];
    rel_y = EXPAND[current_block.type][i][1];
    get_square_pos(x, y, center_x, center_y, rel_x, rel_y, next_state);
    //std::cout << result << std::endl;
    if (x < 0 || x > BOARD_WIDTH -1  || y < 0 || staticBoard[x][y] != EMPTY) {
      result = 1;
    }
  }
  return result;
}

void GameBoard::get_square_pos (int &x,int &y, int center_x, int center_y, int rel_x, int rel_y, int state) {
  //std::cout << x <<" "<<y<<center_x<<" "<<center_y<<" "<<rel_x<<" "<<rel_y<<std::endl;
  switch (state) {
    case UP:
    x = center_x+rel_x;
    y = center_y+rel_y;
    break;
    case LEFT:
    x = center_x-rel_y;
    y = center_y+rel_x;
    break;
    case DOWN:
    x = center_x-rel_x;
    y = center_y-rel_y;
    break;
    case RIGHT:
    x = center_x+rel_y;
    y = center_y-rel_x;
    break;
  }
}
