#include <Servo.h>
#define SERVOS 6
Servo myservo[SERVOS];
int servo_pins[SERVOS] = {3,5,6,9,10,11};
int trigger_pin = 2;
int echo_pin = 4;
float duration, distance1, distance, velocity, Kp, Kv, thrust;
float mass = 0.822; //in kilograms
unsigned long t;
unsigned long t2;
void setup() { 
  Serial.begin(115200); // Initialize serial with a baud rate of 115200 bps 
  for(int i = 0; i < SERVOS; i++) {
    myservo[i].attach(servo_pins[i]);
}
 pinMode (trigger_pin, OUTPUT); 
 pinMode (echo_pin, INPUT);
} 

 

void loop() { 

  int angle = 0;
  String input, iHeight, iRoll, iYaw, iPitch, iAux1, iAux2;
  int Height, Roll, Yaw, Pitch, Aux1, Aux2, Throttle;

  if(Serial.available() > 0) { 

    input = Serial.readStringUntil('\n');
    iHeight = input.substring(1,4);
    iRoll = input.substring(5,8);
    iYaw = input.substring(9,12);
    iPitch = input.substring(13,16);
    iAux1 = input.substring(17,20);
    iAux2 = input.substring(21,24);
    Height = iHeight.toInt();
    Roll = iRoll.toInt();
    Yaw = iYaw.toInt();
    Pitch = iPitch.toInt();
    Aux1 = iAux1.toInt();
    Aux2 = iAux2.toInt();
    Throttle;
    Serial.println(input);
    Serial.println(Throttle);
    Serial.println(Roll);
    Serial.println(Yaw);
    Serial.println(Pitch);
    Serial.println(Aux1);
    Serial.println(Aux2);
  }
  t = millis();
  distance1 = distance;
  delay(10);
  digitalWrite (trigger_pin, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigger_pin, LOW);
  duration = pulseIn (echo_pin, HIGH);
  distance = (duration * 0.034) / 2;
  t2 = millis();
  velocity = ((distance - distance1)*10)/(t2 - t);
  Kp=150;
  Kv=15;
  thrust = mass*(9.81+(Kv*(0-velocity)/100)+(Kp*(Height-distance)/100));  //PID equation
  thrust = thrust*1000/9.81; //in grams
  if (thrust > 2000){
    thrust = 2000;
   }
  if (thrust <= 0){
    thrust = 0;
   } 
   Throttle = (thrust*110/2000)+45;
  Serial.println(Throttle);
  Serial.println(thrust); 
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
