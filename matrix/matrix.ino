int DIN = 2;
int CS = 3;
int CLK = 4;
void setup() {
  pinMode(CS, OUTPUT);
  pinMode(DIN, OUTPUT);
  pinMode(CLK, OUTPUT);
  digitalWrite(CLK, LOW);
  latch(HIGH);//Hi is the default none load state

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  load(0x00, 0x00);
  load(0x01, 0x05);
  load(0x02, 0x04);
  load(0x03, 0x01);
  load(0x04, 0x04);
  load(0x05, 0x05);
  load(0x06, 0x06);
  load(0x07, 0x07);
  load(0x08, 0x08);
  load(0x09, 0x00);
  load(0x0A, 0x05);
  load(0x0B, 0x07);
  load(0x0C, 0x01);
  */
  load(0x01, 0x01);
  delay(10000);
}
//MSB is address and LSB is data
void load(byte MSB, byte LSB)
{
  //We will load MSB first
  latch(LOW);//Get rid
  delayMicroseconds(1);
  for (int a = 7; a >= 0; a--)
  {
    delayMicroseconds(1);
    if ((MSB & (1 << a)) == (0xFF & (1 << a)))
    {
      //Its a hi bit
      digitalWrite(DIN, HIGH);
    } else {
      //Its a low bit
      digitalWrite(DIN, LOW);
    }
    //First latch our bit
    delayMicroseconds(5);
    digitalWrite(CLK, HIGH); //Put the clk hi
    delayMicroseconds(10);//Clock pulse.
    digitalWrite(CLK, LOW); //Put the clk hi
    delayMicroseconds(10);//Clock pulse.
  }

  delayMicroseconds(10);

  for (int a = 7; a >= 0; a--)
  {
    delayMicroseconds(1);
    if ((LSB & (1 << a)) == (0xFF & (1 << a)))
    {
      //Its a hi bit
      digitalWrite(DIN, HIGH);
    } else {
      //Its a low bit
      digitalWrite(DIN, LOW);
    }
    //First latch our bit
    delayMicroseconds(5);
    digitalWrite(CLK, HIGH); //Put the clk hi
    delayMicroseconds(10);//Clock pulse.
    digitalWrite(CLK, LOW); //Put the clk hi
    delayMicroseconds(10);//Clock pulse.
  }
  //Now latch the data
  delayMicroseconds(5);
  digitalWrite(CLK, HIGH); //Put the clk hi
  delayMicroseconds(5);
  latch(HIGH);
  delayMicroseconds(5);
  digitalWrite(CLK, LOW); //Put the clk hi
  delayMicroseconds(50);
  digitalWrite(CLK, HIGH); //Put the clk hi
  delayMicroseconds(5);
  latch(LOW);
  delay(1);
  latch(HIGH);

}

void latch(int state)
{
  if (state == 1)
  {
    digitalWrite(CS, HIGH);
  } else {
    digitalWrite(CS, LOW);
  }
}
