#include "libSonar.h"
#include <iostream>
#include <wiringPi.h>


using namespace std;

int trigger = 2;
int echo = 6;

int main() {
  if (wiringPiSetup() == -1) {
    cout << "error" << endl;
    return -1;
  }

  Sonar sonar;
  sonar.init(trigger, echo);

  while (1) {
    cout << "Distance is " << sonar.distance(30000) << " cm." << endl;
  }
}
