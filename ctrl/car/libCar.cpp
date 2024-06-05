#include "libCar.h"
#include <iostream>
#include <wiringPi.h>

Car::Car(int Motor1Pin1_, int Motor1Pin2_, int Motor2Pin1_, int Motor2Pin2_)
    : Motor1Pin1(Motor1Pin1_), Motor1Pin2(Motor1Pin2_), Motor2Pin1(Motor2Pin1_),
      Motor2Pin2(Motor2Pin2_) {
  pinMode(Motor1Pin1, OUTPUT);
  pinMode(Motor1Pin2, OUTPUT);
  pinMode(Motor2Pin1, OUTPUT);
  pinMode(Motor2Pin2, OUTPUT);
  stop();
  delay(200);
}

void Car::test_motor1_dir() {
  digitalWrite(Motor1Pin1, HIGH);
  digitalWrite(Motor1Pin2, LOW);
  delay(200);
  stop();
}

void Car::test_motor2_dir() {
  digitalWrite(Motor2Pin1, HIGH);
  digitalWrite(Motor2Pin2, LOW);
  delay(200);
  stop();
}

void Car::motor1_run(bool isForward) {
  if (isForward) {
    if (motor1_dir) {
      digitalWrite(Motor1Pin1, HIGH);
      digitalWrite(Motor1Pin2, LOW);
    } else {
      digitalWrite(Motor1Pin1, LOW);
      digitalWrite(Motor1Pin2, HIGH);
    }
  } else {
    if (!motor1_dir) {
      digitalWrite(Motor1Pin1, HIGH);
      digitalWrite(Motor1Pin2, LOW);
    } else {
      digitalWrite(Motor1Pin1, LOW);
      digitalWrite(Motor1Pin2, HIGH);
    }
  }
}

void Car::motor2_run(bool isForward) {
  if (isForward) {
    if (motor2_dir) {
      digitalWrite(Motor2Pin1, HIGH);
      digitalWrite(Motor2Pin2, LOW);
    } else {
      digitalWrite(Motor2Pin1, LOW);
      digitalWrite(Motor2Pin2, HIGH);
    }
  } else {
    if (!motor2_dir) {
      digitalWrite(Motor2Pin1, HIGH);
      digitalWrite(Motor2Pin2, LOW);
    } else {
      digitalWrite(Motor2Pin1, LOW);
      digitalWrite(Motor2Pin2, HIGH);
    }
  }
}

void Car::run(bool isForward, int duration) {
  delay(10);
  if (isForward) {
    // Motor1正转
    motor1_run(1);
    // Motor2正转
    motor2_run(1);
    delay(duration);
  } else {
    // Motor1反转
    motor1_run(0);
    // Motor2反转
    motor2_run(0);
    delay(duration);
  }
  stop();
}

void Car::stop() {
  digitalWrite(Motor1Pin1, LOW);
  digitalWrite(Motor1Pin2, LOW);
  digitalWrite(Motor2Pin1, LOW);
  digitalWrite(Motor2Pin2, LOW);
}

void Car::turn_left(int duration) {
  // Motor1反转
  motor1_run(0);
  // Motor2正转
  motor2_run(1);
  delay(duration);
  stop();
}

void Car::turn_right(int duration) {
  // Motor1正转
  motor1_run(1);
  // Motor2反转
  motor1_run(0);
  delay(duration);
  stop();
}

Car::~Car() {
  std::cout << "destructor called, car stopped..." << std::endl;
  stop();
}