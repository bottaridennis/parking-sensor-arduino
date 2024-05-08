#include <LiquidCrystal_I2C.h>

int trigPin = 10;
int echoPin = 9;          
int buzzerPin = 8;        
int thresholdDistance1 = 20;  
int thresholdDistance2 = 10;  

LiquidCrystal_I2C lcd(0x27, 16, 2);  

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  Serial.begin(9600);
  lcd.init();					
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Parcheggio");
}

void loop() {
  long duration, distance;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration * 0.034 / 2;
  
  lcd.setCursor(0, 1);
  lcd.print("Distanza:");
  lcd.print(distance);
  lcd.print(" cm ");
  Serial.println(distance);
  

  if (distance <= 50 && distance > thresholdDistance1) {
    tone(buzzerPin, 800); 
    delay(100); 
    noTone(buzzerPin); 
  } else if (distance <= 20 && distance > thresholdDistance2) {
    tone(buzzerPin, 800); 
    delay(50); 
    noTone(buzzerPin); 
  } else if (distance <= thresholdDistance2) {
    tone(buzzerPin, 800);
  } else {
    noTone(buzzerPin);
  }
  
  delay(500); 
}