#include "libSonar.h"
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

  Sonar sonar;
  sonar.init(pin1, pin2);

  while (1) {
    cout << "Distance is " << sonar.distance(30000) << " cm." << endl;
  }
  return 0;
}
