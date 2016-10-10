#include <stdio.h>
#include "scoreboard.h"

ScoreBoard::ScoreBoard() {
  set_score_and_level(0,0);
}

void ScoreBoard::set_score_and_level(int score, int level) {
  this->score = score;
  this->level = level;
  char score_text[64];
  sprintf(score_text, "Level: %d \n Score: %d", level, score);
  this->setText(score_text);
}
