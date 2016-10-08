#include <Bounce2.h>
int botaoluzInterna = 5;
int botaoluzCavalo = 6;
int botaoluzAcamp = 7;

const int luzInterna = 2;
const int luzCavalo = 3;
const int luzAcamp = 4;

int luzInternastate = 0;
int luzCavalostate = 0;
int luzAcampstate = 0;

int botaoluzInternastate = 0;
int botaoluzCavalostate = 0;
int botaoluzAcampstate = 0;

int ultimobotaoluzInternastate = 0;
int ultimobotaoluzCavalostate = 0;
int ultimobotaoluzAcampstate = 0;

Bounce debouncerInterna = Bounce();
Bounce debouncerCavalo = Bounce();
Bounce debouncerAcamp = Bounce();

char c;
void setup() {
  pinMode(luzInterna, OUTPUT);
  pinMode(luzCavalo, OUTPUT);
  pinMode(luzAcamp, OUTPUT);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);

  digitalWrite(luzInterna, LOW);
  digitalWrite(luzCavalo, LOW);
  digitalWrite(luzAcamp, LOW);

  debouncerInterna.attach(botaoluzInterna);
  debouncerInterna.interval(10);
  debouncerCavalo.attach(botaoluzCavalo);
  debouncerCavalo.interval(10);
  debouncerAcamp.attach(botaoluzAcamp);
  debouncerAcamp.interval(10);

  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0)
  {
    c = Serial.read() - '0';
    Serial.flush();
    digitalWrite(c, !digitalRead(c));
  }

  debouncerInterna.update();
  botaoluzInternastate = debouncerInterna.read();
  if (botaoluzInternastate != ultimobotaoluzInternastate)
  {
    if (ultimobotaoluzInternastate == LOW)
      luzInternastate = !luzInternastate;

    digitalWrite(luzInterna, luzInternastate);
  }
  ultimobotaoluzInternastate = botaoluzInternastate;


  debouncerCavalo.update();
  botaoluzCavalostate = debouncerCavalo.read();

  if (botaoluzCavalostate != ultimobotaoluzCavalostate)
  {
    if (ultimobotaoluzCavalostate == LOW)
      luzCavalostate = !luzCavalostate;

    digitalWrite(luzCavalo, luzCavalostate);
  }
  ultimobotaoluzCavalostate = botaoluzCavalostate;


  debouncerAcamp.update();
  botaoluzAcampstate = debouncerAcamp.read();

  if (botaoluzAcampstate != ultimobotaoluzAcampstate)
  {
    if (ultimobotaoluzAcampstate == LOW)
      luzAcampstate = !luzAcampstate;

    digitalWrite(luzAcamp, luzAcampstate);
  }
  ultimobotaoluzAcampstate = botaoluzAcampstate;
}


