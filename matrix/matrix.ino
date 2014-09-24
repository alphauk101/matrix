#include "matrix7219.h"

int DIN = 5;
int CS = 3;
int CLK = 4;

static unsigned long intTimer;
static int GAME_LVL;
static int tmpGAME_LVL;

static byte matrixData[8];//Our buffer so that we can send the display class what we want to display.
static byte snapShotData[8];//This will hold effectively a snap shot of the previous victory lines

//Create our new class object
Matrix matrix;

void setup() {
  //Init our driver.
  matrix.initDisplay(DIN,CS,CLK);
  Serial.begin(9600);
  delay(1000);

  attachInterrupt(0, intISR, RISING );

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
    if(tmpGAME_LVL > GAME_LVL){
      GAME_LVL=tmpGAME_LVL;//Try and keep this atomical as possible in arduino do this like this.
      //We need to also check is this is  successful hit.
      //We need to snap shot our matrix
      for(int a = 0 ; a < 8; a++){
        
        if(((matrixData[a] & (1 << a) == (snapShotData[a] & (1 << (a-1))) | 
        
        
        snapShotData[a] = (matrixData[a] | snapShotData[a]);//Snap shot new data with the old.
      }
      //Carry on
    }


    if(GAME_LVL != 8)
    {
      gameSpeed = (200 - (GAME_LVL*25));

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
      //delay(1000);
    }
    else{
      gameRunning = false;//GAME OVER MAN!
    }
  }

}

void intISR()
{
  long a = (unsigned long)(micros() - intTimer);
  //Serial.println(a);
  if(a  > 1000000)
  {
    tmpGAME_LVL++; 
    intTimer=micros();
  }
}

int paddleDir=0;//Use to determine which way the paddle show be moving
int gameCursor=0;
void processFrame(int level, int pSize){

  //We know how many px to make the paddle from pSize and we know what column by the level.
  resetMatrix();//This is important so our prevous data doesnt corrupt the new.

  //We are going this way
  //we need to establish which column is effected

  for(int a = 0; a < pSize; a++)
  {
    //Foreach pixel of paddle sixe
    matrixData[gameCursor+a] = ((0xFF) & (1<<level));//We need to also make our previous data appear.
  }

  if(paddleDir==0){
    gameCursor++;
    if((gameCursor+pSize) == 8){
      paddleDir=1;
    }
  }
  else
  {
    gameCursor--;
    if((gameCursor+pSize) == pSize)
    {
      paddleDir=0;
    }
  }

  for(int a = 0; a < 8; a++)
  {
    //Foreach pixel of paddle sixe
    matrixData[a] |= (byte) snapShotData[a];//We need to also make our previous data appear.
  }
/*
  Serial.print(matrixData[0],HEX);
  Serial.print(" : ");
  Serial.print(matrixData[1],HEX);
  Serial.print(" : ");
  Serial.print(matrixData[2],HEX);
  Serial.print(" : ");
  Serial.print(matrixData[3],HEX);
  Serial.print(" : ");
  Serial.print(matrixData[4],HEX);
  Serial.print(" : ");
  Serial.print(matrixData[5],HEX);
  Serial.print(" : ");
  Serial.print(matrixData[6],HEX);
  Serial.print(" : ");
  Serial.println(matrixData[7],HEX);
*/
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
  tmpGAME_LVL=0;
  paddleDir=0;
  gameCursor=0;
  snapShotData[0]=0;
  snapShotData[1]=0;
  snapShotData[2]=0;
  snapShotData[3]=0;
  snapShotData[4]=0;
  snapShotData[5]=0;
  snapShotData[6]=0;
  snapShotData[7]=0;
}














