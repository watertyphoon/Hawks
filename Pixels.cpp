#include <NonBlockingGame.h>
#include <iostream>
#include <fstream>
#define colorblack 0
#define colorwhite 1

using namespace bridges::game;

struct my_game : public NonBlockingGame {
  // defaults for background color, symbol color, symbol
  NamedColor defaultColor, cursorColor, altColor;
  
 
  int static const rows = 16;
  int static const colums = 16;

  int cursorLoc[2];
  int gameBoard[rows][colums];

  int pixelCol;
  int backCol;
  int curColor;

  /* Initializes the game, passing credentials to bridges
     
   */
  my_game(int assID, std::string username, std::string apikey)
    : NonBlockingGame (172, username, apikey, rows , colums) {
    setTitle("Pixel Drawing");
    setDescription("W: Load, S: Save, Arrow keys for Movement, Q: Switch pixel, Space: Place pixel");
  }

  /* Initialize from NonBlockingGame
     Called once at game start
     More info at https://bridgesuncc.github.io/doc/cxx-api/current/html/classbr     idges_1_1game_1_1_non_blocking_game.html
   */
  virtual void initialize() override {
    keyLeftSetupFire(2);
    keyUpSetupFire(2);
    keyDownSetupFire(2);
    keyRightSetupFire(2);
    keyQSetupFire(10);
    for(int i = 0; i < rows; i++) {
      for(int j = 0; j < colums; j++) {
	gameBoard[i][j] = 0;
      }
    }

    cursorLoc[0] = 0;
    cursorLoc[1] = 0;
    
    defaultColor = NamedColor::black;
    altColor = NamedColor::white;
    cursorColor = NamedColor::blue;

    pixelCol = colorwhite;
    backCol = colorblack;
    curColor = colorwhite;

    updateGridColor();
    
  }

  // updates the visual board by changing the colors to match the gameBoard
  void updateGridColor() {
    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < colums; c++) {
        if(gameBoard[r][c] == colorblack) {
          setBGColor(r, c, defaultColor);
        }
        else if(gameBoard[r][c] == colorwhite) {
          setBGColor(r, c, altColor);
        }           
      }

      setBGColor(cursorLoc[0], cursorLoc[1], cursorColor);
    }
  }

  
 


  /* GameLoop from NonBlockingGame
     Called once each frame
     More info at https://bridgesuncc.github.io/doc/cxx-api/current/html/classbr     idges_1_1game_1_1_non_blocking_game.html
     Sets up key presses
   */
  virtual void gameLoop() override {
    
    if(keyUpFire() && cursorLoc[0] != 0) {
      cursorLoc[0]--;
    }
    else if(keyDownFire() && cursorLoc[0] != rows-1){
        cursorLoc[0]++;
    }
    if(keyLeftFire() && cursorLoc[1] != 0) {
      cursorLoc[1]--;
    }
    else if(keyRightFire() && cursorLoc[1] != (colums-1)){
      cursorLoc[1]++;
    }

    if(keySpace()) {
      gameBoard[cursorLoc[0]][cursorLoc[1]] = curColor;
    }
    if(keyQFire()) {
      changeCursor();
    }
    
    if(keyS()) {
      save();
    }
    if(keyW()) {
      load();
    }

    //UpdateBoard
    updateGridColor();


  }

  //Changes cursor back and forth from both colors
   void changeCursor() {
    if(curColor == pixelCol) {
      curColor = backCol;
    } else {
      curColor = pixelCol;
    }
    
  }
  
  //Resets the position of the cursor
  void resetCursor() {
    cursorLoc[0] = 0;
    cursorLoc[1] = 0;
  }

  /* Saves the board to a txt file
     file must be specified
   */
  void save() {
    //TODO save the state to a file


  }

  /*Loads the board from a file
    file must be specified
   */
  void load() {
    //TODO Load the state from a file and reset the cursor 
    
  }
};


  

// Initialize your game
// Call your game class with your assignment id, username, and api key
int main (int argc, char** argv) {
  my_game g(72, "BRIDGES_USER_ID", "BRIDGES_API_KEY");

  g.start();
}
