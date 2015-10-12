/****************************************************************
HC05 Bluetooth Master setup sketch

In the Serial Monitor ensure that 'Both NL and CR' is selected

AT+ORGL resets to factory settings
AT+ROLE=1  sets to Master mode
{AT+ROLE=0 sets to Slave mode)
AT+INQM=1,9,48   allows up to nine different Bluetooth devices to connect (one at a time)
AT+UART=9600,0,0 sets baud rate to 9600
AT+CMODE=1  connect to any Bluetooth Slave it can find

Note the HC05 will only connect to another HC05 or HC06 when in Master Mode
in Slave mode it will connect to any Master (mobile phone etc)

Connect the KEY pin to Vcc before applying power to switch to Command Mode
or press the button, if on is fixex, and apply power.

Once the parameters have been changed power down then power back up again

****************************************************************/
#include <SoftwareSerial.h>
SoftwareSerial bluetooth(2, 3); // RX, TX

void setup()
{
  // Start the hardware serial port
  Serial.begin(9600);
  pinMode(13, OUTPUT); // onboard LED
  digitalWrite(13, LOW); // switch OFF LED
  bluetooth.begin(38400);
}

void loop()
{
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

}
