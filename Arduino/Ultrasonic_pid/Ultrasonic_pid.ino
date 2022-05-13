int trigger_pin = 2;
int echo_pin = 4;
float duration, distance1, distance, velocity, Kp, Kv, thrust;
float height = 100; //in cm
float mass = 0.822; //in kilograms
unsigned long t;
unsigned long t2;
void setup() {
Serial.begin (9600); 
pinMode (trigger_pin, OUTPUT); 
pinMode (echo_pin, INPUT);
}

void loop() {
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
 Serial.println("distance:");
 Serial.println(distance);
 Serial.println("velocity:");
 Serial.println(velocity);
 Kp=150;
 Kv=15;
 thrust = mass*(9.81+(Kv*(0-velocity)/100)+(Kp*(height-distance)/100));
 thrust = thrust*1000/9.81; //in grams
 if (thrust > 2000){
  thrust = 2000;
 }
 if (thrust <= 0){
  thrust = 0;
 } 
 Serial.println(thrust);
 delay (500);
}
