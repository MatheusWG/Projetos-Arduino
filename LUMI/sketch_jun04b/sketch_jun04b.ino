void setup() 
{
Serial.begin(9600);  
pinMode(7,OUTPUT);
}

void loop() 
{
  int LUMI=analogRead(0);
  Serial.println(LUMI);
  delay(100);
  if(LUMI>600)
  {
  digitalWrite(7,HIGH);
  }
  else
  digitalWrite(7,LOW);

}
