#include "libCar.hpp"

#define MOTOR_PIN1 2
#define MOTOR_PIN2 5
#define MOTOR_PIN3 7
#define MOTOR_PIN4 8
#define SERVO_PIN 9
#define MODEL_PATH "../assets/model/face_detector/opencv_face_detector_uint8.pb"
#define CONFIG_PATH "../assets/model/face_detector/opencv_face_detector.pbtxt"

Sonar sonar(sonar_pin);

Motor motor12(MOTOR_PIN1, MOTOR_PIN2);
Motor motor34(MOTOR_PIN3, MOTOR_PIN4);
Car car(motor12, motor34);
Servo servo(SERVO_PIN);
FaceDetector fd(MODEL_PATH, CONFIG_PATH, cam_index);

int main() {
  while (1) {
    fd.cap_frame();
    fd.process_frame();
    switch (fd.result()) {
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
