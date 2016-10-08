const int but1=5;
const int but2=6;
const int but3=7;
const int but4=8;
int but1state=0;
int but2state=0;
int but3state=0;
int but4state=0;
void setup()
{
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(but1,INPUT);
  pinMode(but2,INPUT);
  pinMode(but3,INPUT);
  pinMode(but4,INPUT);
}
void loop()
{
  but1state=digitalRead(but1);
  but2state=digitalRead(but2);
  but3state=digitalRead(but3);
  but4state=digitalRead(but4);
  if(but1state==HIGH)
  digitalWrite(2,HIGH);
  if(but2state==HIGH)
  digitalWrite(3,HIGH);
  if(but3state==HIGH)
  digitalWrite(4,HIGH);
  if(but1state==LOW)
  digitalWrite(2,LOW);
  if(but2state==LOW)
  digitalWrite(3,LOW);
  if(but3state==LOW)
  digitalWrite(4,LOW);
  if(but4state==HIGH)
  {
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  }
  if(but4state==LOW)
  {
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  }
}
