#include "LiquidCrystal.h"
#include "IRremote.h"

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte customchar1[8] =
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

byte customchar2[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

int receiver = 10;
IRrecv irrecv(receiver);           // create instance of 'irrecv'
decode_results results;            // create instance of 'decode_results'

byte menu_input = 1;


void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  lcd.begin(16,2);    // set up the LCD's number of columns and rows:
  lcd.clear();
  lcd.createChar(1, customchar1);
  lcd.createChar(2, customchar2);
  
  lcd.setCursor(0,0);

  lcd.print("  Arduino Glass");
  for (byte i=0;i<17;i++){
    lcd.setCursor(i,1);
    lcd.write(1);
//    if (i == 3){
//      tone(8, 1480);}
//    else if (i == 9){
//      tone(8, 1661);}
//    else if (i == 15){
//      tone(8, 1864);}
    delay(50);
    
  }
  
  
  delay(150);
  //noTone(8);
  delay(2000);
  lcd.clear();
  mainmenu(1);
}




void loop() {
   
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    //Serial.println(results.value, HEX);  //UN Comment to see raw values
    translateIR(); 
    irrecv.resume(); // receive the next value
    delay(2);
  }
}








void mainmenu(byte menu){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Main menu:");
  lcd.setCursor(0,1);
  
  if (menu > 5){
    menu = 1;}
  else if (menu < 1){
    menu = 5;}
    
  menu_input = menu;
  irrecv.resume(); // receive the next value
  switch(menu){

    case 1: lcd.print("1. Play music"); break;
    case 2: lcd.print("2. Play a movie"); break;
    case 3: lcd.print("3. Play a game"); break;
    case 4: lcd.print("4. Start lasers"); break;
    case 5: lcd.print("5. Screensaver"); break;
  }
}



void translateIR() // takes action based on IR code received

// describing KEYES Remote IR codes 

{

  switch(results.value)

  {

  case 0xFF629D: Serial.println(" FORWARD"); break;
  case 0xFF22DD: Serial.println(" LEFT");    mainmenu(menu_input - 1); break;
  case 0xFF02FD: Serial.println(" -OK-");    selectmenu(menu_input); break;
  case 0xFFC23D: Serial.println(" RIGHT");   mainmenu(menu_input + 1); break;
  case 0xFFA857: Serial.println(" REVERSE"); break;
  case 0xFF6897: Serial.println(" 1");    break;
  case 0xFF9867: Serial.println(" 2");    break;
  case 0xFFB04F: Serial.println(" 3");    break;
  case 0xFF30CF: Serial.println(" 4");    break;
  case 0xFF18E7: Serial.println(" 5");    break;
  case 0xFF7A85: Serial.println(" 6");    break;
  case 0xFF10EF: Serial.println(" 7");    break;
  case 0xFF38C7: Serial.println(" 8");    break;
  case 0xFF5AA5: Serial.println(" 9");    break;
  case 0xFF42BD: Serial.println(" *");    break;
  case 0xFF4AB5: Serial.println(" 0");    break;
  case 0xFF52AD: Serial.println(" #");    break;
  case 0xFFFFFFFF: Serial.println(" REPEAT");break;  

  default: 
    Serial.println(" other button   ");

  }// End Case

  delay(2); // Do not get immediate repeat


}


void selectmenu(byte option){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Loading...");
  lcd.setCursor(0,1);
  
  for (byte i=0;i<17;i++){
    lcd.setCursor(i,1);
    lcd.write(1);
    lcd.setCursor(i-1,1);
    lcd.write(2);
    
    delay(150);}
    
  lcd.clear();
  lcd.setCursor(0,0);  
  switch(option){

    case 1: musicmenu(); break;
    case 2: break;
    case 3: break;
    case 4: break;
    case 5: break;
  }
}

void musicmenu(){
  boolean ir_value = ir_receiver();
  
  if (ir_value == true){
    ir_value = music_choice();}
    
  delay(2);
  byte scrollCursor = 16;
  byte stringStart, stringStop = 0;
  String str = "(1) Fur Elise (2) Star-spangled banner (3) Mario (4) EXIT";
  
  while (!ir_value){
    lcd.setCursor(0,0);
    lcd.print("Playlist:");
    lcd.setCursor(scrollCursor, 1);
    lcd.print(str.substring(stringStart,stringStop));
    boolean ir_value = ir_receiver();
    Serial.println(results.value);
    if (ir_value == true){
      ir_value = music_choice();}
      
    irrecv.resume(); // receive the next value  
    delay(300);
    lcd.clear();
    
    if(stringStart == 0 && scrollCursor > 0){
      scrollCursor--;
      stringStop++;
    }
    else if (stringStart == stringStop){
      stringStart = stringStop = 0;
      scrollCursor = 16;
    }
    else if (stringStop == str.length() && scrollCursor == 0){
      stringStart++;
    }
    else {
      stringStart++;
      stringStop++;
    }
  }
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Now playing:");
  lcd.setCursor(0,1);
  
  switch(results.value){
      case 0xFF6897: Serial.println(" 1");
        lcd.print("Fur Elise"); delay(1000);
        break;
      case 0xFF9867: Serial.println(" 2");
        lcd.print("Star-spangled banner"); delay(1000);
        break;
      case 0xFFB04F: Serial.println(" 3");
        lcd.print("Mario"); delay(1000);
        break;
      case 0xFF30CF: Serial.println(" 4");
            break;
  }
  mainmenu(1);
}



boolean ir_receiver(){
  irrecv.resume(); // receive the next value
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    return true;
  }
  else {
    return false;
  }
}

boolean music_choice(){
  switch(results.value){
      case 0xFF6897: Serial.println(" 1");
        return true;
        break;
      case 0xFF9867: Serial.println(" 2");
        return true;
        break;
      case 0xFFB04F: Serial.println(" 3");
        return true;
        break;
      case 0xFF30CF: Serial.println(" 4");
        return true;
        break;
      default: return false;
    }
}
