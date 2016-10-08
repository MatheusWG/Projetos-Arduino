
#include <SPI.h>
#include <Ethernet.h>
#include <Thermistor.h>
Thermistor temperatura(0);
#include <LiquidCrystal.h> //Inclui a biblioteca do LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

 
//Definicoes de IP, mascara de rede e gateway
byte mac[] = {
  0x90, 0xA2, 0xDA, 0x0E, 0xB3, 0x00 };
IPAddress ip(172,20,33,70);          //Define o endereco IP
IPAddress gateway(172,20,32,1);     //Define o gateway
IPAddress subnet(255, 255, 255, 0); //Define a máscara de rede
 
//Inicializa o servidor web na porta 80
EthernetServer server(80);
 
void setup()
{
  //Inicializa a interface de rede
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Temperatura:");
  lcd.setCursor(0, 1);
  lcd.print("Luminosidade:");
  lcd.setCursor(15, 0);
  lcd.print("C");
}
 
void loop() {
  int temp=temperatura.getTemp();
  Serial.println(temp);
  delay(1000);
  int LUMI=analogRead(2);
  Serial.println(LUMI);
  delay(1000);
  lcd.setCursor(13, 0); 
  lcd.print(temp);
  delay(200);
  lcd.setCursor(13, 3); 
  lcd.print(LUMI); 
  delay(200);
 
  //Aguarda conexao do browser
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == 'n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println("Refresh: 1"); //Recarrega a pagina a cada 2seg
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          //Configura o texto e imprime o titulo no browser
          client.print("<font color=#FF0000><b><u>");
          client.print("Envio de informacoes pela rede utilizando Arduino");
          client.print("</u></b></font>");
          client.println("<br />");
          client.println("<br />");
          //Mostra o estado da porta digital 3
          int porta_digital = digitalRead(3);
          client.print("Porta Digital 3 : ");
          client.print("<b>");
          client.print(porta_digital);
          client.println("</b>");
          client.print("  (0 = Desligada, 1 = Ligada)");
          client.println("<br /><br />");
          //Mostra as informacoes lidas pelo sensor ultrasonico
          client.print("Temperatura :   ");
          client.print("<b>");
          client.print(temp);
          client.println(" graus");
          client.println("</b><br />");
          client.println("Luminosidade : ");
          client.print("<b>");
          client.print(LUMI);
          client.println("</b></html>");
          break;
        }
        if (c == 'n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != 'r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    }
}
