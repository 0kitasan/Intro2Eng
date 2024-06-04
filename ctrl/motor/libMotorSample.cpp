#include "libMotor.h"
#include <iostream>
#include <thread>
#include <wiringPi.h>

using namespace std;

int motor_pin1 = 2;
int motor_pin2 = 5;
int motor_pin3 = 7;
int motor_pin4 = 8;

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

int main() {

  if (wiringPiSetup() == -1) {
    cout << "error" << endl;
    return -1;
  }
  Motor motor12(motor_pin1, motor_pin2);
  Motor motor34(motor_pin3, motor_pin4);
  Car car(motor12, motor34);

  for (int i = 0; i < 3; i++) {
    car.forward_awhile(300);
    cout << "running" << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
  }
  car.stop();

  for (int i = 0; i < 3; i++) {
    car.turn_left_awhile(300);
    cout << "turn left" << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
  }
  car.stop();

  for (int i = 0; i < 3; i++) {
    car.turn_right_awhile(300);
    cout << "turn right" << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
  }
  car.stop();

  return 0;
}