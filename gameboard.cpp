#include "gameboard.h"
#include "constants.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

GameBoard::GameBoard() {
  clearBoard();
}

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
  int i, x, y;
  std::cout << current_block.center_pos[0] << current_block.center_pos[1] << "  " << std::endl;

  static_board_to_board();

  for (i = 0; i < 4; i++){
    switch (current_block.state) {
      case UP:
      x = current_block.center_pos[0]+EXPAND[current_block.type][i][0];
      y = current_block.center_pos[1]+EXPAND[current_block.type][i][1];
      break;
      case LEFT:
      x = current_block.center_pos[0]-EXPAND[current_block.type][i][1];
      y = current_block.center_pos[1]+EXPAND[current_block.type][i][0];
      break;
      case DOWN:
      x = current_block.center_pos[0]-EXPAND[current_block.type][i][0];
      y = current_block.center_pos[1]-EXPAND[current_block.type][i][1];
      break;
      case RIGHT:
      x = current_block.center_pos[0]+EXPAND[current_block.type][i][1];
      y = current_block.center_pos[1]-EXPAND[current_block.type][i][0];
      break;
    }
    if (x >= 0 && x <= BOARD_WIDTH - 1 && y >= 0 &&  y <= BOARD_HEIGHT - 1) {
      std::cout << x << "  " << y << std::endl;
      board[x][y] = type;
    }
  }
/*
  for (i = 0; i < 4; i++){
    switch (current_block.state) {
      case UP:
      board[current_block.center_pos[0]+EXPAND[current_block.type][i][0]][current_block.center_pos[1]+EXPAND[current_block.type][i][1]] = type;
      break;
      case LEFT:
      board[current_block.center_pos[0]-EXPAND[current_block.type][i][1]][current_block.center_pos[1]+EXPAND[current_block.type][i][0]] = type;
      break;
      case DOWN:
      board[current_block.center_pos[0]-EXPAND[current_block.type][i][0]][current_block.center_pos[1]-EXPAND[current_block.type][i][1]] = type;
      break;
      case RIGHT:
      board[current_block.center_pos[0]+EXPAND[current_block.type][i][1]][current_block.center_pos[1]-EXPAND[current_block.type][i][0]] = type;
      break;
    }
  }
*/
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
  switch (current_block.state) {
    case UP: if(check_rotate(LEFT)) return;current_block.state = LEFT; break;
    case LEFT: if(check_rotate(DOWN)) return;current_block.state = DOWN; break;
    case DOWN: if(check_rotate(RIGHT)) return;current_block.state = RIGHT; break;
    case RIGHT: if(check_rotate(UP)) return;current_block.state = UP; break;
  }
  after_move();
}

void GameBoard::rotateRight() {
  switch (current_block.state) {
    case UP: if(check_rotate(RIGHT)) return;current_block.state = RIGHT; break;
    case RIGHT: if(check_rotate(DOWN)) return;current_block.state = DOWN; break;
    case DOWN: if(check_rotate(LEFT)) return;current_block.state = LEFT; break;
    case LEFT: if(check_rotate(UP)) return;current_block.state = UP; break;
  }
  after_move();
}

/*
int GameBoard::check_move(int direction) {
  int result;
  int type = current_block.type;
  int state = current_block.state;
  switch (direction) {
    case LEFT:
    result = (current_block.center_pos[0]-CONFLICT[type][3+LEFT-state]) <= 0?1:0;
    break;
    case RIGHT:
    result = (current_block.center_pos[0]+CONFLICT[type][3+RIGHT-state]) >= BOARD_WIDTH-1?1:0;
    break;
    case DOWN:
    result = (current_block.center_pos[1]-CONFLICT[type][3+DOWN-state]) <= 0?1:0;
    break;
  }
  return result;
}
*/

int GameBoard::check_move(int direction) {
  int i, x, y;
  int result = 0;
  int center_x, center_y;
  center_x = current_block.center_pos[0];
  center_y = current_block.center_pos[1];

  std::cout << center_x << "  " << center_y << std::endl;

  switch (direction) {
    case DOWN: center_y--;
    case LEFT: center_x--;
    case RIGHT: center_x++;
  }

  for (i = 0; i < 4; i++){
    switch (current_block.state) {
      case UP:
      x = center_x+EXPAND[current_block.type][i][0];
      y = center_y+EXPAND[current_block.type][i][1];
      break;
      case LEFT:
      x = center_x-EXPAND[current_block.type][i][1];
      y = center_y+EXPAND[current_block.type][i][0];
      break;
      case DOWN:
      x = center_x-EXPAND[current_block.type][i][0];
      y = center_y-EXPAND[current_block.type][i][1];
      break;
      case RIGHT:
      x = center_x+EXPAND[current_block.type][i][1];
      y = center_y-EXPAND[current_block.type][i][0];
      break;
    }

    if (x <= 0 || x >= BOARD_WIDTH || y < 0) {
      result = 1;
    }
  }

  return result;
}

int GameBoard::check_rotate(int next_state) {
  int i, x, y;
  int result = 0;

  for (i = 0; i < 4; i++){
    switch (next_state) {
      case UP:
      x = current_block.center_pos[0]+EXPAND[current_block.type][i][0];
      y = current_block.center_pos[1]+EXPAND[current_block.type][i][1];
      break;
      case LEFT:
      x = current_block.center_pos[0]-EXPAND[current_block.type][i][1];
      y = current_block.center_pos[1]+EXPAND[current_block.type][i][0];
      break;
      case DOWN:
      x = current_block.center_pos[0]-EXPAND[current_block.type][i][0];
      y = current_block.center_pos[1]-EXPAND[current_block.type][i][1];
      break;
      case RIGHT:
      x = current_block.center_pos[0]+EXPAND[current_block.type][i][1];
      y = current_block.center_pos[1]-EXPAND[current_block.type][i][0];
      break;
    }
    //std::cout << result << std::endl;
    if (x < 0 || x > BOARD_WIDTH - 1 || y < 0) {
      result = 1;
    }
  }
  return result;
}

void GameBoard::moveRight() {
  if (check_move(RIGHT)) return;
  current_block.center_pos[0]++;
  after_move();
}

void GameBoard::moveLeft() {
  if (check_move(LEFT)) return;
  current_block.center_pos[0]--;
  after_move();
}

void GameBoard::moveDown() {
  if (check_move(DOWN)) return;
  current_block.center_pos[1]--;
  after_move();
}
