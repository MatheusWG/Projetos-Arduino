int b = 2;
int estado;


void setup()
{
  pinMode(2, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(b, INPUT);


}

void loop()
{
  int estado = (digitalRead(b));
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  digitalWrite(12, LOW);
  if (estado == LOW)
  {
    digitalWrite(11, HIGH);
    delay(1000);
    digitalWrite(11, LOW);
    delay(50);
    digitalWrite(12, HIGH);
    delay(4000);
    digitalWrite(12, LOW);
    delay(50);
    
  }
  if (estado == HIGH)
  {
    digitalWrite(10, HIGH);
  }
}
