#include "libMotor.h"
#include <iostream>
#include <wiringPi.h>

using namespace std;

int pin1 = 2;
int pin2 = 6;

int main() {
  if (wiringPiSetup() == -1) {
    cout << "error" << endl;
    return -1;
  }
  Motor motor(pin1, pin2, 0);

  while (1) {
    motor.run();
    cout << "running" << endl;
  }
  return 0;
}
