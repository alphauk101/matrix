#include "matrix7219.h"

int DIN = 2;
int CS = 3;
int CLK = 4;

static int GAME_LVL;

byte matrixData[8];//Our buffer so that we can send the display class what we want to display.

//Create our new class object
Matrix matrix;

void setup() {
  //Init our driver.
  matrix.initDisplay(DIN,CS,CLK);
  Serial.begin(9600);
  delay(1000);
}

void loop() {

  //We need to set anything here before we start our main game loop

    newGame();//Resets the game to beginning.
  /*
  matrixData[0] = 0x10;
   matrixData[1] = 0x02;
   matrixData[2] = 0x04;
   matrixData[3] = 0x08;
   matrixData[4] = 0x10;
   matrixData[5] = 0x20;
   matrixData[6] = 0x40;
   matrixData[7] = 0x80;
   matrix.updateDisplay(matrixData);
   delay(1000);
   */
  gameLoop();//Start the game.
}


/**********************************
 * //This represents are main game loop
 ***********************************/
void gameLoop(){
  int gameSpeed;
  int paddleSize;
  boolean gameRunning = true;
  //First we need to calculate exactly everything that should be on the screen based on the game variables.
  //What level are we.
  gameSpeed = ((GAME_LVL+10)*10);//First set our speed (effectively the speed of the loop.

  while(gameRunning == true){
    //The game loop will run whist the gameRunnning variable is true;

    //Depending on what the game level is determines the paddle size.
    if(GAME_LVL < 3){//Our paddle size depends on the gae level.
      paddleSize=3;//This means that our paddle is 3 pixels big
    } 
    else if(GAME_LVL < 5){
      paddleSize=2;
    }
    else{
      paddleSize=1;
    }
    processFrame(GAME_LVL,paddleSize);//display next frame.

    delay(gameSpeed);//This is important because this effects the overall gamespeed/difficulty.

  }

}


int paddleDir=0;//Use to determine which way the paddle show be moving
int gameCursor=0;
void processFrame(int level, int pSize){
  Serial.println(gameCursor,HEX);
  //We know how many px to make the paddle from pSize and we know what column by the level.
  resetMatrix();//This is important so our prevous data doesnt corrupt the new.
  if(paddleDir==0){
    //We are going this way
    //we need to establish which column is effected

    for(int a = 0; a < pSize; a++)
    {
      //Foreach pixel of paddle sixe
      matrixData[gameCursor+a] = ((0xFF) & (1<<level));
    }
    gameCursor++;
    if((gameCursor+pSize) == 8){
      paddleDir=1;
    }
  }
  else
  {
    for(int a = 0; a < pSize; a++)
    {
      //Foreach pixel of paddle sixe
      matrixData[gameCursor+a] = ((0xFF) & (1<<level));
    }
    gameCursor--;
    if((gameCursor+pSize) == pSize)
    {
      paddleDir=0;
    }
  }


  matrix.updateDisplay(matrixData);
}

void resetMatrix(){
  matrixData[0]=0;
  matrixData[1]=0;
  matrixData[2]=0;
  matrixData[3]=0;
  matrixData[4]=0;
  matrixData[5]=0;
  matrixData[6]=0;
  matrixData[7]=0;  
}

/*************
 * //Resets all the parameters for a new game.
 *************/
void newGame(){
  GAME_LVL=0;
}








