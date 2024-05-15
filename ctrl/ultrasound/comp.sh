#!/bin/bash
g++ libSonarSample.cpp -o test -lwiringPi libSonar.cpp
./test
g++ libSonarSample.cpp libSonar.cpp -o test -l wiringPi