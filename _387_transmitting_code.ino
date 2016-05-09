
#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3); // RX | TX because can't upload to pins 0/1 without having to unplug them first

 
boolean DEBUG = true;//when true reads more info out on serial monitor if you want extra info to debug; set to false if you don't care
int flexSensorPin1 = A0; //forward input on analog pin 
int flexSensorPin2 = A1; //reverse
int flexSensorPin3 = A2; //left steer
int flexSensorPin4 = A3; //right steer
int flexNumber1;//these are the mapped values of the analog read input values from the flex sensors
int flexNumber2;
int flexNumber3;
int flexNumber4;

void setup()  
{
    if (DEBUG)
    {
        // open serial communication for debugging and show 
        // the sketch filename and the date compiled
        Serial.begin(9600);
    }
 
    //  open software serial connection to the Bluetooth module.
    BTserial.begin(9600); 
    if (DEBUG)  {   Serial.println("BTserial started at 9600");     }
 
} // void setup()
 
 
void loop()  
{
 int flexSensorNumba1 = analogRead(flexSensorPin1);
 int flexSensorNumba2 = analogRead(flexSensorPin2);
 int flexSensorNumba3 = analogRead(flexSensorPin3);
 int flexSensorNumba4 = analogRead(flexSensorPin4);
// Serial.println(flexNumber2);

 flexNumber1=map(flexSensorNumba1,982,1017,0,100); //45
 flexNumber2=map(flexSensorNumba2,910,994,0,100); //16
 flexNumber3=map(flexSensorNumba3,982,1017,0,100); 
 flexNumber4=map(flexSensorNumba4,982,1017,0,100); 
 /*
  * This enables the motor to move in the forward direction by sending the FORWARD command
  */
 if (flexNumber1<65&&flexNumber2>65){
    BTserial.println("<FORWARD>");
    if (DEBUG){Serial.println("FORWARD command sent");
    Serial.println(flexNumber1);}    
    delay (50);
 }
 /*
  * This enables the motor to move in the reverse direction by sending the REVERSE command
  */
    if (flexNumber2<65&&flexNumber1>65){
    BTserial.println("<REVERSE>");
    if (DEBUG){Serial.println("REVERSE command sent");
    Serial.println(flexNumber2);}      
    delay (50);    
 }
 /*
  * The following code is to prevent the motor from locking and overheating. When the user is trying to make it go 
  * forward or backward at the same time, this causes strain on the motor becuase voltage is tring to spread across
  * the motor in both directions. To prevent this from ruining the motor, a STILL command is sent when this happens
  * disabling the motor entirely until the user makes up their mind on which direction they want to go.
  */
if((flexNumber1<65&&flexNumber2<65)||(flexNumber1>=65&&flexNumber2>=65)){
    BTserial.println("<STILL>");
    if (DEBUG){Serial.println("STILL command sent");
    Serial.println(flexNumber1);}      
    delay (50);    
 }
}
