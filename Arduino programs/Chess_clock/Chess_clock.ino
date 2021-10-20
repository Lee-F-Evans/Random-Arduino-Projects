
int button1 = 9;
int button2 = 8;
int button3 = 7;
int button4 = 6;

int mode = 0;
int state1 = 2;

int Min1b = 1;
int Min2b = 0;
int sec1b = 0;
int sec2b = 0;

int Min1a = 1;
int Min2a = 0;
int sec1a = 0;
int sec2a = 0;

int reset = 0;

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);

  lcd.begin(16, 2);
  lcd.setCursor(2, 0);
  lcd.print("Bring it on");
  lcd.setCursor(5, 1);
  lcd.print("Nerd!");
  delay(4000);

  lcd.begin(16, 2);
  lcd.setCursor(1, 0);
  lcd.print("Set Game Time!");

  settime();
}




void loop() {

  modeselect();

  if (mode == 0) {
    if (digitalRead(button1) == HIGH && Min2a < 9) {
      zeroout();
      Min2a ++;
      Min2b ++;
      settime();
      delay(700);
    } else if (digitalRead(button1) == HIGH && Min2a == 9) {
      zeroout();
      Min1a++;
      Min1b++;
      Min2a = 0;
      Min2b = 0;
      settime();
      delay(700);
    }

    if (digitalRead(button2) == HIGH && (Min2a > 0 || Min2b > 0)) {
      zeroout();
      Min2a --;
      Min2b --;
      settime();
      delay(400);
    } else if (digitalRead(button2) == HIGH && (Min2a == 0 || Min2b == 0) && (Min1a > 0 || Min2a > 0)) {
      zeroout();
      Min1a--;
      Min1b--;
      Min2a = 9;
      Min2b = 9;
      settime();
      delay(400);
    }

  }

  if (mode == 1) {
    playstate();

    if (state1 == 1) {
      playerA();
      Clock1();
      checkstate();
    }
    if (state1 == 0) {
      playerB();
      Clock2();
      checkstate();
    }
    if (digitalRead(button1) == HIGH && digitalRead(button2) == HIGH) {
      state1 = 2;
      delay(1500);
    }
  }
}

void settime() {
  lcd.setCursor(5, 1);
  lcd.print(Min1a);
  lcd.setCursor(6, 1);
  lcd.print(Min2a);
  lcd.setCursor(7, 1);
  lcd.print(":");
  lcd.setCursor(8, 1);
  lcd.print(sec1a);
  lcd.setCursor(9 , 1);
  lcd.print(sec2a);
}


void zeroout() {
  sec1a = 0;
  sec2a = 0;
  sec1b = 0;
  sec2b = 0;
}


void modeselect() {

  if (digitalRead(button3 == HIGH)) {
    if (digitalRead(button3) == HIGH && mode == 1) {
      mode = 0;
      lcd.begin(16, 2);
      lcd.setCursor(1, 0);
      lcd.print("Set Game Time!");
      settime();
      delay(500);
    } else if (digitalRead(button3) == HIGH && mode == 0) {
      mode = 1;
      lcd.begin(16, 2);
      lcd.setCursor(2, 0);
      lcd.print("P1");
      lcd.setCursor(13, 0);
      lcd.print("P2");
      playerA();
      playerB();
      delay(500);
    }
  }

}


//state switch
void checkstate() {
  for (int i = 0; i < 10; i ++) {
    delay (100);
    playstate();
  }
}

void playstate() {
  if (digitalRead(button1) == HIGH) {
    state1 = 0;
  } else if (digitalRead(button2) == HIGH) {
    state1 = 1;
  }
}




void Clock1() {

  sec2a--;

  //second clock logic
  if (sec1a >= 1 && sec2a == 0) {
    sec1a -= 1;
    sec2a = 9;
  }

  // minute clock logic
  if (sec1a < 1 && sec2a < 1) {
    sec1a = 5;
    sec2a = 9;
    if (Min1a == 1 && Min2a == 0) {
      Min2a = 9;
      Min1a = 0;
    } else if ( Min1a == 0 && Min2a != 0) {
      Min2a -= 1;
    } else if ( Min1a != 0 && Min2a != 0) {
      Min2a -= 1;
    }
  }
}




void Clock2() {

  sec2b--;

  //second clock logic
  if (sec1b >= 1 && sec2b == 0) {
    sec1b -= 1;
    sec2b = 9;
  }

  // minute clock logic
  if (sec1b < 1 && sec2b < 1) {
    sec1b = 5;
    sec2b = 9;
    if (Min1b == 1 && Min2b == 0) {
      Min2b = 9;
      Min1b = 0;
    } else if ( Min1b == 0 && Min2b != 0) {
      Min2b -= 1;
    } else if ( Min1b != 0 && Min2b != 0) {
      Min2b -= 1;
    }
  }
}


void playerA () {

  lcd.setCursor(0, 1);
  lcd.print( Min1a);

  lcd.setCursor(1, 1);
  lcd.print( Min2a);

  lcd.setCursor(2, 1);
  lcd.print(":");

  lcd.setCursor(3, 1);
  lcd.print( sec1a);

  lcd.setCursor(4, 1);
  lcd.print( sec2a);
}

void playerB() {
  lcd.setCursor(11, 1);
  lcd.print( Min1b);

  lcd.setCursor(12, 1);
  lcd.print( Min2b);

  lcd.setCursor(13, 1);
  lcd.print(":");

  lcd.setCursor(14, 1);
  lcd.print( sec1b);

  lcd.setCursor(15, 1);
  lcd.print( sec2b);
}
