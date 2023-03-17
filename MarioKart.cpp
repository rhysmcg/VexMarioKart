#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START IQ MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END IQ MACROS


// Robot configuration code.
motor LeftMotor = motor(PORT1, false);
motor RightMotor = motor(PORT6, true);
controller Controller = controller();
touchled TouchLED5 = touchled(PORT5);
bumper Bumper8 = bumper(PORT8);
bumper Bumper9 = bumper(PORT9);

// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;




#pragma endregion VEXcode Generated Robot Configuration

#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;

float myVariable, deadBand, lives;

// "when started" hat block
int whenStarted1() {
  lives = 3.0;
  deadBand = 5.0;
  TouchLED5.setColor(green);
  while (!(lives < 1.0)) {
    if (fabs(static_cast<float>(Controller.AxisA.position())) > deadBand) {
      LeftMotor.setVelocity(100.0, percent);
      RightMotor.setVelocity(100.0, percent);
    }
    else {
      LeftMotor.spin(forward);
      RightMotor.spin(forward);
    }
    if (fabs(static_cast<float>(Controller.AxisD.position())) > deadBand) {
      LeftMotor.setVelocity(-100.0, percent);
      RightMotor.setVelocity(-100.0, percent);
    }
    else {
      LeftMotor.spin(forward);
      RightMotor.spin(forward);
    }
  wait(20, msec);
  }
  return 0;
}

// "when started" hat block
int whenStarted2() {
  while (true) {
    if (Bumper8.pressing()) {
      lives = lives + -1.0;
      wait(2.0, seconds);
    }
    if (Bumper9.pressing()) {
      lives = lives + -1.0;
      wait(2.0, seconds);
    }
    if (lives == 2.0) {
      TouchLED5.setColor(yellow);
    }
    if (lives == 1.0) {
      TouchLED5.setColor(orange);
    }
    if (lives == 0.0) {
      TouchLED5.setColor(red);
    }
  wait(20, msec);
  }
  return 0;
}


int main() {
  vex::task ws1(whenStarted2);
  whenStarted1();
}
