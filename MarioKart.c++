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
controller Controller = controller();
motor LeftDriveSmart = motor(PORT1, 1, false);
motor RightDriveSmart = motor(PORT6, 1, true);
gyro DrivetrainGyro = gyro(PORT4, true);
smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, DrivetrainGyro, 200);

colorsensor Color3 = colorsensor(PORT3);

void calibrateDrivetrain() {
  wait(200, msec);
  Brain.Screen.print("Calibrating");
  Brain.Screen.newLine();
  Brain.Screen.print("Gyro");
  DrivetrainGyro.calibrate();
  while (DrivetrainGyro.isCalibrating()) {
    wait(25, msec);
  }

  // Clears the screen and returns the cursor to row 1, column 1.
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
}

// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
#pragma endregion VEXcode Generated Robot Configuration
// Include the IQ Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;

float myVariable, deadBand, randomnumber, speed;

event message1 = event();
event turnOffNOS = event();

int mathRandomInt(float a, float b) {
  if (a > b) {
    // Swap a and b to ensure a is smaller.
    float c = a;
    a = b;
    b = c;
  }
  int tmpA = static_cast<int>(a);
  int tmpB = static_cast<int>(b);
  int r = tmpA + rand() / (RAND_MAX / (tmpB - tmpA + 1));
  return r;
}

// "when Controller ButtonEDown pressed" hat block
void onevent_ControllerButtonEDown_pressed_0() {
  if (Color3.detects(red)) {
    if (static_cast<float>(mathRandomInt(1.0, 10.0)) > 2.0) {
      Brain.playSound(tada);
      speed = 1.0;
      turnOffNOS.broadcast();
    }
    else {
      Brain.playSound(wrongWaySlow);
      Drivetrain.turnFor(right, 1000.0, degrees);
    }
  }
}

// "when started" hat block
int whenStarted1() {
  return 0;
}


int main() {
  // initialize the random number system
  srand(Brain.Timer.system());

  // Calibrate the Drivetrain Gyro
  calibrateDrivetrain();

  // register event handlers
  Controller.ButtonEDown.pressed(onevent_ControllerButtonEDown_pressed_0);
  turnOffNOS(onevent_turnOffNOS_0);

  wait(15, msec);
  whenStarted1();
}
