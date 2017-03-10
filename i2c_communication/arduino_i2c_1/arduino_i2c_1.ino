/*
  I2C Pinouts

  SDA -> A4
  SCL -> A5
*/

//Import the library required
#include <Wire.h>

//Slave Address for the Communication
#define SLAVE_ADDRESS 0x04

char number[50];
int state = 0;

//Code Initialization
void setup() {
  // initialize i2c as slave
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  // define callbacks for i2c communication
  Wire.onReceive(receiveData);
  //  Wire.onRequest(sendData);
}

void loop() {
  delay(100);
} // end loop

// callback for received data
void receiveData(int byteCount) {
  int i = 0;
  while (Wire.available()) {
    number[i] = Wire.read();
    i++;
  }
  number[i] = '\0';
  Serial.print(number);
}  // end while

// callback for sending data
void sendData() {
  Wire.write(number);
}

//End of the program
