#include "libCar.hpp"

int motor_pin1 = 2;
int motor_pin2 = 5;
int motor_pin3 = 7;
int motor_pin4 = 8;
int motor_pwm_pin = 9;

Sonar sonar(sonar_pin);

Motor motor12(motor_pin1, motor_pin2);
Motor motor34(motor_pin3, motor_pin4);
Car car(motor12, motor34);
Servo servo(motor_pwm_pin);
FaceDetector fd(model_path, config_path, cam_index);

int main() {
  while (1) {
    fd.cap_frame();
    fd.process_frame();
    switch (fd.response()) {
    case RIGHT:
      motor.turn_left();
      break;
    case LEFT:
      motor.turn_right();
    break case UP:
      servo.down();
      break;
    case DOWN:
      servo.up();
      break;
    case MIDDLE:
      break;
    default:
      break;
    }
    if (sonar.distance() > max_threshold) {
      motor.forward();
    } else if (sonar.distance() < min_threshold) {
      motor.backward();
    }
  }
}
