#include <Thermistor.h>
Thermistor temperatura(0);
#include <LiquidCrystal.h> //Inclui a biblioteca do LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //Configura os pinos do Arduino para se comunicar com o LCD
 void setup()
{
Serial.begin(9600);
lcd.begin(16, 2); //Inicia o LCD com dimensões 16x2(Colunas x Linhas)
lcd.setCursor(0, 0); //Posiciona o cursor na primeira coluna(0) e na primeira linha(0) do LCD
lcd.print("Temperatura:"); //Escreve no LCD "Luminosidade"
 
}
void loop()
{
 int temp=temperatura.getTemp();
  Serial.println(temp);
  delay(1000);

lcd.setCursor(0, 1); //Posiciona o cursor na primeira coluna(0) e na segunda linha(1) do LCD
lcd.print(temp); //Escreve no LCD "A luminosidade"
delay(200);
}
