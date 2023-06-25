#include <LiquidCrystal.h>

// For LCD display
const int rs = 2, enable = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7; 
LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);

//Buttons
const int button50min = 8, buttonBreak = 9, buttonReset = 10; 

unsigned long currentMillis = 0;
unsigned long startMillis;
const unsigned long period = 1000;

int sec1 = 0, sec2 = 0, min1 = 0, min2 = 0;
const int sec1Pos = 9, sec2Pos = 8, min1Pos =6, min2Pos = 5;
int limit;
bool session = false, breakallow = false,studyallow = true;


void setup() {
  //LCD Initilized
  LCDInitial();   
  //Button initialized
  buttonHigh();
  //
  startMillis = millis();
}

void loop() {
    currentMillis = millis();
    
    if (digitalRead(button50min) == LOW && studyallow)
    {
      session50Initial();
    }

    if (digitalRead(buttonBreak) == LOW && breakallow)
    {
      breakInitial();
    }
    if(session) //Starts the study session
    {
      pomoSession();
    }
}

void session50Initial(){
  limit = 5;
  session = true;
  breakallow = false;
  lcd.setCursor(0, 0);
  lcd.print("-50-min-Session-");
  lcd.setCursor(0, 1);
  lcd.print("-------:--------");
  lcd.setCursor(sec1Pos, 1);
  lcd.print(sec1);
  lcd.setCursor(sec2Pos, 1);
  lcd.print(sec2);
  lcd.setCursor(min1Pos, 1);
  lcd.print(min1);
  lcd.setCursor(min2Pos, 1);
  lcd.print(min2);
}
void breakInitial(){
  limit = 1;
  session = true;
  lcd.setCursor(0, 0);
  lcd.print("--10-in-Break--");
  lcd.setCursor(0, 1);
  lcd.print("-------:--------");
  lcd.setCursor(sec1Pos, 1);
  lcd.print(sec1);
  lcd.setCursor(sec2Pos, 1);
  lcd.print(sec2);
  lcd.setCursor(min1Pos, 1);
  lcd.print(min1);
  lcd.setCursor(min2Pos, 1);
  lcd.print(min2);
}
void pomoSession() {
  if(currentMillis - startMillis >= period) //Every second
      {
        startMillis  = currentMillis;
        sec1++;
        if (sec1 > 9) {                         // Handles the First digit of second
          sec1 = 0;
          lcd.setCursor(sec1Pos, 1);
          lcd.print(sec1);
          sec2++;
          if (sec2 > 6) {                       // Handles the second digit of second
            sec2 = 0;
            lcd.setCursor(sec2Pos, 1);
            lcd.print(sec2);
            min1++;
            if(min1 > 9) {
              min1 = 0;
              lcd.setCursor(min1Pos, 1);        // Handles the first digit of minute
              lcd.print(min1);
              min2++;
              if (min2 > limit) {
                session = false;                //session ended

                studyallow = !studyallow;       //I cant start a study session during break
                breakallow = !breakallow ;      // if I just finish study break is allowed
                                                // if break just finished break is not allowed
                sec1 = 0;
                sec2 = 0;
                min1 = 0;
                min2 = 0;
                LCDInitial();
              }
              else {
                lcd.setCursor(min2Pos, 1);        // Handles the first digit of minute
                lcd.print(min2);
              }
            }
            else {
              lcd.setCursor(min1Pos, 1);        // Handles the first digit of minute
              lcd.print(min1);
            }
          }
          else {
          lcd.setCursor(sec2Pos, 1);
          lcd.print(sec2);
        }
        }
        else {
          lcd.setCursor(sec1Pos, 1);
          lcd.print(sec1);
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
  pinMode(buttonBreak, INPUT_PULLUP);  
  pinMode(buttonReset, INPUT_PULLUP);  
}


