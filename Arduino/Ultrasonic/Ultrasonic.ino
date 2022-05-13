int trigger_pin = 2;
int echo_pin = 4;
float duration;
float distance1;
float distance;
float velocity;
unsigned long elaspedtime;
unsigned long t;
unsigned long t2;
void setup() {
Serial.begin (115200); 
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
 delay(1000);
}
