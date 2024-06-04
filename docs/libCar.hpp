#include "libServo.h"
#include <iostream>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <wiringPi.h>

class Motor {
public:
  Motor(int Pin1_, int Pin2_);
  void run();
  void run_reverse();
  // 需要后台运行，以免阻塞线程
  void run_awhile(int duration_ms);
  void run_reverse_awhile(int duration_ms);
  void stop();

private:
  int Pin1, Pin2;
  void run_awhile_thread(int duration_ms);
  void run_reverse_awhile_thread(int duration_ms);
};

Motor::Motor(int Pin1_, int Pin2_) : Pin1(Pin1_), Pin2(Pin2_) {
  pinMode(Pin1, OUTPUT);
  pinMode(Pin2, OUTPUT);
  digitalWrite(Pin1, LOW);
  digitalWrite(Pin2, LOW);
  delay(500);
}

void Motor::run() {
  delay(10);
  digitalWrite(Pin1, HIGH);
  digitalWrite(Pin2, LOW);
}

void Motor::run_reverse() {
  delay(10);
  digitalWrite(Pin1, LOW);
  digitalWrite(Pin2, HIGH);
}

void Motor::stop() {
  digitalWrite(Pin1, LOW);
  digitalWrite(Pin2, LOW);
}

void Motor::run_awhile(int duration_ms) {
  std::thread t(&Motor::run_awhile_thread, this, duration_ms);
  t.detach(); // 让线程在后台运行
}

void Motor::run_awhile_thread(int duration_ms) {
  // delay(10);
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  run();
  std::this_thread::sleep_for(std::chrono::milliseconds(duration_ms));
  digitalWrite(Pin1, LOW);
  digitalWrite(Pin2, LOW);
}

void Motor::run_reverse_awhile(int duration_ms) {
  std::thread t(&Motor::run_reverse_awhile_thread, this, duration_ms);
  t.detach(); // 让线程在后台运行
}

void Motor::run_reverse_awhile_thread(int duration_ms) {
  // delay(10);
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  run_reverse();
  std::this_thread::sleep_for(std::chrono::milliseconds(duration_ms));
  digitalWrite(Pin1, LOW);
  digitalWrite(Pin2, LOW);
}

class Servo {
public:
  Servo(int pwm_pin_);
  void rotate_to_angle(int angle);

private:
  int pwm_pin;
  int cycle = 200;   // 设置 PMW 的周期为 20ms
  int duty_max = 25; // 设置最大脉宽为 2.5ms，即占空比为 12.5%
  int duty_min = 5;  // 设置最小脉宽为 0.5ms，即占空比为 2.5%
};

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

class Car {
public:
  Car(Motor motor12_, Motor motor34_) : motor12(motor12_), motor34(motor34_) {}

  void forward_awhile(int duration) {
    motor12.run_awhile(duration);
    motor34.run_awhile(duration);
  }

  void stop() {
    motor12.stop();
    motor34.stop();
  }

  void turn_left_awhile(int duration) {
    motor12.run_reverse_awhile(duration);
    motor34.run_awhile(duration);
  }

  void turn_right_awhile(int duration) {
    motor12.run_awhile(duration);
    motor34.run_reverse_awhile(duration);
  }

private:
  Motor motor12;
  Motor motor34;
};