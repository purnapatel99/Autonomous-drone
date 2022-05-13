#include <Servo.h>
#define SERVOS 6
#include <NewPing.h>
#define TRIGGER_PIN  4  
#define ECHO_PIN     7  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
unsigned long t, t2;
float a, distance, Height;
float velocity, thrust;
volatile int pwm_value = 0;
volatile int prev_time = 0;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Servo myservo[SERVOS];
int servo_pins[SERVOS] = {3,5,6,9,10,11};
float Kp1;
float Kv1;
float mass = 0.600; //in kilograms

void rising() {
  attachInterrupt(0, falling, FALLING);
  prev_time = micros();
}
 
void falling() {
  attachInterrupt(0, rising, RISING);
  pwm_value = micros()-prev_time;
  //Serial.println(pwm_value);
}

void setup() { 
  Serial.begin(115200); // Initialize serial with a baud rate of 115200 bps 
  for(int i = 0; i < SERVOS; i++) {
    myservo[i].attach(servo_pins[i]);
  }
  attachInterrupt(0, rising, RISING);
} 

 

void loop() { 

  //int angle = 0;
  //String input, iHeight, iRoll, iYaw, iPitch, iAux1, iAux2;
  int Height, Roll=93, Yaw=93, Pitch=93, Aux1, Aux2=40, Throttle=45;

  if (pwm_value > 1000){
    a = distance;
    t = millis();
    delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    distance = sonar.ping_cm();
    t2 = millis();
    velocity = ((distance - a)*1000)/50;
    Serial.print("Distance: ");
    Serial.println(distance); // Send ping, get distance in cm and print result (0 = outside set distance range)
    //Serial.print("Velocity ");
    //Serial.println(velocity);
    Kp1 = 3; //set for 10cm hovering height
    Kv1 = 1;
    Height = (pwm_value-1000)/10;
  
    thrust = (9.81+(Kv1*(0-velocity)/100)+(Kp1*(Height-distance)/100))*1000/9.81;  //PID equation
    //thrust = thrust*1000/9.81; //in grams
    Serial.println(thrust);
    if (thrust > 1200){
      Throttle = (1.2*40)+45;
    }
    else if (thrust <= 0){
      Throttle = 45;
    } 
    else{
    Throttle = (thrust*40/1000)+45;
    }
  }
  else {
    Throttle = 45;   
  }
   Serial.println(Throttle);
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
