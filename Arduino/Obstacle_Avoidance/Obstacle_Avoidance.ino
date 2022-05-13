#include <Servo.h>
#define SERVOS 6
Servo myservo[SERVOS];
int servo_pins[SERVOS] = {3,5,6,9,10,11};
int trigger_pin = 2;
int echo_pin1 = 4;
int echo_pin2 = 7;
int echo_pin3 = 8;
int echo_pin4 = 12;
//int echo_pin1 = 13; //for 5th ultrasoic sensor
float duration1, duration2, duration3, duration4, distance1, distance2, distance3, distance4, velocity1, velocity2, velocity3, velocity4, thrust, a, b, c, d;
float Kp1 = 150;
float Kv1 = 15;
float Kp2 = 8;
float Kv2 = 8;
float Kp3 = 8;
float Kv3 = 8;
float Kp4 = 8;
float Kv4 = 8;
float mass = 0.822; //in kilograms
unsigned long t;
unsigned long t2;
void setup() { 
  Serial.begin(115200); // Initialize serial with a baud rate of 115200 bps 
  for(int i = 0; i < SERVOS; i++) {
    myservo[i].attach(servo_pins[i]);
}
 pinMode (trigger_pin, OUTPUT); 
 pinMode (echo_pin1, INPUT);
 pinMode (echo_pin2, INPUT);
 pinMode (echo_pin3, INPUT);
 pinMode (echo_pin4, INPUT);
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
  a = distance1;
  b = distance2;
  c = distance3;
  d = distance4;
  delay(10);
  digitalWrite (trigger_pin, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigger_pin, LOW);
  duration1 = pulseIn (echo_pin1, HIGH);
  distance1 = (duration1 * 0.034) / 2;
  duration2 = pulseIn (echo_pin2, HIGH);
  distance2 = (duration2 * 0.034) / 2;
  duration3 = pulseIn (echo_pin3, HIGH);
  distance3 = (duration3 * 0.034) / 2;
  duration4 = pulseIn (echo_pin4, HIGH);
  distance4 = (duration4 * 0.034) / 2;
  t2 = millis();
  velocity1 = ((distance1 - a)*10)/(t2 - t);
  velocity2 = ((distance2 - b)*10)/(t2 - t);
  velocity3 = ((distance3 - c)*10)/(t2 - t);
  velocity4 = ((distance4 - d)*10)/(t2 - t);
  
  thrust = mass*(9.81+(Kv1*(0-velocity1)/100)+(Kp1*(Height-distance1)/100));  //PID equation
  thrust = thrust*1000/9.81; //in grams
  if (thrust > 2000){
    thrust = 2000;
   }
  if (thrust <= 0){
    thrust = 0;
   } 
   Throttle = (thrust*110/2000)+45;

  if (distance2 < 100){    //at front
    Pitch=(-180/(9.81*3.14))*(0+Kv2*(0-velocity2)+Kp2*(100-distance2));
    Pitch=Pitch+90;
  }

  if (distance3 < 100){    //right side
    Roll=(-180/(9.81*3.14))*(0+Kv3*(0-velocity3)+Kp3*(100-distance3));
    Roll=Roll+90;
  }

  if (distance4 < 100){    //left side
    Roll=(-180/(9.81*3.14))*(0+Kv4*(0-velocity4)+Kp4*(100-distance4));
    Roll=-Roll+90;
  }
  
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
