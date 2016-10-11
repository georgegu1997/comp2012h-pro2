/*
This file contains all the game data and logic.
It reacts with the MainWindow to receive the input and generate the output.
*/

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "constants.h"
#include <QApplication>
#include <QObject>
#include <QTimer>

class MainWindow;
class GameController: public QObject{
  Q_OBJECT
public:
  //initialize the timer, connect the SIGNAL and the SLOT.
  //initialize the game data, and clear the square of the board.
  GameController();

  //get a point of the mainwindow to update the GUI
  void set_mainwindow(MainWindow * arg);

  //public interface to handling keyboard input to manipulate the game.
  void move_left();
  void move_right();
  void move_down();
  void rotate_right();
  void rotate_left();
  void game_start();

public slots:
  // this is the main loop  used in the timer.
  //It let the block move down once,
  //and check whether the rows can be eliminated and do it if so.
  //and check whether the player fail.
  void main_loop();

private:
  MainWindow *mainwindow;
  QTimer *timer;

  //the staticBoard contain the cumulated squares without the current falling block
  //the board will be created by adding the current blcok to the staticBoard to serve as the data to update the board.
  int staticBoard[BOARD_WIDTH][BOARD_HEIGHT];
  int board[BOARD_WIDTH][BOARD_HEIGHT];

  //this is a variables to indicate whether the game is running.
  int running;

  //this is a struct to store the information of the current board and the next board.
  struct block {
    int center_pos[2];
    int state;
    int type;
  } current_block, next_block;

  //these variables store the information like score and level of the player.
  int current_level, fall_interval, score;

  //check whether there is square in the top FAIL_ROWS rows, return 1 if true.
  int check_fail();

  //check wheter there exist rows can be eliminated. If true, call the eliminate_rows.
  void check_eliminate();
  void eliminate_rows(int eli_start, int eli_rows);

  //restore the info of the player to the initial state.
  void init_data();

  //clear the staticBoard and board.
  void clear_board();

  //gen_rand_block generate the next_block randomly.
  //gen_current_block copy the next_block to the current_block and call gen_rand_block again.
  void gen_rand_block();
  void gen_current_block();

  //after change, this function use mainwindow to update the GUI.
  void after_move();

  //these functions manipulate the 2_D arrays baord and staticBoard
  void add_block_to_board(int board_type);
  void static_board_to_board();

  //check whether there is conflict after the command by user. If so, return 1.
  int check_move(int direction);
  int check_rotate(int next_state);

  //get absolute position of each square of the block using center position of the block and relative position
  //return the position by revise the value of x and y in reference.
  void get_square_pos (int &x,int &y, int center_x, int center_y, int rel_x, int rel_y, int state);
};

#endif
