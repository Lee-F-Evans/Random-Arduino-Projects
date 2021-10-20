#define PWM 9
#define Q1 7

void setup() {
pinMode(PWM,OUTPUT);
pinMode(Q1,OUTPUT);

analogWrite(PWM,0);
}

void loop() {
  analogWrite(PWM, 250);
  digitalWrite(Q1,HIGH);
  delay(2000);
  analogWrite(PWM, 125);
  digitalWrite(Q1,LOW);
  delay(2000);
  analogWrite(PWM, 0);
  digitalWrite(Q1,HIGH);
  delay(2000);  
}
