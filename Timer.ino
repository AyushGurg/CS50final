#include <LiquidCrystal.h>

// For LCD display
const int rs = 2, enable = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7; 
LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);

//Buttons
const int button50min = 8, button30min = 9, buttonBreak = 10, buttonReset = 11; 


void setup() {
  //LCD Initilized
  LCDInitial();   
  //Button initialized
  buttonHigh();
}

void loop() {
  if(digitalRead(button50min) == LOW)
  {
    Session(5);
  }
  if(digitalRead(button30min) == LOW)
  {
    Session(3);
  }
  if(digitalRead(buttonBreak) == LOW)
  {
    SessionBreak();
  }
  if(digitalRead(buttonReset) == LOW)
  {
    lcd.setCursor(0, 1);
    lcd.print("Reset");
  }
} 

void Session(int limit)
{
  int sec1 = 0, sec2 = 0, min1 = 0, min2 = 0;
  const int sec1Pos = 9, sec2Pos = 8, min1Pos =6, min2Pos = 5;

  lcd.setCursor(0, 0);
  lcd.print("--Study---Time--");

  lcd.setCursor(6,1);
  lcd.print("00:00");

  while (min2 < limit)
  {
    while(sec1 <= 9)
    {
      lcd.setCursor(sec1Pos,1);
      lcd.print(sec1);
      sec1++;
      delay(1000);
    }
    sec1 = 0;
    lcd.setCursor(sec1Pos,1);
    lcd.print(sec1);
    
    sec2++;
    if (sec2 == 6) {
      sec2 = 0;
      lcd.setCursor(sec2Pos,1);
      lcd.print(sec2);
      if (min1 == 9) {
        min1 = 0;
        lcd.setCursor(min1Pos,1);
        lcd.print(min1);
        min2++;
        lcd.setCursor(min2Pos,1);
        lcd.print(min2);
      }
      else {
        min1++;
        lcd.setCursor(min1Pos,1);
        lcd.print(min1);
      }
    }
    else {
      lcd.setCursor(sec2Pos,1);
      lcd.print(sec2);
    }
  }

}
void LCDInitial() {
  lcd.begin(16,2);
  lcd.setCursor(0, 0);
  lcd.print("-Pomodoro-Timer-");
  lcd.setCursor(0, 1);
  lcd.print("----------------");
}
void buttonHigh() {
  pinMode(button50min, INPUT_PULLUP);  
  pinMode(button30min, INPUT_PULLUP);  
  pinMode(buttonBreak, INPUT_PULLUP);  
  pinMode(buttonReset, INPUT_PULLUP);  
}

bool SessionBreak() {
  
  int sec1 = 0, sec2 = 0, min1 = 0, min2 = 0;
  const int sec1Pos = 9, sec2Pos = 8, min1Pos =6, min2Pos = 5;

  lcd.setCursor(0, 0);
  lcd.print("--Break---Time--");

  lcd.setCursor(6,1);
  lcd.print("00:00");

  while (min2 < 1)
  {
    while(sec1 <= 9)
    {
      lcd.setCursor(sec1Pos,1);
      lcd.print(sec1);
      sec1++;
      delay(1000);
    }
    sec1 = 0;
    lcd.setCursor(sec1Pos,1);
    lcd.print(sec1);
    
    sec2++;
    if (sec2 == 6) {
      sec2 = 0;
      lcd.setCursor(sec2Pos,1);
      lcd.print(sec2);
      if (min1 == 9) {
        min1 = 0;
        lcd.setCursor(min1Pos,1);
        lcd.print(min1);
        min2++;
        lcd.setCursor(min2Pos,1);
        lcd.print(min2);
      }
      else {
        min1++;
        lcd.setCursor(min1Pos,1);
        lcd.print(min1);
      }
    }
    else {
      lcd.setCursor(sec2Pos,1);
      lcd.print(sec2);
    }
  }
}
