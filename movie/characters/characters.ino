#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte man[8] = {B01110,B01110,B01110,B00100,B11111,B00100,B01010,B01010};
//byte talkingMan[8] = {B01110,B01100,B01110,B00100,B11111,B00100,B01010,B01010};
byte woman[8] = {B01110, B01110, B11111,B00100, B11111,B01110,B01110,B01010};
//byte talkingWoman[8] = {B01110, B00110, B11111,B00100, B11111,B01110,B01110,B01010};
byte skull[8] = { B01110, B11111, B10101, B11111, B01110, B01010, B00000, B00000 };
byte heart[8] = { B00000, B01010, B11111, B11111, B01110, B00100, B00000, B00000 };
byte dagger[8] = { B00000, B10000, B01100, B01100, B00010, B00001, B00000, B00000 };
byte poison[8] = { B00000, B00000, B11111, B01110, B11111, B11111, B11111, B01110 };
//byte music_note[8] = { B00001, B00011, B00101, B01001, B01001, B01011, B11011, B11000 };
byte sadface[8] = { B00000, B01010, B01010, B00000, B00000, B01110, B10001, B00000 };
byte happyface[8] = { B00000, B01010, B01010, B00000, B00000, B10001, B01110, B00000 };
//byte flower[8] = {B11011, B10101, B01110, B10101, B11111, B00100, B01110, B00100 };
byte sleepingPerson[8] = {B00000,B00000,B00000,B00011,B00011,B00001,B00111,B11111};

void setup() {
    lcd.createChar(1, man); //
    lcd.createChar(2, woman);//
    
    lcd.createChar(3, skull);//
    lcd.createChar(4, heart);//
    lcd.createChar(5, dagger);//
    lcd.createChar(6, poison);//
    
    //lcd.createChar(7, music_note);//
    lcd.createChar(8, sadface);//
    //lcd.createChar(9, happyface);//
    //lcd.createChar(10, flower);//
    //lcd.createChar(11, talkingMan);//
    //lcd.createChar(12, talkingWoman);//
    lcd.createChar(7, sleepingPerson);//
    
    
    //intro
    lcd.begin(16, 2);
    lcd.print("Romeo");
    lcd.write(1);
    lcd.setCursor(0,1);
    lcd.print("Juliet");
    lcd.write(2);
    delay(3000);
    
    lcd.clear();
    
    //man & woman enterance
    for (byte i = 0; i <= 7; i++){
      lcd.clear();
      lcd.setCursor(i,1);
      lcd.write(1);
      lcd.setCursor(15 - i, 1);
      lcd.write(2);
      delay(400);
      
    }
    
    delay(750);
    
    //smiles
//    lcd.setCursor(7,0);
//    lcd.write(9);
//    lcd.setCursor(8,0);
//    lcd.write(9);
    
    //Introductions
    lcd.setCursor(7,1);
    lcd.write(1);
    lcd.setCursor(0,0);
    lcd.print("Hi. I'm Romeo.");
    delay(2000);
    lcd.clear();
    lcd.setCursor(7,1);
    lcd.write(1);
    lcd.setCursor(8,1);
    lcd.write(2);
    delay(10);
    
    lcd.setCursor(8,1);
    lcd.write(2);
    lcd.setCursor(2, 0);
    lcd.print("Hi. I'm Juliet");
    delay(2000);
    lcd.clear();
    lcd.setCursor(7,1);
    lcd.write(1);
    lcd.setCursor(8,1);
    lcd.write(2);
    delay(10);
    
    //music notes (now hearts)
    for (byte i=0; i<8; i++){
      if (i % 2 == 0){
        lcd.setCursor(7,0);
        lcd.write(4);
      }
      else{
        lcd.setCursor(8,0);
        lcd.write(4);
      }
      delay(400);
      lcd.clear();
      lcd.setCursor(7,1);
      lcd.write(1);
      lcd.setCursor(8,1);
      lcd.write(2);
    }
    
    //hearts
    lcd.setCursor(7,0);
    lcd.write(4);
    lcd.setCursor(8,0);
    lcd.write(4);
    delay(500);
    
    lcd.setCursor(6,0);
    lcd.write(4);
    lcd.setCursor(9,0);
    lcd.write(4);
    delay(500);
    
    lcd.setCursor(6,1);
    lcd.write(4);
    lcd.setCursor(9,1);
    lcd.write(4);
    delay(500);
    
    //flowers (hearts)
    for (byte i= 0; i<6; i++){
      lcd.setCursor(5 - i,1);
      lcd.write(4);
      lcd.setCursor(10 + i,1);
      lcd.write(4);
      delay(450);
    }
    
    lcd.clear();
    
    delay(1000);
    
    //woman on scene
    for (byte i = 0; i <= 7; i++){
      lcd.clear();
      lcd.setCursor(15 - i, 1);
      lcd.write(2);
      delay(400);
    }
    delay(10);
    lcd.setCursor(9,0);
    delay(10);
    lcd.write(6); //potion
    delay(10);
    lcd.setCursor(10,0);
    delay(10);
    lcd.print("=Zzz");
    delay(2000);
    lcd.setCursor(8,1);
    lcd.clear();
    lcd.write(7); //Juliet asleep
    
    for (byte i = 0; i <= 7; i++){
      lcd.clear();
      lcd.setCursor(8,1);
      lcd.write(7); //Juliet asleep
      lcd.setCursor(i, 1);
      lcd.write(1);
      delay(400);
    }
    
    lcd.setCursor(7,0);
    lcd.write(8);
    delay(1000);
    
    lcd.setCursor(5,0);
    lcd.write(6); ///poison
    lcd.setCursor(6,0);
    lcd.print("=");
    lcd.setCursor(7,0);
    lcd.write(3);
    
    delay(2000);
    lcd.clear();
    
    lcd.setCursor(8,1);
    lcd.write(7); //Juliet asleep
    lcd.setCursor(7,1);
    lcd.write(3);
    delay(500);
    lcd.setCursor(7,1);
    lcd.print("_");
    
    delay(1000);
    
    lcd.setCursor(8,1);
    lcd.write(2);
    delay(500);
    lcd.setCursor(8,0);
    lcd.print("!");
    lcd.setCursor(9,0);
    lcd.write(8);
    delay(1500);
    
    lcd.clear();
    
    lcd.setCursor(7,1);
    lcd.print("_");
    lcd.setCursor(8,1);
    lcd.write(2);
    delay(500);
    
    lcd.setCursor(8,0);
    lcd.write(5);
    lcd.setCursor(9,0);
    lcd.print("=");
    lcd.setCursor(10,0);
    lcd.write(3);//death
    delay(2000);
    
    lcd.clear();
    
    lcd.setCursor(7,1);
    lcd.print("_");
    lcd.setCursor(8,1);
    lcd.write(3);
    delay(500);
    lcd.setCursor(8,1);
    lcd.print("_");
    
    lcd.setCursor(0,0);
    lcd.print("Thus with a kiss,");
    lcd.setCursor(0,1);
    lcd.print("I die.");
    delay(4000);
}

void loop() {


}
