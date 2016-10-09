#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QLabel>
#include "constants.h"

class ScoreBoard: public QLabel{
public:
  //the constructor only set the level and score to 0.
  ScoreBoard();
  //this function set the level and score, then display them.
  void set_score_and_level();
private:
  int level;
  int score;
}

#endif
