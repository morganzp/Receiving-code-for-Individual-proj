#include <SoftwareSerial.h>
#define E2  10 // Enable Pin for motor 1
#define I3 8  // Control pin 1 for motor 
#define I4 9  // Control pin 2 for motor 
SoftwareSerial BTserial(2,3);//Rx, Tx
int led=7;
int led2=6;
boolean DEBUG = true;//brings up values for debugging if true on serial monitor
  
const byte maxDataLength = 20;          // maxDataLength is the maximum length allowed for received data.
char receivedChars[maxDataLength+1] ;
boolean newData = false;               // newData is used to determine if there is a new command
 
void setup()  
{
    pinMode(E2, OUTPUT);
    pinMode(I3, OUTPUT);
    pinMode(I4, OUTPUT);
    pinMode(8, OUTPUT); 
    pinMode(9, OUTPUT); 
    digitalWrite(7,LOW);
    digitalWrite(6,LOW);
 
    if (DEBUG)
    {
        Serial.begin(9600);
    }
 
    
    BTserial.begin(9600); 
    if (DEBUG)  {   Serial.println(F("Serial started at 9600"));     }
 
    newData = false;
 
}
 
 
 
void loop()  
{
         recvWithStartEndMarkers();                // check to see if we have received any new commands
         if (newData)  {   processCommand();  }    // if we have a new command do something
}
 
 
void processCommand()
{
    analogWrite(E2, 255); // Run in full speed
    newData = false;
    if (DEBUG)  {   Serial.print("recieved data = ");  Serial.println(receivedChars);         }
 
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
 
void recvWithStartEndMarkers() //checks incoming signal to make sure it falls within data constrictions. 
{
     static boolean recvInProgress = false;
     static byte ndx = 0;
     char startMarker = '<';
     char endMarker = '>';
 
     if (BTserial.available() > 0) 
     {
          char rc = BTserial.read();
          if (recvInProgress == true) 
          {
               if (rc != endMarker) 
               {
                    if (ndx < maxDataLength) { receivedChars[ndx] = rc; ndx++;  }
               }
               else 
               {
                     receivedChars[ndx] = '\0'; // terminate the string
                     recvInProgress = false;
                     ndx = 0;
                     newData = true;
               }
          }
          else if (rc == startMarker) { recvInProgress = true; }
     }
 
}
