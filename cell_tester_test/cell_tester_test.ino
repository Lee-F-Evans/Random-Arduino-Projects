#define PWM 9
#define Vin 6
#define Charge 7

void setup() {
pinMode(PWM,OUTPUT);
pinMode(Charge,OUTPUT);
pinMode(Vin, INPUT);


Serial.begin(115200);


digitalWrite(Charge,LOW);
analogWrite(PWM,0);
}

void loop() {
  Serial.print((float(analogRead(Vin))/1024)*5);
  Serial.print("\n");
  delay(1500);  
}
