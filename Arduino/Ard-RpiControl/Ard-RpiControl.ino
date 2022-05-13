#include <Servo.h>
#define SERVOS 6
Servo myservo[SERVOS];
int servo_pins[SERVOS] = {3,5,6,9,10,11};
void setup() { 
  Serial.begin(115200); // Initialize serial with a baud rate of 115200 bps 
  for(int i = 0; i < SERVOS; i++) {
    myservo[i].attach(servo_pins[i]);
}
} 

 

void loop() { 

  int angle = 0;

  while(Serial.available() > 0) { 

    String input = Serial.readStringUntil('\n');
    String iThrottle = input.substring(1,4);
    String iRoll = input.substring(5,8);
    String iYaw = input.substring(9,12);
    String iPitch = input.substring(13,16);
    String iAux1 = input.substring(17,20);
    String iAux2 = input.substring(21,24);
    int Throttle = iThrottle.toInt();
    int Roll = iRoll.toInt();
    int Yaw = iYaw.toInt();
    int Pitch = iPitch.toInt();
    int Aux1 = iAux1.toInt();
    int Aux2 = iAux2.toInt();
    Serial.println(input);
    Serial.println(Throttle);
    Serial.println(Roll);
    Serial.println(Yaw);
    Serial.println(Pitch);
    Serial.println(Aux1);
    Serial.println(Aux2);    
   myservo[0].write(Throttle); //Throttle
   delay(10);
   myservo[1].write(Roll); //Roll
   delay(10);
   myservo[2].write(Yaw); //Yaw
   delay(10);
   myservo[3].write(Pitch); //Pitch
   delay(10);
   myservo[4].write(Aux1); //Aux1
   delay(10);
   myservo[5].write(Aux2); //Aux2
   delay(10);
   

  
  }
} 
