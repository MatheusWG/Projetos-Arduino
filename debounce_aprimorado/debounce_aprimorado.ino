#include <Bounce2.h>
int ledstate;
int lst;
int ledstate1;
int lst1;
Bounce debouncer = Bounce();
Bounce debouncer1 = Bounce();
void setup() {
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  debouncer.attach(3);
  debouncer.interval(20);
  debouncer1.attach(4);
  debouncer1.interval(20);
}

void loop() {
  debouncer.update();
  int value = debouncer.read();

  if (value != lst)
  {
    if (lst == HIGH)
      ledstate = !ledstate;

    digitalWrite(2, ledstate);
  }
  lst = value;

  debouncer1.update();
  int value1 = debouncer1.read();

  if (value1 != lst1)
  {
    if (lst1 == HIGH)
      ledstate = !ledstate;

    digitalWrite(2, ledstate);
  }
  lst1 = value1;
}
