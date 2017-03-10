/*
Receiving the Data from the UART to toggle the LED

Pinouts 
GPIO6 -> LED 1
GPIO7 -> LED 2
GPIO10 -> Rx
GPIO11 -> Tx

*/

//Import the Library needed
#include <SoftwareSerial.h>
#include <stdlib.h>

//Initialize the Serial Communication 
SoftwareSerial mySerial(10, 11); // RX, TX

//Code Initialization Starts
void setup() {
  //Setting the Baud to 9600 Bits/Second
  Serial.begin(9600);
  mySerial.begin(9600);

  //Setting up the LED Pins as the Output
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
}

void loop() {

  char num[2];

  //If the data is available serially, then receive it
  if(mySerial.available()>0){
    for(int i= 0 ;i<2;i++){
      num[i] = mySerial.read();
      delay(10);
    }
    
    int x;
    x = atoi(num);

  	//If the data matches, toggles the LED's
    switch(x){
      case 10:
        Serial.println("LED 1 LOW");
        digitalWrite(6,LOW);
        break;
      case 11:
        Serial.println("LED 1 HIGH");
        digitalWrite(6,HIGH);
        break;
      case 20:
        Serial.println("LED 2 LOW");
        digitalWrite(7,LOW);
        break;
      case 21:
        Serial.println("LED 2 HIGH");
        digitalWrite(7,HIGH);
        break;
    }
  }
}

//End of the Program


