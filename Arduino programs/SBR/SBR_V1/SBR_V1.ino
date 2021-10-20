/* Board is ESP8266, motor driver is L298N, and 2 DC geared motors at 100RPM max pwm
PWM1 = D3;
PWM2 = D4;

EN1 = D5;
EN2 = D6;
EN3 = D7;
EN4 = D8;
*/

#define PWM1 D3
#define PWM2 D4
#define EN1 D5
#define EN2 D6
#define EN3 D7
#define EN4 D8
#define Pot A0

void setup() {
  Serial.begin(9600);
  analogWrite(PWM1,0);
  analogWrite(PWM2,0);

  pinMode(EN1,OUTPUT);
  pinMode(EN2,OUTPUT);
  pinMode(EN3,OUTPUT);
  pinMode(EN4,OUTPUT);  
}

void loop() {
  int PWM = (float(analogRead(Pot))/1024)*256;
  Serial.print(PWM);
  Serial.print("\n");
  analogWrite(PWM1,PWM);
  analogWrite(PWM2,PWM);

  
  //delay(1000);
  Motor1("FWD");
  Motor2("FWD");
 // delay(2000);
 // Motor1("RVS");
 // Motor2("RVS");
 // delay(2000);
    
}
