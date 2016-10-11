#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <QApplication>
#include <QObject>
#include <QTimer>
#include "gamecontroller.h"
#include "mainwindow.h"

GameController::GameController() {
  timer = new QTimer(this);
  QObject::connect(timer, SIGNAL(timeout()), this, SLOT(main_loop()));
  init_data();
  clear_board();
}

void GameController::set_mainwindow(MainWindow * arg) {
  mainwindow = arg;
}

void GameController::main_loop() {
  int fail = 0;
  if(check_move(DOWN)) {
    add_block_to_board(0);
    fail = check_fail();
    if (fail == 1) {
      timer->stop();
      return;
    }else {
      check_eliminate();
      gen_current_block();
      after_move();
    }
  }else {
    move_down();
  }

  timer->setInterval(fall_interval);
}

void GameController::check_eliminate() {
  int x,y;
  int eli_start = -1;
  int eli_rows = 0;
  int eli;
  for (y = 0; y < BOARD_HEIGHT; y++) {
    eli = 1;

    for(x = 0; x < BOARD_WIDTH; x++) {
      if (staticBoard[x][y] == EMPTY){
        eli = 0;
      }
    }

    if (eli == 1) {
      if (eli_start<0){
        eli_start = y;
      }
      eli_rows ++;
    }
  }

  if (eli_start >= 0){
    eliminate_rows(eli_start, eli_rows);
  }
}

void GameController::eliminate_rows(int eli_start, int eli_rows) {
  int x, y;
  for (y = eli_start; y < BOARD_HEIGHT; y++){
    for (x = 0; x < BOARD_WIDTH; x++) {
      if (y + eli_rows < BOARD_HEIGHT){
        staticBoard[x][y] = staticBoard[x][y+eli_rows];
      }else {
        staticBoard[x][y] = EMPTY;
      }
    }
  }
  score += MARK_BASE * eli_rows * eli_rows;
  current_level = (int)floor(score/LEVEL_STEP) + START_LEVEL;
  if (current_level>10) current_level=10;
  fall_interval = FALL_TIME_INIT - (current_level-1)*FALL_TIME_DES;
}

int GameController::check_fail() {
  int x, y;
  int fail = 0;
  for (y = BOARD_HEIGHT-FAIL_ROWS; y < BOARD_HEIGHT; y++) {
    for (x = 0; x < BOARD_WIDTH; x++) {
      //std::cout <<x<<" "<<y<<" "<<staticBoard[x][y]<< std::endl;
      if(staticBoard[x][y] != EMPTY) {
        fail = 1;
      }
    }
  }
  return fail;
}

void GameController::clear_board() {
  int i, j;
  for (i = 0; i < BOARD_WIDTH; i++){
    for(j = 0; j < BOARD_HEIGHT; j++){
      staticBoard[i][j] = EMPTY;
      board[i][j] = EMPTY;
    };
  };
}

void GameController::game_start() {
  if (timer->isActive()) return;
  init_data();
  clear_board();
  gen_rand_block();
  gen_current_block();
  after_move();
  timer->start(fall_interval);
}

void GameController::init_data() {
  current_level = START_LEVEL;
  fall_interval = FALL_TIME_INIT;
  current_block.type = EMPTY;
  next_block.type = EMPTY;
  score = 0;
}

void GameController::static_board_to_board() {
  int i, j;
  for(i = 0; i < BOARD_WIDTH; i++){
    for(j = 0; j < BOARD_HEIGHT; j++){
      board[i][j] = staticBoard[i][j];
    };
  };
}

void GameController::add_block_to_board(int board_type = 1) {
  int type = current_block.type;
  int i, rel_x, rel_y;
  int x = 0;
  int y = 0;
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
      if (board_type == 1) {
        board[x][y] = type;
      }else if (board_type == 0) {
        staticBoard[x][y] = type;
      }
    }
  }
}

void GameController::after_move() {
  add_block_to_board();
  mainwindow->update(board, next_block.type, score, current_level);
}

void GameController::gen_rand_block() {
  srand((unsigned int)(time(NULL)));
  next_block.type = (rand() % (TYPE_AMOUNT)) + 1;
  next_block.center_pos[0] = BOARD_WIDTH / 2;
  next_block.center_pos[1] = BOARD_HEIGHT - 2;
  next_block.state = UP;
}

void GameController::gen_current_block() {
  current_block = next_block;
  gen_rand_block();
}

void GameController::rotate_left() {
  if (current_block.type == EMPTY) return;
  switch (current_block.state) {
    case UP: if(check_rotate(LEFT)) return;current_block.state = LEFT; break;
    case LEFT: if(check_rotate(DOWN)) return;current_block.state = DOWN; break;
    case DOWN: if(check_rotate(RIGHT)) return;current_block.state = RIGHT; break;
    case RIGHT: if(check_rotate(UP)) return;current_block.state = UP; break;
  }
  after_move();
}

void GameController::rotate_right() {
  if (current_block.type == EMPTY) return;
  switch (current_block.state) {
    case UP: if(check_rotate(RIGHT)) return;current_block.state = RIGHT; break;
    case RIGHT: if(check_rotate(DOWN)) return;current_block.state = DOWN; break;
    case DOWN: if(check_rotate(LEFT)) return;current_block.state = LEFT; break;
    case LEFT: if(check_rotate(UP)) return;current_block.state = UP; break;
  }
  after_move();
}

void GameController::move_right() {
  if (current_block.type == EMPTY) return;
  if (check_move(RIGHT)) return;
  current_block.center_pos[0]++;
  after_move();
}

void GameController::move_left() {
  if (current_block.type == EMPTY) return;
  if (check_move(LEFT)) return;
  current_block.center_pos[0]--;
  after_move();
}

void GameController::move_down() {
  if (current_block.type == EMPTY) return;
  if (check_move(DOWN) == 1) return;
  if (check_move(DOWN) == 2) {
    main_loop();
    timer->start();
  }
  current_block.center_pos[1]--;
  after_move();
}

int GameController::check_move(int direction) {
  if (!timer->isActive()) return 1;
  int i, rel_x, rel_y;
  int x = 0;
  int y = 0;
  int result = 0;
  int center_x = current_block.center_pos[0];
  int center_y = current_block.center_pos[1];

  //std::cout << center_x << "  " << center_y << current_block.type << std::endl;

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

    if (x < 0 || x > BOARD_WIDTH -1  || y < 0 || (y<BOARD_HEIGHT && staticBoard[x][y] != EMPTY)) {
      if (direction == DOWN){
        return 2;
      }
      return 1;
    }
  }

  return 0;
}

int GameController::check_rotate(int next_state) {
  if (!timer->isActive()) return 1;
  int i, rel_x, rel_y;
  int x = 0;
  int y = 0;
  int result = 0;
  int center_x = current_block.center_pos[0];
  int center_y = current_block.center_pos[1];

  for (i = 0; i < 4; i++){
    rel_x = EXPAND[current_block.type][i][0];
    rel_y = EXPAND[current_block.type][i][1];
    get_square_pos(x, y, center_x, center_y, rel_x, rel_y, next_state);
    if (x < 0 || x > BOARD_WIDTH -1  || y < 0 || (y<BOARD_HEIGHT && staticBoard[x][y] != EMPTY)) {
      result = 1;
    }
  }
  return result;
}

void GameController::get_square_pos (int &x,int &y, int center_x, int center_y, int rel_x, int rel_y, int state) {
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
