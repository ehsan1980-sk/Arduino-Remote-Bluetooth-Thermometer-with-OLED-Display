/******************************************************************************
OLEd Bluetooth Receiver using U8GLIB Library

visit https://code.google.com/p/u8glib/ for full details of the U8GLIB library and
full instructions for use.

by Chris Rouse Oct 2015

Using a IIC 128x64 OLED with SSD1306 chip
 
HC05 or HC06 Bluetooth Receiver

Wire OLED:
  VCC +5v
  GND GND
  SDA Analog pin 4
  SCL Analog pin 5

Wire HC05/06
This is a 3v device and although the board has a 3v regulator
the connections will need a logic level convertor
  Vcc to Arduino 5 volts
  Gnd to Arduino Gnd
  Tx to Arduino pin 2 through a logic level converter
  Rx to Arduino pin 3 through a logic level converter

******************************************************************************/

// Add libraries
  #include "U8glib.h"
  #include <SPI.h>
  #include <Wire.h>  
  #include <SoftwareSerial.h>  
  SoftwareSerial bluetooth(2, 3); // RX, TX
// setup u8g object
  U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);	// I2C 
//
  String inputString = "";
  boolean stringComplete = false;
  boolean flip = false;

void draw(void) {
  u8g.setFont(u8g_font_profont12);
  u8g.drawStr(1,10, "Bluetooth Thermometer");
  u8g.setFont(u8g_font_helvR24);  
  if (flip){u8g.drawStr(110,64, "*");}
  else{u8g.drawStr(110,64, " ");}  
  const char* newData = (const char*) inputString.c_str();
  u8g.drawStr(20,50,newData);
}

void drawOpen(void){
  // waits for Bluetooth connection
  u8g.setFont(u8g_font_profont12);
  u8g.drawStr(1,10, "Waiting for Bluetooth");
  u8g.drawStr(35,30, "connection");  
}

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);  
  Wire.begin();
  inputString.reserve(200);
  u8g.firstPage();  
    do {
      drawOpen();
    } while( u8g.nextPage() ); 
}

void loop() {
  Serial.println(stringComplete);
  serialEvent();
  if(stringComplete){
    Serial.println(inputString); 
    u8g.firstPage();  
    do {
      draw();
    } while( u8g.nextPage() );      
    inputString = "";
    stringComplete = false;
    
  }
  // rebuild the picture after some delay
  delay(50);

}

void serialEvent(){
  while (bluetooth.available()){
    char inChar = (char)bluetooth.read();
    if (inChar == '#') {
      stringComplete = true;
      flip = !flip; // used to flash bluetooth received sign
    }
    else{
      inputString += inChar;
    }
  }
  
}
