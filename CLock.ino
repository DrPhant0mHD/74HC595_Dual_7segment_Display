#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>
#include <TimeLib.h>
int latchPin = 5;  // Latch pin of 74HC595 is connected to Digital pin 5
int clockPin = 4; // Clock pin of 74HC595 is connected to Digital pin 6
int dataPin = 2;  // Data pin of 74HC595 is connected to Digital pin 4

byte  leds = B00000000; ; 
byte seg = B11111111;// Variable to hold the pattern of which LEDs are currently turned on or off
byte dis[] ={0x3,0x9F,0x25,0xD,0x99,0x49,0x41,0x1F,0x1,0x19,0x11,0xC1,0x63,0xC1,0x61,0x71};
//byte pos[] = {1,2,4,8,16,32,64,128};
//byte pos[] = {16,32,64,128,1,2,4,8};
byte pos[] = {8,4,2,1,128,64,32,16};
bool flag = 1;

const char* ssid = "NOS-00DC";
const char* password = "WZTZTYZM";

char Time[] = "TIME:00:00:00";
char Date[] = "DATE:00/00/2000";
byte last_second, second_, minute_, hour_, day_, month_;
int year_;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

const long interval = 1000; 
unsigned long previousMillis = 0;

void setup(){
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    
  }

  timeClient.begin();
  
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
  timeClient.update();
  }
  
  unsigned long unix_epoch = timeClient.getEpochTime();

  second_ = second(unix_epoch);
  if (last_second != second_) {
 
    minute_ = minute(unix_epoch);
    hour_   = hour(unix_epoch);
  
 
    Time[12] = second_ % 10 + 48;
    Time[11] = second_ / 10 + 48;
    Time[9]  = minute_ % 10 + 48;
    Time[8]  = minute_ / 10 + 48;
    Time[6]  = hour_   % 10 + 48;
    Time[5]  = hour_   / 10 + 48;
 
    leds = dis[hour_   / 10 ];
    seg=   pos[0];
    updateShiftRegister();
    
    leds = dis[(hour_   % 10)+ 1 ];
    seg=   pos[1];
    updateShiftRegister();
    ;
     leds = dis[minute_ / 10 ];
    seg=   pos[3];
    updateShiftRegister();
    
     leds = dis[minute_ % 10 ];
    seg=   pos[4];
    updateShiftRegister();
    
     leds = dis[second_ / 10];
    seg=   pos[6];
    updateShiftRegister();
    
     leds = dis[second_ % 10 ];
    seg=   pos[7];
    updateShiftRegister();
    
Serial.print ( Time[6] );

  
 
}
}

  void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   shiftOut(dataPin, clockPin, LSBFIRST, seg);
  digitalWrite(latchPin, HIGH);
}
