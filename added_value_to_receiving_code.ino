#include <SoftwareSerial.h>
#define E2  10 // Enable Pin for motor 1
#define I3 8  // Control pin 1 for motor 
#define I4 9  // Control pin 2 for motor 
SoftwareSerial BTserial(2,3);//Rx, Tx
int led=7;
int led2=6;

void setup() {
   pinMode(E2, OUTPUT);
    pinMode(I3, OUTPUT);
    pinMode(I4, OUTPUT);
    pinMode(8, OUTPUT); 
    pinMode(9, OUTPUT); 
    digitalWrite(7,LOW);
    digitalWrite(6,LOW);

}

void processCommand()
{
    analogWrite(E2, 255); // Run in full speed
 
      if      (strcmp ("FORWARD",receivedChars) == 0)  { 
        digitalWrite(7,HIGH); 
        digitalWrite(I3, HIGH);//these are pins that will reverse the output motor;
        digitalWrite(I4, LOW);
        }
      else if (strcmp ("STILL",receivedChars) == 0) { //this says if both flex sensors are being activated or not being activated
        digitalWrite(6,LOW);                          //then it tells the motor to do nothing  
        digitalWrite(7,LOW);    
        digitalWrite(I3, LOW);
        digitalWrite(I4, LOW);
    }
      else if (strcmp ("REVERSE",receivedChars) == 0) { 
        digitalWrite(6,HIGH);    
        digitalWrite(I3, LOW);
        digitalWrite(I4, HIGH);
    }
   
}
