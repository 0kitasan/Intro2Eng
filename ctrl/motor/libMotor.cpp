#include "libMotor.h"
#include <iostream>
#include <thread>
#include <wiringPi.h>

Motor::Motor(int Pin1, int Pin2) {
  this->Pin1 = Pin1;
  this->Pin2 = Pin2;
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