#include "libCar.h"
#include <iostream>
#include <thread>
#include <wiringPi.h>

using namespace std;

int motor_pin1 = 2;
int motor_pin2 = 5;
int motor_pin3 = 7;
int motor_pin4 = 8;

int main() {

  if (wiringPiSetup() == -1) {
    cout << "error" << endl;
    return -1;
  }

  Car car(motor_pin1, motor_pin2, motor_pin3, motor_pin4);

  int duration_time = 300;
  int delay = 800;
  for (int i = 0; i < 3; i++) {
    car.run(1, duration_time);
    cout << "running" << endl;
    // std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  }

  for (int i = 0; i < 3; i++) {
    car.turn_left(duration_time);
    cout << "turn left" << endl;
    // std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  }

  for (int i = 0; i < 3; i++) {
    car.turn_right(duration_time);
    cout << "turn right" << endl;
    // std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  }

  return 0;
}