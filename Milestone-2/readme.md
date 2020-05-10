# Milestone 2

## Attempt 1

I attempted to steer the robot using Bang Bang Control

Before the robot drives along the line on the floor, it calibrates its sensor
by rotating back and forth, then it follows the line, adjusting its steering
angle once the line is 200 units to the left or right of the robot's center.

While the robot tries to follow the line, by it's third turn, it no longer
steers sharp enough in time to continue following the line's path.

## Attempt 2

I then attempted to steer the robot using Proportional Control to improve the
robot's steering capabilities.

With this configuration, the robot manages to follow the line and stay centered
for the entire length of the winding path.

## Attempt 3

I then included Derivative Control in the Robot's calculations.

Because the error was improved even more by the inclusion of this extra parameter,
I was able to increase the speed of the robot and still accurately follow the line.

## Attempt 4

To instanstiate full PID Control, I included an integral term that summed
the total error in order to determine whether the robot was spending more time
on one side of the line than the other.
