#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

const int temppin = A0;  // LM35
int fan = 11;
int buzz = 12;
float temp = 0;

#define ldr A1
#define led 10

int threshold = 500;      
int level;
int tempmin = 30;          
int tempmax = 50;          
int fanSpeed;
int fanlcd;

void setup() {
  pinMode(fan, OUTPUT);
  pinMode(buzz, OUTPUT);
  pinMode(led, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("welcome");
  delay(2000);
  lcd.clear();
  Serial.begin(9600);
}

void loop() {
  
  int raw = analogRead(temppin);        // 0-1023
  temp = (raw / 1023.0) * 500.0;        // تحويل إلى درجة مئوية
  
  Serial.print("Temperature: ");
  Serial.println(temp);
  
  lcd.setCursor(0, 0);
  lcd.print("Temp= ");
  lcd.print(temp);
  lcd.print(" C");
  
  // التحكم في المروحة والجرس حسب درجة الحرارة
  if (temp > tempmax) {
    digitalWrite(fan, HIGH);   
    digitalWrite(buzz, HIGH);  
    lcd.setCursor(0, 1);
    lcd.print("Fan: MAX  ALARM!");
  }
  else if (temp >= tempmin) {
    // التحكم في سرعة المروحة 
    fanSpeed = map(temp, tempmin, tempmax, 80, 255);
    fanlcd = map(temp, tempmin, tempmax, 0, 100);
    analogWrite(fan, fanSpeed);
    digitalWrite(buzz, LOW);
    
    lcd.setCursor(0, 1);
    lcd.print("Fan: ");
    lcd.print(fanlcd);
    lcd.print("%  ");
  }
  else {
    digitalWrite(fan, LOW);
    digitalWrite(buzz, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Fan: OFF     ");
  }
  
  // التحكم في الليد حسب شدة الضوء
  level = analogRead(ldr);
  if (level < threshold) {
    digitalWrite(led, HIGH);   
  } else {
    digitalWrite(led, LOW);    
  }
  
  delay(500);
}