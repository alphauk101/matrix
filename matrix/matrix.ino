#include "matrix7219.h"

int DIN = 2;
int CS = 3;
int CLK = 4;

byte columns[8];//This represents each column
byte columns2[8];

//Create our new class object
Matrix matrix;

void setup() {
  //Init our driver.
  matrix.initDisplay(DIN,CS,CLK);

  Serial.begin(9600);
  delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:

  columns[0] = 0xFF;
  columns[1] = 0x18; 
  columns[2] = 0x18; 
  columns[3] = 0x18; 
  columns[4] = 0x18; 
  columns[5] = 0x18; 
  columns[6] = 0x18; 
  columns[7] = 0xFF; 
  
  matrix.updateDisplay(columns);
  delay(50);
  
  columns2[0] = 0x55;
  columns2[1] = 0xAA; 
  columns2[2] = 0x55; 
  columns2[3] = 0xAA; 
  columns2[4] = 0x55; 
  columns2[5] = 0xAA; 
  columns2[6] = 0x55; 
  columns2[7] = 0xAA; 

  //matrix.updateDisplay(columns2);
  delay(50);
}


