int latchPin = 13;  // Latch pin of 74HC595 is connected to Digital pin 5
int clockPin = 12; // Clock pin of 74HC595 is connected to Digital pin 6
int dataPin = 11;  // Data pin of 74HC595 is connected to Digital pin 4

byte  leds = B00000000; ; 
byte seg = B11111111;// Variable to hold the pattern of which LEDs are currently turned on or off
byte dis[] ={0x3,0x9F,0x25,0xD,0x99,0x49,0x41,0x1F,0x1,0x19,0x11,0xC1,0x63,0xC1,0x61,0x71};
//byte pos[] = {1,2,4,8,16,32,64,128};
//byte pos[] = {16,32,64,128,1,2,4,8};
byte pos[] = {8,4,2,1,128,64,32,16};
bool flag = 1;

/*
 * setup() - this function runs once when you turn your Arduino on
 * We initialize the serial connection with the computer
 */
void setup() 
{
  // Set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}

/*
 * loop() - this function runs over and over again
 */
void loop() 
{
  int number1 = 125;
  int number2 = 32;
 for (int i = 0; i < 8; i++) // Turn all the LEDs ON one by one.
  {
    leds = dis[i];
    seg=   pos[i];
    updateShiftRegister();
    delay(100);
  }
  
}

/*
 * updateShiftRegister() - This function sets the latchPin to low, then calls the Arduino function 'shiftOut' to shift out contents of variable 'leds' in the shift register before putting the 'latchPin' high again.
 */
void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   shiftOut(dataPin, clockPin, LSBFIRST, seg);
  digitalWrite(latchPin, HIGH);
}
