#include <Servo.h>

// values for SERVO can be from 0 to 180
#define SERVO_RANGE 180

// number of servos in system
#define NUMBER_OF_POSITIONS 3

// pins the srvos are located on
const int SERVO_IO_LOCATIONS[NUMBER_OF_POSITIONS] = {11, 10, 9};

// pointer to servo objects, used of control servos
Servo* pServo[NUMBER_OF_POSITIONS];

//Data on where to place the servos
int servo_current_locations[NUMBER_OF_POSITIONS] = {SERVO_RANGE,SERVO_RANGE,SERVO_RANGE};

unsigned long pasttime = 0;
unsigned long currenttime = millis();
int finished = 0;

void setup() {
  for(int i = 0 ; i < NUMBER_OF_POSITIONS; i++)
  {
      // Create a new Servo object, and keep a pointer to it.
      pServo[i] = new Servo;

      // User the pointer to attach a control line to the servo.
      pServo[i]->attach(SERVO_IO_LOCATIONS[i]);

      // Write the default start position to the servo.
      pServo[i]->write(servo_current_locations[i]);
  }
}
// increases digit one and hour servo angle, 9 postions
int posincrone(int x) {
  int y;
  y = x - ( SERVO_RANGE / 9 );
  return y;
}
// increases digit two servo angle, 5 postions
int posincrtwo(int x) {
  int y;
  y = x - ( SERVO_RANGE / 5);
  return y;
}

void loop() {
  unsigned long currenttime = millis();
  
    // checks to see if 1 min has gone by.
  if (currenttime - pasttime > 60000 || finished != 1) {
      pasttime = currenttime;
    
    // if the servo 1 is not less then zeros it will move it one postion down
      if (servo_current_locations[0] >= 0) {
        servo_current_locations[0] = posincrone(servo_current_locations[0]);
        pServo[0]->write(servo_current_locations[0]);
      
    // if servo 1 is less then 0 it will reset it to 180 and move servo 2 one postion down 
      }else if (servo_current_locations[0] < 0 || servo_current_locations[1] >= 0 ) {
        servo_current_locations[0] = SERVO_RANGE;
        servo_current_locations[1] = posincrtwo(servo_current_locations[1]);
        pServo[1]->write(servo_current_locations[1]);
        
     // if servo 2 is less then 0 it will reset it to 180 and move servo 3 one postion down
      }else if (servo_current_locations[1] < 0) {
        servo_current_locations[1] = SERVO_RANGE;  
        servo_current_locations[2] = posincrone(servo_current_locations[3]);
        pServo[2]->write(servo_current_locations[2]);
  }
  // checks to see if countdown has finished
   if (servo_current_locations[2] == 0 || servo_current_locations[1] == 0 || servo_current_locations[0] ==0) {
     finished = 1;
    }
  }
}
