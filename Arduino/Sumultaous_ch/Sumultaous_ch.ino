/*
Program: Control 6 SG90s Independently Using Arduino
File: control_6_sg90s_independently_using_arduino.ino
Description: Control 6 servos independently using Arduino.
Author: Addison Sears-Collins
Website: https://automaticaddison.com
Date: June 29, 2020
*/
  
#include <Servo.h>
 
// Define the number of servos
#define SERVOS 6
 
// Create the servo objects.
Servo myservo[SERVOS];  
 
// Attach servos to digital pins on the Arduino
int servo_pins[SERVOS] = {3,5,6,9,10,11}; 
 
void setup() {
   
  for(int i = 0; i < SERVOS; i++) {
     
    // Attach the servo to the servo object 
    myservo[i].attach(servo_pins[i]); 
 
    // Wait 500 milliseconds 
    //delay(500);  
  } 
}
  
void loop() {

   myservo[0].write(150); //Throttel
   delay(10);
   myservo[1].write(90); //Roll
   delay(10);
   myservo[2].write(80); //Yaw
   delay(10);
   myservo[3].write(140); //Pitch
   delay(10);
   myservo[4].write(70); //Aux1
   delay(10);
   myservo[5].write(140); //Aux2
   delay(10);
 
}
