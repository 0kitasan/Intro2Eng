#include "libServo.h"
#include <iostream>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define PWM_PIN 9

Servo servo(PWM_PIN);

int main() {
  for (int i = 0; i < 180; i++) {
    servo.rotate_to_angle(i);
    delay(100);
  }
  return 0;
}