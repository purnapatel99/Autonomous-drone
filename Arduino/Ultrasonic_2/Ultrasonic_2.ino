#include <NewPing.h>
#define TRIGGER_PIN  4  
#define ECHO_PIN     7  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
unsigned long t, t2;
int a, distance;
float velocity;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  
}
void loop() {
  a = distance;
  t = millis();
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  distance = sonar.ping_cm();
  t2 = millis();
  velocity = ((distance - a)*1000)/50;
  Serial.print("Distance: ");
  Serial.println(distance); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.print("Velocity ");
  Serial.println(velocity);
  
}
