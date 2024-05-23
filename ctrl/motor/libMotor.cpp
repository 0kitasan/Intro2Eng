#include "libMotor.h"
#include <iostream>
#include <wiringPi.h>

Motor::Motor(int Pin1, int Pin2, bool direction) {
  this->Pin1 = Pin1;
  this->Pin2 = Pin2;
  this->direction = direction;
  pinMode(Pin1, OUTPUT);
  pinMode(Pin2, OUTPUT);
  digitalWrite(Pin1, LOW);
  digitalWrite(Pin2, LOW);
  delay(500);
}

void Motor::run() {
  delay(10);
  if (direction) {
    digitalWrite(Pin1, HIGH);
    digitalWrite(Pin2, LOW);
  } else {
    digitalWrite(Pin1, LOW);
    digitalWrite(Pin2, HIGH);
  }
}
