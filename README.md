# comp2012h-pro2
tetris

#  The program still need the background.bmp as the background image of the #game board.
  The main.cpp provide a entry to instantialize the MainWindow class and start the tetris. It dose nothing important.
  The constants.h stores all the parameters used in the game.We can easily make changes such as the size of the grid, scoring policy by simply changing this header file.
  The MainWindow class define the layout of the game window. It has the instants of GameBoard, PreviewBoard, ScoreBoard and GameController.It receives the keypress inputs of the player and pass them to the GameController.It also has the interface to receive the signal from GameController and update the three boards. 
  The GameBoard, PreviewBoard and ScoreBoard are the three widget in the game. They only have the interface to display the data/graph, but do not have anything to do with the controll of the game.
  The GameController class has all the information about the game. It handles the input, manipulates the grid board, stores the score and level, keep the falling loop, and update the UI.