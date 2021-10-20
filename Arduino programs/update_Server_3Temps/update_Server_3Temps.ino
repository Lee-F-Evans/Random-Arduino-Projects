// Including the ESP8266 WiFi library
#include <ESP8266WiFi.h>


// my temp
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS D4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


//LCD 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display


// Replace with your network credentials
const char* ssid = "TP-Link_CA34";
const char* password = "69848728";


// Web Server on port 80
WiFiServer server(80);


//Timing stuff
unsigned long previousmilli = 0;
long Pontime = 3600000;
long Pofftime = 900000;
#define pump D6
#define fan D5

long LCDUpdate = 5000;

unsigned long previousmilliLCD = 0;

//-----------------------------------------------------------------------------

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(pump, OUTPUT);
  digitalWrite(pump, HIGH);

  pinMode(fan, OUTPUT);
  pinMode(fan,HIGH);

  // LCD initialization
  lcd.init();
  lcd.backlight();
  
  // Dallas temp sensor begin
  sensors.begin();

  // Connecting to WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Starting the web server
  server.begin();
  Serial.println("Web server running. Waiting for the ESP IP...");
  delay(5000);
  
  // Printing the ESP IP address
  Serial.println(WiFi.localIP());
  lcd.setCursor(0,3);
  lcd.print(WiFi.localIP());
}

//-----------------------------------------------------------------

void loop() {
  unsigned long currentmilli = millis();
  unsigned long currentmilliLCD = millis();
  

  sensors.requestTemperatures();
  
  // Listenning for new clients
  WiFiClient client = server.available();

    // Pump timing for low active optocoupler relay
    if ((digitalRead(pump) == LOW) && (currentmilli - previousmilli >= Pontime)) {
    previousmilli = currentmilli;
    digitalWrite(pump, 1);
  } else if ((digitalRead(pump) == HIGH) && (currentmilli - previousmilli >= Pofftime)) {
    previousmilli = currentmilli;
    digitalWrite(pump, 0);
  }

  // fan temp controls
  if(sensors.getTempCByIndex(2) >= 40 && digitalRead(fan) == HIGH){
    digitalWrite(fan, LOW); 
  }
    if(sensors.getTempCByIndex(2) <= 30 && digitalRead(fan) == LOW){
    digitalWrite(fan, HIGH);
  }

    // LCD update
    if (currentmilliLCD - previousmilliLCD >= LCDUpdate) {
    previousmilliLCD = currentmilliLCD;
    LCDtemp();
    }
  
  
  
  if (client) {
    Serial.println("New client");
    // bolean to locate when the http request ends
    boolean blank_line = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("Connection: close");
        client.println();
        // your actual web page that displays temperature and humidity
        client.println("<!DOCTYPE HTML>");
        client.println("<html>");
        client.println("<head></head><body><h1>Leo's Tower Temperature server</h1><h3>Tank: ");
        client.println(sensors.getTempCByIndex(0));
        client.println(" C</h3><h3>Ambient: ");
        client.println(sensors.getTempCByIndex(1));
        client.println(" C</h3><h3>Controls: ");
        client.println(sensors.getTempCByIndex(2));
        client.println(" C</h3><h3>");
        client.println("</body></html>");     
        break;
        if (c == '\n') {
          // when starts reading a new line
          blank_line = true;
        }
        else if (c != '\r') {
          // when finds a character on the current line
          blank_line = false;
        }
      }
    }  
    // closing the client connection
    delay(1);
    client.stop();
    Serial.println("Client disconnected.");
  }
}   

      
void LCDtemp (){
      lcd.setCursor(0,1);
      lcd.print("          ");
      lcd.setCursor(0,1);
      lcd.print("Ambient: ");
      lcd.print(sensors.getTempCByIndex(1));

      lcd.setCursor(0,0);
      lcd.print("          ");
      lcd.setCursor(0,0);
      lcd.print("Tank:    ");
      lcd.print(sensors.getTempCByIndex(0));

      lcd.setCursor(0,2);
      lcd.print("          ");
      lcd.setCursor(0,2);
      lcd.print("Controls:");
      lcd.print(sensors.getTempCByIndex(2));

}
