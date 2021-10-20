// my temp
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


//LCD 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//Timing stuff
unsigned long previousmilli = 0;
long Pontime = 3600000;
long Pofftime = 900000;
#define pump 6
#define fan 5

long LCDUpdate = 2500;

unsigned long previousmilliLCD = 0;

//-----------------------------------------------------------------------------

void setup() {
  Serial.begin(115200);
  
  pinMode(pump, OUTPUT);
  digitalWrite(pump, HIGH);

  pinMode(fan, OUTPUT);
  digitalWrite(fan,HIGH);

  // LCD initialization
  lcd.init();
  lcd.backlight();
  
  // Dallas temp sensor begin
  sensors.begin();


  // boot up sequence
  digitalWrite(pump, LOW);
  digitalWrite(fan,LOW);
  lcd.setCursor(0,0);
  lcd.print("LOAD"); 
  
  for(int i =0;i<10;i++){
  lcd.print(".");
  delay(500);
  }
  digitalWrite(pump, HIGH);
  digitalWrite(fan, HIGH);

  lcd.setCursor(0,3);
  lcd.print("Check my water!"); 

}

//-----------------------------------------------------------------

void loop() {
  unsigned long currentmilli = millis();
  unsigned long currentmilliLCD = millis();

  sensors.requestTemperatures();

    // Pump timing for low active optocoupler relay
    if ((digitalRead(pump) == LOW) && (currentmilli - previousmilli >= Pontime)) {
    previousmilli = currentmilli;
    digitalWrite(pump, 1);
  } else if ((digitalRead(pump) == HIGH) && (currentmilli - previousmilli >= Pofftime)) {
    previousmilli = currentmilli;
    digitalWrite(pump, 0);
  }

  // fan temp controls
  if(sensors.getTempCByIndex(1) >= 40 && digitalRead(fan) == HIGH){
    digitalWrite(fan, LOW); 
  }
    if(sensors.getTempCByIndex(1) <= 30 && digitalRead(fan) == LOW){
    digitalWrite(fan, HIGH);
  }

    // LCD update
    if (currentmilliLCD - previousmilliLCD >= LCDUpdate) {
    previousmilliLCD = currentmilliLCD;
    LCDtemp();
    }
}   

      
void LCDtemp (){
      lcd.setCursor(0,1);
      lcd.print("            ");
      lcd.setCursor(0,1);
      lcd.print("Controls: ");
      lcd.print(sensors.getTempCByIndex(1));

      lcd.setCursor(0,0);
      lcd.print("            ");
      lcd.setCursor(0,0);
      lcd.print("Tank:    ");
      lcd.print(sensors.getTempCByIndex(0));

}
