#include <Thermistor.h>
Thermistor temperatura(0);
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int temp,lumi;
void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Temperatura:");
  lcd.setCursor(0, 1);
  lcd.print("Luminosidade:");
  lcd.setCursor(15, 0);
  lcd.print("C");
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(7, OUTPUT);


}

void loop()
{
  temp = temperatura.getTemp();
  lumi = analogRead(2);
  Serial.println(temp);
  Serial.println(lumi);
  delay(300);

  lcd.setCursor(12, 0); 
  lcd.print(temp);
  delay(200);
  lcd.setCursor(13, 1); 
  lcd.print(lumi); 
  delay(200);

  if (temp < 20)
    digitalWrite(10, HIGH);
  else
    digitalWrite(10, LOW);
  if (temp >= 20 && temp <= 24)
    digitalWrite(6, HIGH);
  else
    digitalWrite(6, LOW);

  if (temp > 24)
  {
    digitalWrite(9, HIGH);
    tone(7, 1900);
    delay(500);
    noTone(7);
    delay(100);
  }
  else
  {
    digitalWrite(9, LOW);
    noTone(7);
  }

  if (lumi < 150)
  {
    digitalWrite(8, HIGH);
  }
  else
  {
    digitalWrite(8, LOW);
  }

}

