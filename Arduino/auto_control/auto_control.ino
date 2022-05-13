#include <Servo.h>
#define SERVOS 4
#include <NewPing.h>
#define trigger_pin  2  
#define echo_pinZ    4  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define echo_pinX    7
#define max_distance 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define pwm1   13
#define pwm2   12
#define pwm3   11
unsigned long t, t2;
float aZ, aX, distanceZ, distanceX, Height, set_dist;
float velocityZ, velocityX, thrust;
int pwm_value1, pwm_value2, pwm_value3, Roll=93, Yaw=93, Pitch=93, Aux1, Aux2=40, Throttle=45;
NewPing sonarZ(trigger_pin, echo_pinZ, max_distance);
NewPing sonarX(trigger_pin, echo_pinX, max_distance);
Servo myservo[SERVOS];
int servo_pins[SERVOS] = {3,5,6,9};
float Kp1, Kv1, Kp2, Kv2;
float mass = 0.600; //in kilograms

void setup() { 
  Serial.begin(115200); // Initialize serial with a baud rate of 115200 bps 
  for(int i = 0; i < SERVOS; i++) {
    myservo[i].attach(servo_pins[i]);
  }
  pinMode(pwm1, INPUT);
  pinMode(pwm2, INPUT);
  pinMode(pwm3, INPUT);
} 

 

void loop() { 
  
  pwm_value1 = pulseIn(pwm1, HIGH);
  pwm_value2 = pulseIn(pwm2, HIGH);
  pwm_value3 = pulseIn(pwm3, HIGH);
  
  
  //delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  aZ = sonarZ.ping_cm();
  delay(50);
  aX = sonarX.ping_cm();
  delay(50);
  distanceZ = sonarZ.ping_cm();
  delay(50);
  distanceX = sonarX.ping_cm();
  velocityZ = ((distanceZ - aZ)*1000)/100;
  velocityX = ((distanceX - aX)*1000)/100;
  //aZ = distanceZ;
  //aX = distanceX;
  Serial.print("DistanceZ: ");
  Serial.println(distanceZ); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.print("DistanceX: ");
  Serial.println(distanceX);
  Serial.print("VelocityZ: ");
  Serial.println(velocityZ);
  Serial.print("VelocityX: ");
  Serial.println(velocityX);

  if (pwm_value1 > 1500){
    
    Kp1 = 2; //set for 10cm hovering height
    Kv1 = 0.3;
    Height = 10;
  
    thrust = (9.81+(Kv1*(0-velocityZ)/100)+(Kp1*(Height-distanceZ)/100))*950/9.81;  //PID equation
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
  if (pwm_value2 > 1500){
    
    Kp2 = 2; //set for 10cm hovering height
    Kv2 = 2.15;
    set_dist = 100; //(pwm_value3-1000)/5;
  
    Pitch=(-180/(9.81*3.14))*(0+(Kv2*(0-velocityX)/100)+(Kp2*(set_dist-distanceX)/100));
    Pitch=Pitch+93;
    Serial.println(Pitch);
    if (Pitch > 108){
      Pitch = 108;
    }
    else if (Pitch < 78){
      Pitch = 78;
    } 
  }
  else{
    Pitch = 93;
  }
  if (pwm_value3 > 1550 || pwm_value3 < 1450){
    Pitch = (pwm_value3*45)/500 + 93;
  }
   Serial.println(Pitch);
   myservo[0].write(Throttle); //Throttle
   delay(10);
   myservo[1].write(Roll); //Roll
   delay(10);
   myservo[2].write(Yaw); //Yaw
   delay(10);
   myservo[3].write(Pitch); //Pitch
   delay(10);

}
