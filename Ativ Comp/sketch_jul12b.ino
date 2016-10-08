#include <SPI.h>
#include <Ethernet.h>
#include <Thermistor.h>
Thermistor temperatura(0);
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#include <Ultrasonic.h>
#define pino_trigger 6
#define pino_echo 7
Ultrasonic ultrasonic(pino_trigger, pino_echo);
 
byte mac[] = {
  0x90, 0xA2, 0xDA, 0x0E, 0xB3, 0x00
};
IPAddress ip(172, 20, 33, 70);
IPAddress gateway(172, 20, 32, 1);
IPAddress subnet(255, 255, 255, 0);


EthernetServer server(80);

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperatura:");
  lcd.setCursor(0, 1);
  lcd.print("Luminosidade:");
  lcd.setCursor(15, 0);
  lcd.print("C");
  
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();

}
void loop() {
  int temp = temperatura.getTemp();
  int LUMI = analogRead(2);

  Serial.println(temp);
  Serial.println(LUMI);
  delay(300);
  lcd.setCursor(12, 0);
  lcd.print(temp);
  delay(200);
  lcd.setCursor(13, 3);
  lcd.print(LUMI);
  delay(200);
  lcd.clear();
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);

  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");

    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);

        if (c == 'n' && currentLineIsBlank) {

          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println("Refresh: 1"); //Recarrega a pagina a cada 2seg
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.print("<font color=#FF0000><b><u>");
          client.print("Envio de informacoes pela rede utilizando Arduino");
          client.print("</u></b></font>");
          client.println("<br />");
          client.println("<br />");

          int porta_digital = digitalRead(3);
          client.print("Porta Digital 3 : ");
          client.print("<b>");
          client.print(porta_digital);
          client.println("</b>");
          client.print("  (0 = Desligada, 1 = Ligada)");
          client.println("<br /><br />");

          client.print("Temperatura :   ");
          client.print("<b>");
          client.print(temp);
          client.println(" graus");
          client.println("</b><br />");
          client.println("Luminosidade : ");
          client.print("<b>");
          client.print(LUMI);
          client.println("</b><br />");
          client.print("Distancia em cm :   ");
          client.print("<b>");
          client.print(cmMsec);
          client.println("</b></html>");
          break;
        }
        if (c == 'n') {

          currentLineIsBlank = true;
        }
        else if (c != 'r') {

          currentLineIsBlank = false;
        }
      }
    }

    delay(1);

    client.stop();
  }
  
}
