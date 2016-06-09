#include "IRremote.h"
#include "Servo.h"
 

int receiver = 6; // Signal Pin of IR receiver  -> Digital I/O Pin 6
int ledPin = 9;   // Signal Pin of LED          -> Digital I/O Pin 9
int pos = 0;      // Variable to store the servo position
 
IRrecv irObj(receiver);    // create instance of IR Receiver
decode_results results;    // create instance to decode IR Signal
Servo servoObj;            // create instance of Servo


void runServo(int hexSignal) {
    
    switch(hexSignal)
 
    {
 
      case 0xFF629D: // UP button pressed
                      digitalWrite(ledPin, HIGH);

                      for (int i=0; i<10; i++) {
                      
                        for (pos = 10; pos <= 50; pos ++) { 
                          servoObj.write(pos);               
                          delay(15);                       
                        }
                        
                        for (pos = 50; pos >= 10; pos --) { 
                          servoObj.write(pos);               
                          delay(15);                        
                        }
                      }

                      digitalWrite(ledPin, LOW);
                      break;
                      
    }

    irObj.resume(); // receive the next value
}
 
void setup()
{ 
    pinMode(ledPin, OUTPUT);
    servoObj.attach(4);
    irObj.enableIRIn(); // Start receiving IR
}
 
void loop()
{
    if (irObj.decode(&results)) // Check if IR Signal is received
     
      {
        runServo(results.value);     
      }  
 
}



