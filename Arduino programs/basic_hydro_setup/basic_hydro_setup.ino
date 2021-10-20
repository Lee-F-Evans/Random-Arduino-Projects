int pump = 5;
int pumpstate = LOW;
unsigned long previousmilli1 = 0;
long pumpontime = 120000;     // 2 min on
long pumpofftime = 7200000;   // 2 hr off/ 8 cycles per 16 hr period

int fan = 3;
int fanstate = LOW;
unsigned long previousmilli2 = 0;
long fanontime = 600000;     // 10 min on
long fanofftime = 600000;    // 10 min off

void setup() {
 pinMode(pump,OUTPUT);
 pinMode(fan,OUTPUT);

digitalWrite(pump, HIGH);
delay(90000);
digitalWrite(pump, LOW);
}

void loop() {

  unsigned long currentmilli1 = millis();
  if ((pumpstate == HIGH) && (currentmilli1 - previousmilli1 >= pumpontime)) {
    pumpstate = LOW;
    previousmilli1 = currentmilli1;
    digitalWrite(pump, pumpstate);
  } else if (((pumpstate == LOW) && (currentmilli1 - previousmilli1 >= pumpofftime))) {
    pumpstate = HIGH;
    previousmilli1 = currentmilli1;
    digitalWrite(pump, pumpstate);
  }



  unsigned long currentmilli2 = millis();
  if ((fanstate == HIGH) && (currentmilli2 - previousmilli2 >= fanontime)) {
    fanstate = LOW;
    previousmilli2 = currentmilli2;
    digitalWrite(fan, fanstate);
  } else if ((fanstate == LOW) && (currentmilli2 - previousmilli2 >= fanofftime)) {
    fanstate = HIGH;
    previousmilli2 = currentmilli2;
    digitalWrite(fan, fanstate);
  }
}
