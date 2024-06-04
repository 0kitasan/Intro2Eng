#include <iostream>
#include <wiringPi.h>

#define SERVO 2
#define PERIOD 20.0

// 软件模拟PWM

void angle2pwm(int servo_pin, double angle) {
  // 0:0.5ms
  // 90:1.5ms
  // 180:2.5ms
  double time = 0.5 + angle / 90;
  digitalWrite(servo_pin, HIGH);
  delay(time);
  digitalWrite(servo_pin, LOW);
  delay(PERIOD - time);
  digitalWrite(servo_pin, HIGH);
  delay(time);
  digitalWrite(servo_pin, LOW);
  delay(PERIOD - time);
  delay(5 * PERIOD);
  std::cout << "angle=" << angle << std::endl;
}

int main(void) {
  wiringPiSetup();        // wiringOP 库初始化。
  pinMode(SERVO, OUTPUT); // 把引脚设置为输出模式。
  digitalWrite(SERVO, HIGH);
  delay(1);
  digitalWrite(SERVO, LOW);
  delay(19);
  delay(19);
  delay(1000);
  angle2pwm(SERVO, 180);
  delay(1000);
  angle2pwm(SERVO, 90);
  delay(1000);
  angle2pwm(SERVO, 0);
  delay(1000);
  for (int angle = 0; angle < 180; angle += 5) {
    angle2pwm(SERVO, angle);
    delay(100);
  }
  return 0;
}