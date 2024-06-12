#include <iostream>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <wiringPi.h>

class Car {
public:
  Car(int Motor1Pin1_, int Motor1Pin2_, int Motor2Pin1_, int Motor2Pin2_);
  ~Car();
  void test_motor1_dir();
  void test_motor2_dir();
  void set_default_dir(bool motor1_dir_, bool motor2_dir_);
  void run(bool isForward, int duration);
  void stop();
  void turn_left(int duration);
  void turn_right(int duration);

private:
  int Motor1Pin1, Motor1Pin2, Motor2Pin1, Motor2Pin2;
  bool motor1_dir = true;
  bool motor2_dir = true;
  void motor1_run(bool isForward);
  void motor2_run(bool isForward);
};

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
  delay(500);
  stop();
}

void Car::test_motor2_dir() {
  digitalWrite(Motor2Pin1, HIGH);
  digitalWrite(Motor2Pin2, LOW);
  delay(500);
  stop();
}

void Car::set_default_dir(bool motor1_dir_, bool motor2_dir_) {
  motor1_dir = motor1_dir_;
  motor2_dir = motor2_dir_;
};

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
  motor2_run(0);
  delay(duration);
  stop();
}

Car::~Car() {
  std::cout << "destructor called, car stopped..." << std::endl;
  stop();
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
  softPwmCreate(pwm_pin, duty_max, cycle);
  delay(10);
}

void Servo::rotate_to_angle(int angle) {
  int val = duty_min; // 5-25  0-180
  // 如果全是int，那么精度只有9度
  val = duty_min + angle / 9;
  softPwmWrite(pwm_pin, val);
  delay(10);
}

class Sonar {
public:
  Sonar(int trigger_, int echo_);
  double distance(int timeout);

private:
  void recordPulseLength();
  int trigger;
  int echo;
  volatile long startTimeUsec;
  volatile long endTimeUsec;
  double distanceMeters;
  long travelTimeUsec;
  long now;
};

Sonar::Sonar(int trigger_, int echo_) : trigger(trigger_), echo(echo_) {
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(trigger, LOW);
  delay(500);
}

double Sonar::distance(int timeout) {
  delay(10);

  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  now = micros();

  while (digitalRead(echo) == LOW && micros() - now < timeout)
    ;
  recordPulseLength();

  travelTimeUsec = endTimeUsec - startTimeUsec;
  distanceMeters = 100 * ((travelTimeUsec / 1000000.0) * 340.29) / 2;

  return distanceMeters;
}

void Sonar::recordPulseLength() {
  startTimeUsec = micros();
  while (digitalRead(echo) == HIGH)
    ;
  endTimeUsec = micros();
}
