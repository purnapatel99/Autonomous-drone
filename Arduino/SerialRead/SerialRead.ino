uint8_t incomingByte ; // for incoming serial data


void setup() {
  pinMode(11, INPUT);
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {
  // send data only when you receive data:
  if (pulseIn(11, HIGH)){
    Serial.print("1");
  }
  else {
    Serial.print("0");
  /*if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte);
    //delay(1000);*/
  }
}
