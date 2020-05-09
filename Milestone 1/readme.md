# Milestone 1

## Attempt 1

To move the robot forward I used this function:
setSpeeds (int leftSpeed, int rightSpeed)

However, the robot's right motor ran at a slightly higher speed,
causing the robot to drift to the left.

## Attempt 2

To try to solve this issue, I tried to set each motor's speed individually:
setLeftSpeed(int speed)
setRightSpeed(int speed)

Through trial and error, I learned that assigning 0.96 percent of left motor's
speed to the right motor evened out the discrepancy and allowed the robot
to drive in a straight line.
