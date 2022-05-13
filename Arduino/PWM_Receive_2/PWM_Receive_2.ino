#define pwm1  11
#define pwm2  10
#define pwm3  9
int pwm_value1, pwm_value2, pwm_value3, t, t2;

void setup() {
  pinMode(pwm1, INPUT);
  pinMode(pwm2, INPUT);
  pinMode(pwm3, INPUT);
  Serial.begin(115200);
}

void loop() {
  t = millis();
  pwm_value1 = pulseIn(pwm1, HIGH);
  pwm_value2 = pulseIn(pwm2, HIGH);
  pwm_value3 = pulseIn(pwm3, HIGH);
  t2 = millis()-t;
  Serial.println(pwm_value1);
  Serial.println(pwm_value2);
  Serial.println(pwm_value3);
  Serial.println(t2);
  //delay(50);
}
