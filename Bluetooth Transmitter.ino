/******************************************************************************
OLEd Bluetooth Transmitter

by Chris Rouse Oct 2015
 
HC05  Bluetooth Transmitter/Receiver

Wire HC05
This is a 3v device and although the board has a 3v regulator
the connections will need a logic level convertor
  Vcc to Arduino 5 volts
  Gnd to Arduino Gnd
  Tx to Arduino pin 2
  Rx to Arduino pin 3
  
Wire TMP 36
 Vcc to Arduino 5 volts
 Gnd to Arduino Gnd
 Signal to Arduino Analog pin 0

******************************************************************************/

#include <SoftwareSerial.h>
SoftwareSerial bluetooth(2, 3); // RX, TX
//TMP36 Pin Variables
int tempPin = 14; //the analog pin the TMP36's Vout (sense) pin is connected to
//the resolution is 10 mV / degree centigrade with a
//500 mV offset to allow for negative temperatures
int tempReading; // the analog reading from the sensor
double aref_voltage = 5.0;
String stringTemp = "";

void setup()
{
  // Start the hardware serial port
  Serial.begin(9600);
  // use pin 4 to activate KEY
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);    
  bluetooth.begin(9600);
}

void loop()
{
  // get temperature
  tempReading = analogRead(tempPin); 
  // converting that reading to voltage, which is based off the reference voltage
  float voltage = tempReading * aref_voltage;
  voltage /= 1024.0;
  float temperatureC = (voltage - 0.5) * 100 ; //converting from 10 mv per degree with 500 mV offset
  // now send it
  //
  stringTemp = String(int(temperatureC));
  bluetooth.print(stringTemp + "\260C#");
  digitalWrite(13, HIGH); 
  delay(500);
  digitalWrite(13, LOW);  
  //
  bluetooth.listen();
  // while there is data coming in, read it
  // and send to the hardware serial port:
  while (bluetooth.available() > 0) {
    char inByte = bluetooth.read();
    Serial.write(inByte);
  }
  
   // Read user input if available.
 if (Serial.available()){
 delay(10); // The DELAY!
 bluetooth.write(Serial.read());
 }
 
 delay(1500);
}
