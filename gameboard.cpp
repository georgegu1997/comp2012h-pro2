#include "gameboard.h"
#include "constants.h"
#include <stdlib.h>
#include <time.h>

GameBoard::GameBoard() {
  clearBoard();
}

void GameBoard::clearBoard() {
  int i, j;
  for (i = 0; i < BOARD_WIDTH; i++){
    for(j = 0; j < BOARD_HEIGHT; j++){
      staticBoard[i][j] = EMPTY;
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
  int i;

  static_board_to_board();

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
    case UP: current_block.state = LEFT; break;
    case LEFT: current_block.state = DOWN; break;
    case DOWN: current_block.state = RIGHT; break;
    case RIGHT: current_block.state = UP; break;
  }
  after_move();
}

void GameBoard::rotateRight() {
  switch (current_block.state) {
    case UP: current_block.state = RIGHT; break;
    case RIGHT: current_block.state = DOWN; break;
    case DOWN: current_block.state = LEFT; break;
    case LEFT: current_block.state = UP; break;
  }
  after_move();
}

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
