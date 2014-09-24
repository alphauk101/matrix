#ifndef MATRIX_7219
#define MATRIX_7219

#include <arduino.h>

/*DEFINES*/
#define DEFAULT_INTENSITY 0x07
#define DECODEMODE_NO_DECODE 0x00
#define DECODEMODE_CODE_B_D1-7 0x01
#define DECODEMODE_CODE_B_D1-3_NO_DECODE_D4-7 0x0F
#define DECODEMODE_CODE_B_D0-7 0xFF
//Data defines
#define CLOCK_PULSE_WIDTH 10//In Micro seconds


class Matrix{
public:
  void initDisplay(int,int,int);//Initialises our display.-init(DIN pin, CS pin, CLK pin)
  void setIntensity(int);//Default to 7 (range 0 - 15)
  void testDisplay(void);//Simply puts display into test mode (all leds)
  void setDecodeMode(byte);//Sets the mode according to the DS table 4 decode mode.
  void updateDisplay(byte*);//The big one that applies the bytes to the screen
private: 
  inline void setClock(int);
  inline void setLatch(int);
  void shift(byte, byte);//Shifts these 16 bits in
};
#endif

