#include <Wire.h>
#include <ZumoShield.h>

ZumoMotors motors;
ZumoReflectanceSensorArray linesensors(QTR_NO_EMITTER_PIN);
ZumoBuzzer buzzer;

void setup() {
  int i;
  int spin_direction = 1;
  motors.setSpeeds(80*spin_direction, -80*spin_direction);
  for(i = 0; i<100; i++){
    linesensors.calibrate();
    if(i%50 == 25){ // every 50 loops, starting on loop 25...
      spin_direction = -spin_direction;
      motors.setSpeeds(80*spin_direction, -80*spin_direction);
    }
    delay(20);
  }
  motors.setSpeeds(0,0);
  delay(500);
}

unsigned int sensor_vals[6];
const int THRESHOLD = 600;
const int LEFT_SPEED = 300;
const int RIGHT_SPEED = 0.96 * LEFT_SPEED;
int line_position;
char path[50];
int turn_counter = 0;

void loop() {
  line_position = linesensors.readLine(sensor_vals);
  if(sensor_vals[0] > THRESHOLD && sensor_vals[5] > THRESHOLD){
    solved(); 
  }else if(sensor_vals[0] > THRESHOLD && sensor_vals[1] > THRESHOLD){
    path[turn_counter] = 'L';
    turn_counter++;
    turn_left();
  } else if(sensor_vals[4] > THRESHOLD && sensor_vals[5] > THRESHOLD){
    path[turn_counter] = 'R';
    turn_counter++;
    turn_right();
  } else {
    follow_line();
  }
}

void turn_left() {
  motors.setSpeeds(-LEFT_SPEED*0.75, RIGHT_SPEED*1.5);
  linesensors.read(sensor_vals);
  while(sensor_vals[0] > THRESHOLD && sensor_vals[1] > THRESHOLD){
      linesensors.read(sensor_vals);
  } 
  delay(115);  
}

void turn_right() {
  motors.setSpeeds(LEFT_SPEED*1.5, -RIGHT_SPEED*0.75);
  linesensors.read(sensor_vals);
  while(sensor_vals[4] > THRESHOLD && sensor_vals[5] > THRESHOLD){
      linesensors.read(sensor_vals);
  }
  delay(115);  
}

double PROPORTION_GAIN = 0.2;
double DERIVATIVE_GAIN = 3;
double INTEGRAL_GAIN = 0.001;
int last_error = 0;
int total_error = 0;

void follow_line() {
  int line_position = linesensors.readLine(sensor_vals);
  int error = line_position - 2500;
  int error_change = error - last_error;
  int left_speed = LEFT_SPEED + PROPORTION_GAIN * error + DERIVATIVE_GAIN * error_change + INTEGRAL_GAIN * total_error;
  int right_speed = RIGHT_SPEED + -PROPORTION_GAIN * error + -DERIVATIVE_GAIN * error_change + -INTEGRAL_GAIN * total_error;
  last_error = error;
  total_error = total_error + error;
  motors.setSpeeds(left_speed, right_speed);
}

void solved(){
  motors.setSpeeds(0,0);
  for(int i=0; i<turn_counter+1; i++){
    if(path[i] == 'L'){
      buzzer.playNote(NOTE_G(5), 200, 15);
      delay(400);
    }
    if(path[i] == 'R'){
      buzzer.playNote(NOTE_G(6), 200, 15);
      delay(400);
    }
  }
  while(true){
    // do nothing!
  }
}
