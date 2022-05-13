void setup() { 

  Serial.begin(115200); // Initialize serial with a baud rate of 115200 bps 

} 

 

void loop() { 

  // put your main code here, to run repeatedly: 
  int angle = 0;

  while(Serial.available() > 0) { 

    String input = Serial.readStringUntil('\n');
    int angle = input.toInt();
    angle = angle + 10;
    String a = (String)angle;
    Serial.println(input);
    //int a = (int)input - 48;
  }
    //delay(1000); 

  

} 
