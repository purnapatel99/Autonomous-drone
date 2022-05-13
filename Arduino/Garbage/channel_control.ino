#include <Servo.h>
 
// Define the number of servos
#define CH 6
 
// Define the number of states
#define STATES 7
 
// Create the servo objects.
Servo channel[CH];  
 
// Attach servos to digital pins on the Arduino
int ch_pins[CH] = {3,5,6,9,10,11}; 
 
// Potential angle values of the servos in degrees
int angle_states[STATES] = {180, 150, 120, 90, 60, 30, 0};
 
void setup() {
   
  for(int i = 0; i < CH; i++) {
     
    // Attach the servo to the servo object 
    channel[i].attach(ch_pins[i]); 
 
    // Wait 500 milliseconds 
    delay(500);  
  } 
}
  
void loop() {
    for(int i = 0; i<=180 ; i++) {
    channel[0].write(i);
     }
    delay(10);
    for(int i = 0; i<=150 ; i++) {
    channel[1].write(i);
     }
    delay(10);
    for(int i = 0; i<=120 ; i++) {
    channel[2].write(i);
     }
    delay(10);
    for(int i = 0; i<=90 ; i++) {
    channel[3].write(i);
     }
    delay(10);
    for(int i = 0; i<=60 ; i++) {
    channel[4].write(i);
     }
    delay(10);
    for(int i = 0; i<=30 ; i++) {
    channel[5].write(i);
     }
    delay(10);
     }
 
  // Move in one direction.
  /*for(int i = 0; i < STATES; i++) {
     
    channel[0].write(angle_states[i]);
    delay(10);
    channel[1].write(angle_states[i]);
    delay(10);
    channel[2].write(angle_states[i]);
    delay(10);
    channel[3].write(angle_states[i]);
    delay(10);
    channel[4].write(angle_states[i]);
    delay(10);
    channel[5].write(angle_states[i]);
    delay(100); 
  }
 
  // Move in the other direction
  for(int i = (STATES - 1); i >= 0; i--) {
     
    channel[0].write(angle_states[i]);
    delay(10);
    channel[1].write(angle_states[i]);
    delay(10);
    channel[2].write(angle_states[i]);
    delay(10);
    channel[3].write(angle_states[i]);
    delay(10);
    channel[4].write(angle_states[i]);
    delay(10);
    channel[5].write(angle_states[i]);
    delay(100); 
  }
}*/
