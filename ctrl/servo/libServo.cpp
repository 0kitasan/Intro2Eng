#include "libServo.h"
#include <iostream>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

Servo::Servo(int pwm_pin_) : pwm_pin(pwm_pin_) {
  if (wiringPiSetup() == -1)
    exit(1);
  softPwmCreate(pwm_pin, duty_max, cycle);
}

void Servo::rotate_to_angle(int angle) {
  int val = duty_min; // 5-25  0-180
  // 如果全是int，那么精度只有9度
  val = duty_min + angle / 9;
  softPwmWrite(pwm_pin, val);
}
