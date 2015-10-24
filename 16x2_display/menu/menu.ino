#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16,2);
  lcd.clear();
}

void loop() {
  // set the cursor to (0,0):
  lcd.setCursor(0,0);
  
  lcd.print("    Welcome");
  lcd.setCursor(0,1);
  lcd.print("    to Glass");
  
  // clear screen for the next loop:
  lcd.clear();
}
