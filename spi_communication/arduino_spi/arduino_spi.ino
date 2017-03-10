/*
SPI Pin outs

MOSI -> GPIO11
MISO -> GPIO12
SCK  -> GPIO13
SS   -> GPIO10

LED_1 -> GPIO6
LED_2 -> GPIO7
*/

//Import the Library
#include <SPI.h>
#include <stdlib.h>

char buf [100];
volatile byte pos;
volatile boolean process_it;

void setup (void)
{
  //Start the Serial for the debugging
  Serial.begin (115200);   

  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);
  pinMode(10,INPUT);

  //Setting up the LED pin as OUTPUT
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  
  // turn on SPI in slave mode
  SPCR |= _BV(SPE);
  
  // get ready for an interrupt 
  pos = 0;   // buffer empty
  process_it = false;

  // now turn on interrupts
  SPI.attachInterrupt();

}  // end of setup


// SPI interrupt routine
ISR (SPI_STC_vect)
{
byte c = SPDR;  // grab byte from SPI Data Register
  if(digitalRead(10)==0){
  // add to buffer if room
  if (pos < sizeof buf)
    {
    buf [pos++] = c;
    
    // example: newline means time to process buffer
    if (c == '\n')
      process_it = true;
      
    }  // end of room available
  }
}  // end of interrupt routine SPI_STC_vect

// main loop - wait for flag set in interrupt routine
void loop (void)
{
  if (process_it)
  {
    buf [pos] = 0;
    int buff = atoi(buf);  
    Serial.println (buff);
    switch(buff){
      case 10:
        digitalWrite(6,HIGH);
        digitalWrite(7,LOW);
        break;
      case 11:
        digitalWrite(6,LOW);
        digitalWrite(7,HIGH);
        break;
    }
    pos = 0;
    process_it = false;
  }  // end of flag set
    
}  

// end of program

