#include "LiquidCrystal.h"
#include "IRremote.h"
# include "pitches.h"

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//star-spangled banner
int melody1[] = {
NOTE_F5,NOTE_D5,NOTE_AS4,NOTE_D5,NOTE_F5,NOTE_AS5,NOTE_D6,NOTE_C6,NOTE_AS5,NOTE_D5,NOTE_E5,NOTE_F5,
NOTE_F5,NOTE_F5,NOTE_D6,NOTE_C6,NOTE_AS5,NOTE_A5,NOTE_G5,NOTE_A5,NOTE_AS5,NOTE_AS5,NOTE_F5,NOTE_D5,NOTE_AS4,
NOTE_D6,NOTE_D6,NOTE_D6,NOTE_DS6,NOTE_F6,NOTE_F6,NOTE_DS6,NOTE_D6,NOTE_C6,NOTE_D6,NOTE_DS6,NOTE_DS6,
0,NOTE_DS6,NOTE_D6,NOTE_C6,NOTE_AS5,NOTE_A5,NOTE_G5,NOTE_A5,NOTE_AS5,NOTE_D5,NOTE_E5,NOTE_F5,
NOTE_F5,NOTE_AS5,NOTE_AS5,NOTE_AS5,NOTE_A5,NOTE_G5,NOTE_G5,NOTE_G5,NOTE_C6,NOTE_DS6,NOTE_D6,NOTE_C6,NOTE_AS5,NOTE_AS5,NOTE_A5,
NOTE_F5,NOTE_F5,NOTE_AS5,NOTE_C6,NOTE_D6,NOTE_DS6,NOTE_F6,NOTE_AS5,NOTE_C6,NOTE_D6,NOTE_DS6,NOTE_C6,NOTE_AS5
};
float noteDurations[] = {
6,12,4,4,4,2,6,12,4,4,4,2,
8,8,8/2.9,8,4,2,8,8,4,4,4,4,4,
6,12,4,4,4,2,8,8,4,4,4,2,
8,8,8/2.9,8,4,2,8,8,4,4,4,2,
4,4,4,8,8,4,4,4,4,8,8,8,8,4,4,
8,8,8/2.9,8,8,8,2,8,8,4,4,4,2
};
int musicLength=sizeof(melody1)/sizeof('NOTE_F5');

//Mario
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7, 
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0, 

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main theme tempo
int tempo[] = {
  12, 12, 12, 12, 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12, 

  12, 12, 12, 12,
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 12, 

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};

byte customchar1[8] ={  B11111,  B11111,  B11111,  B11111,  B11111,  B11111,  B11111,  B11111};
byte customchar2[8] = {B00000,B00000,B00000,B00000,B00000,B00000, B00000, B00000};
byte man[8] = {B01110,B01110,B01110,B00100,B11111,B00100,B01010,B01010};
byte woman[8] = {B01110, B01110, B11111,B00100, B11111,B01110,B01110,B01010};
byte skull[8] = { B01110, B11111, B10101, B11111, B01110, B01010, B00000, B00000 };
byte heart[8] = { B00000, B01010, B11111, B11111, B01110, B00100, B00000, B00000 };
byte dagger[8] = { B00000, B10000, B01100, B01100, B00010, B00001, B00000, B00000 };
byte poison[8] = { B00000, B00000, B11111, B01110, B11111, B11111, B11111, B01110 };
byte sadface[8] = { B00000, B01010, B01010, B00000, B00000, B01110, B10001, B00000 };
byte happyface[8] = { B00000, B01010, B01010, B00000, B00000, B10001, B01110, B00000 };
byte sleepingPerson[8] = {B00000,B00000,B00000,B00011,B00011,B00001,B00111,B11111};

//laser
byte lasers = 0;

//screensaver
byte screensaver = 0;
byte screen_num = 0;

//ir code setup
int receiver = 10;
IRrecv irrecv(receiver);           // create instance of 'irrecv'
decode_results results;            // create instance of 'decode_results'

byte menu_input = 1;
unsigned long x = 0;

//music menu variables
byte scrollCursor = 16;
byte stringStart, stringStop = 0;
String music_str = "(1) Pachelbel's Canon in D (2) Star-spangled Banner (3) Mario (4) EXIT";

//menu flags
byte main_menu = 1;
byte music_menu = 0;

void setup() {
  pinMode(37, OUTPUT);
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
    if (i == 3){
      tone(8, 1480);}
    else if (i == 9){
      tone(8, 1661);}
    else if (i == 15){
      tone(8, 1864);}
    delay(50);
    
  }
  
  
  delay(150);
  noTone(8);
  delay(2000);
  lcd.clear();
  mainmenu(1);
}




void loop() {
   
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    //Serial.println(results.value, HEX);  //UN Comment to see raw values
    switch(results.value)

      {
      case 0xFF22DD: Serial.println(" LEFT");  x = results.value; break;
      case 0xFF02FD: Serial.println(" -OK-");  x = results.value; break;
      case 0xFFC23D: Serial.println(" RIGHT"); x = results.value; break;
      case 0xFFA857: Serial.println(" REVERSE"); x = results.value; break;
      case 0xFF6897: Serial.println(" 1");   x = results.value; break;
      case 0xFF9867: Serial.println(" 2");   x = results.value; break;
      case 0xFFB04F: Serial.println(" 3");   x = results.value; break;
      case 0xFF30CF: Serial.println(" 4");   x = results.value; break;
      case 0xFF18E7: Serial.println(" 5");   x = results.value; break;
      case 0xFF7A85: Serial.println(" 6");   x = results.value; break;
      case 0xFF10EF: Serial.println(" 7");   x = results.value; break;
      case 0xFF38C7: Serial.println(" 8");   x = results.value; break;
      case 0xFF5AA5: Serial.println(" 9");   x = results.value; break;
      case 0xFF42BD: Serial.println(" *");   x = results.value; break;
      case 0xFF4AB5: Serial.println(" 0");   x = results.value; break;
      case 0xFF52AD: Serial.println(" #");   x = results.value; break;
      default: 
        Serial.println(" other button   ");
    
      } 
    irrecv.resume(); // receive the next value
    delay(2);
  }
  
  if (main_menu == 1){
    switch(x){
      case 0xFF22DD: Serial.println(" LEFT");  mainmenu(menu_input - 1); break;
      case 0xFF02FD: Serial.println(" -OK-");  main_menu = 0; selectmenu(menu_input);   break;  
        
      case 0xFFC23D: Serial.println(" RIGHT"); mainmenu(menu_input + 1); break;
      
      default: 
        Serial.println(" other button   ");
    }
  }
  else if (music_menu == 1){
    delay(2);
    lcd.setCursor(0,0);
    lcd.print("Playlist:");
    lcd.setCursor(scrollCursor, 1);
    lcd.print(music_str.substring(stringStart,stringStop));
    
    
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
    else if (stringStop == music_str.length() && scrollCursor == 0){
      stringStart++;
    }
    else {
      stringStart++;
      stringStop++;
    }
    
    if (music_choice()){
      musicmenu();
    }
  }
  
  //LASERS
  else if (lasers == 1){
    digitalWrite(37, HIGH);
    for (byte i=1; i<16; i++){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Laser cooldown");
      lcd.setCursor(0,1);
      lcd.print("in ");
      lcd.print(16 - i);
      lcd.print(" seconds.");
      delay(1000);
    }
    digitalWrite(37, LOW);
    lasers = 0;
    main_menu = 1;
    mainmenu(3);
  }
  
  //SCREENSAVER
  else if (screensaver == 1){
    if (x == 0){
      screen_num += 1;
      lcd.print(screen_num);
      lcd.print(" ");
      delay(500);
    }
    else {
      screensaver = 0;
      main_menu = 1;
      mainmenu(4);
    }
    
  }
  x = 0;
  Serial.println(lasers);
}


void mainmenu(byte menu){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Main menu:");
  lcd.setCursor(0,1);
  
  if (menu > 4){
    menu = 1;}
  else if (menu < 1){
    menu = 4;}
    
  menu_input = menu;
  Serial.println(results.value,HEX);
  switch(menu){

    case 1: lcd.print("<  Play music  >"); break;
    case 2: lcd.print("<  Play a movie>"); break;
    case 3: lcd.print("<  Start lasers>"); break;
    case 4: lcd.print("<  Screensaver >"); break;
  }
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

    case 1: music_menu = 1; break;
    case 2: movie(); break;
    case 3: lcd.clear(); lasers = true; break;
    case 4: lcd.clear(); lcd.setCursor(0,0); screensaver = 1; break;
  }
}

void musicmenu(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Now playing:");
  lcd.setCursor(0,1);
  
  switch(x){
      case 0xFF6897: Serial.println(" 1");
        lcd.print("Pachelbel's Canon in D"); fur_elise(); noTone(8); delay(1000);
        break;
      case 0xFF9867: Serial.println(" 2");
        lcd.print("Star-spangled Banner");  star(); noTone(8); delay(1000);
        break;
      case 0xFFB04F: Serial.println(" 3");
        lcd.print("Mario"); noTone(8); sing(); delay(1000);
        break;
      case 0xFF30CF: Serial.println(" 4");
        main_menu = 1;
        music_menu = 0;
        mainmenu(1);
            break;
  }
}


boolean music_choice(){
  switch(x){
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

void fur_elise(){
  tone(8, 880);
  delay(375);
  tone(8, 740);
  delay(187.5);
  tone(8, 784);
  delay(187.5);
  tone(8, 880);
  delay(375);
  tone(8, 740);
  delay(187.5);
  tone(8, 784);
  delay(187.5);
  tone(8, 880);
  delay(187.5);
  tone(8, 440);
  delay(187.5);
  tone(8, 494);
  delay(187.5);
  tone(8, 554);
  delay(187.5);
  tone(8, 587);
  delay(187.5);
  tone(8, 659);
  delay(187.5);
  tone(8, 740);
  delay(187.5);
  tone(8, 784);
  delay(187.5);
  tone(8, 740);
  delay(375);
  tone(8, 587);
  delay(187.5);
  tone(8, 659);
  delay(187.5);
  tone(8, 740);
  delay(375);
  tone(8, 587);
  delay(187.5);
  tone(8, 659);
  delay(187.5);
  tone(8, 740);
  delay(187.5);
  tone(8, 370);
  delay(187.5);
  tone(8, 392);
  delay(187.5);
  tone(8, 440);
  delay(187.5);
  tone(8, 494);
  delay(187.5);
  tone(8, 440);
  delay(187.5);
  tone(8, 392);
  delay(187.5);
  tone(8, 440);
  delay(187.5);
  tone(8, 587);
  delay(187.5);
  tone(8, 554);
  delay(187.5);
  tone(8, 587);
  delay(187.5);
  tone(8, 392);
  delay(375);
  tone(8, 494);
  delay(187.5);
  tone(8, 440);
  delay(187.5);
  tone(8, 392);
  delay(375);
  tone(8, 370);
  delay(187.5);
  tone(8, 330);
  delay(187.5);
  tone(8, 370);
  delay(187.5);
  tone(8, 330);
  delay(187.5);
  tone(8, 294);
  delay(187.5);
  tone(8, 330);
  delay(187.5);
  tone(8, 370);
  delay(187.5);
  tone(8, 392);
  delay(187.5);
  tone(8, 494);
  delay(187.5);
  tone(8, 440);
  delay(187.5);
  tone(8, 494);
  delay(375);
  tone(8, 554);
  delay(187.5);
  tone(8, 587);
  delay(187.5);
  tone(8, 440);
  delay(187.5);
  tone(8, 494);
  delay(187.5);
  tone(8, 554);
  delay(187.5);
  tone(8, 587);
  delay(187.5);
  tone(8, 659);
  delay(187.5);
  tone(8, 740);
  delay(187.5);
  tone(8, 784);
  delay(187.5);
  tone(8, 880);
  delay(187.5);
  tone(8, 740);
  delay(375);
  tone(8, 587);
  delay(187.5);
  tone(8, 659);
  delay(187.5);
  tone(8, 740);
  delay(375);
  tone(8, 587);
  delay(187.5);
  tone(8, 659);
  delay(187.5);
  tone(8, 554);
  delay(187.5);
  tone(8, 587);
  delay(187.5);
  tone(8, 659);
  delay(187.5);
  tone(8, 659);
  delay(187.5);
  tone(8, 698);
  delay(375);
  tone(8, 587);
  delay(187.5);
  tone(8, 554);
  delay(187.5);
  tone(8, 587);
  delay(375);
  tone(8, 494);
  delay(187.5);
  tone(8, 554);
  delay(187.5);
  tone(8, 587);
  delay(375);
}
//star-spangled banner
void star(){
  for (int thisNote = 0; thisNote < musicLength; thisNote++) {
      // calculate the note duration. change tempo by changing 2000 to other values
      int noteDuration = 2000/noteDurations[thisNote];
      tone(8, melody1[thisNote],noteDuration);
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well
      float pauseBetweenNotes = noteDuration * 1.30;
      //split the delay into two parts and check to see
      //whether the pushbutton is pressed to turn off
      //the sound and light
      delay(pauseBetweenNotes/2);
      delay(pauseBetweenNotes/2);
  }
}

//Mario
void sing(){      
   // iterate over the notes of the melody:
   Serial.println(" 'Mario Theme'");
     int size = sizeof(melody) / sizeof(int);
     for (int thisNote = 0; thisNote < size; thisNote++) {

       // to calculate the note duration, take one second
       // divided by the note type.
       //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
       int noteDuration = 1000/tempo[thisNote];

       buzz(8, melody[thisNote],noteDuration);

       // to distinguish the notes, set a minimum time between them.
       // the note's duration + 30% seems to work well:
       int pauseBetweenNotes = noteDuration * 1.30;
       delay(pauseBetweenNotes);

       // stop the tone playing:
       buzz(8, 0,noteDuration);

    }
  }
void buzz(int targetPin, long frequency, long length) {
  digitalWrite(13,HIGH);
  long delayValue = 1000000/frequency/2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length/ 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to 
  //// get the total number of cycles to produce
  for (long i=0; i < numCycles; i++){ // for the calculated length of time...
    digitalWrite(targetPin,HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin,LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
}

//Romeo and Juliet movie
void movie(){
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
    delay(400);
    
    lcd.setCursor(6,0);
    lcd.write(4);
    lcd.setCursor(9,0);
    lcd.write(4);
    delay(400);
    
    lcd.setCursor(6,1);
    lcd.write(4);
    lcd.setCursor(9,1);
    lcd.write(4);
    delay(400);
    
    //flowers (hearts)
    for (byte i= 0; i<6; i++){
      lcd.setCursor(5 - i,1);
      lcd.write(4);
      lcd.setCursor(10 + i,1);
      lcd.write(4);
      delay(350);
    }
    
    lcd.clear();
    
    delay(900);
    
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
    
    lcd.createChar(1, customchar1);
    lcd.createChar(2, customchar2);
    
    main_menu = 1;
    mainmenu(1);
}

