#include <ZumoShield.h>

ZumoMotors motors;

const int LEFT_SPEED = 250;
const int RIGHT_SPEED = 0.96 * LEFT_SPEED;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  motors.setLeftSpeed(LEFT_SPEED);
  motors.setRightSpeed(RIGHT_SPEED);
  delay(4000);
  motors.setSpeeds(0, 0);
  while (true) {

  }

}
