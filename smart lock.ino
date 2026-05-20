#include <Servo.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
Servo myservo;

char password[] = {'1', '2', '3', '4'}; //كلمة المرور
int buzz = 12;
int RedpinLock = 10;  
int GreenpinUnlock = 11;

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 13};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  pinMode(RedpinLock, OUTPUT);
  pinMode(GreenpinUnlock, OUTPUT);
  pinMode(buzz, OUTPUT);
  myservo.attach(9);
  
  // تأمين القفل 
  myservo.write(0);
  digitalWrite(RedpinLock, HIGH);
  digitalWrite(GreenpinUnlock, LOW);

  lcd.begin(16, 2);
  lcd.print("Hello");
  delay(2000);
  lcd.clear();
}

bool Flag = false;

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("enter password");

  for (int i = 0; i < 4; i++) {
    char key = keypad.waitForKey();
    lcd.setCursor(i, 1);
    lcd.print(key);
    if (key != password[i])
      Flag = true;
  }

  if (Flag) {
    lcd.clear();
    lcd.print("Wrong password");
    digitalWrite(GreenpinUnlock, HIGH);
    tone(buzz, 3000);
    delay(1000);
    noTone(buzz);
    digitalWrite(GreenpinUnlock, LOW);
    delay(1000);
    Flag = false;
  } 
  else {
    lcd.clear();
    lcd.print("Welcome");
    digitalWrite(RedpinLock, LOW);
    digitalWrite(GreenpinUnlock, HIGH);
    
    // فتح القفل
    for (int pos = 0; pos <= 90; pos++) {
      myservo.write(pos);
      delay(15);
    }
    delay(2000);
    
    // إغلاق القفل
    for (int pos = 90; pos >= 0; pos--) {
      myservo.write(pos);
      delay(15);
    }
    
    digitalWrite(RedpinLock, HIGH);
    digitalWrite(GreenpinUnlock, LOW);
  }
  
  delay(500);
  lcd.clear();
}