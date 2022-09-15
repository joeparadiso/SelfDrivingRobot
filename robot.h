/***********************************************************
*THIS IS THE LIBRARY FOR TEAM #4 ROBOT
***********************************************************/
//GLOBAL VARIABLES
  unsigned long currentTime;            // time value to track current time
  unsigned long startTime;              // time value to track start time
  #define pause 5000                    // defines pause for timer
  #define LEDPIN A0                     // defines built in LED
  int sensorState = 0, lastState=0;     // variables for reading the IR breakbeam status
//===========================================================================================

//CONTINUOUS SERVO DEFINITONS
  Servo gateServo;                      // Names the continuous servo used for ball gate as gateServo
  Servo leftMotor;                      // Names the left continuous servo motor/wheel as leftMotor
  Servo rightMotor;                     // Names the right continuous servo motor/wheel as rightMotor
//===========================================================================================

//LINE FOLLOWING DEFINITIONS
  #define uchar unsigned char           // Used in the line following array
  uchar data[16];                       // Setup array for line follower
  uchar t;                              // Used in the way 'i' is normally used/incremented
//===========================================================================================

//ULTRASONIC DEFINITIONS
  #define RIGHT_TRIGGER_PIN 6           // Sets right trigger to pin 6
  #define RIGHT_ECHO_PIN 5              // Sets right echo to pin 5
  #define LEFT_TRIGGER_PIN 8            // Sets left trigger to pin 8
  #define LEFT_ECHO_PIN 7               // Sets left echo to pin 7
  #define CENTER_TRIGGER_PIN 13         // Sets center trigger to pin 13
  #define CENTER_ECHO_PIN 2             // Sets center echo to pip 2
  #define MAX_DISTANCE 200              // Sets max measuring dist. to 200 cm

  NewPing sonarR(RIGHT_TRIGGER_PIN, RIGHT_ECHO_PIN, MAX_DISTANCE);  // Setup right ultrasonic sensor as sonarR
  NewPing sonarL(LEFT_TRIGGER_PIN, LEFT_ECHO_PIN, MAX_DISTANCE);    // Setup left ultrasonic sensor as sonarL
  NewPing sonarC(CENTER_TRIGGER_PIN, CENTER_ECHO_PIN, MAX_DISTANCE);// Setup center ultrasonic sensor as sonarC
//===========================================================================================

//sensor location declaration 
float centerIR=0;                   //Center IR initialized to zero
float leftIR=0;                     //Left IR initialized to zero
float rightIR=0;                    //Right IR initialized to zero
int ultrasonicL=0;                  //Left ultrasonic initialized to zero
int ultrasonicR=0;                  //Right ultrasonic initialized to zero
int ultrasonicC=0;                  //Center ultrasonic initialized to zero
int breakBeam=1;                    //Breakbeam initialized to 1 (NO BALL PRESENT)
int bumperLeft;                     //Left bumper declared
int bumperRight;                    //Right bumper declared
int turnNum = 0;                    //This variable is used for the random number generator for turning directions


  
//===========================================================================================

//RIGHT MOTOR CONTROLS
//  RIGHT SERVO MOTOR IS PWM PIN 10
//===========================================================================================

//LEFT MOTOR CONTROLS
//  LEFT SERVO MOTOR IS PWM PIN 11
//===========================================================================================

//GATE SERVO CONTROL
//  GATE SERVO MOTOR IS PWM PIN 9
//===========================================================================================

//LIMIT SWITCH VARIABLES
  int leftBumper = 4;
  int rightBumper = 3;
  int bothBumpers;
//=========================================================================================== 

//IR BREAKBEAM VARIABLES
  int breakbeamIn = 12;
// breakbeamOut is just 5V in, GND out; 
//===========================================================================================

//SHARP IR OBJECT DETECTORS VARIABLES  
  #define irSensorR A3                // right IR on pin A3
  #define irSensorL A2                // left IR on pin A2
  int val1 = 0;                       // variable to store the values from sensor(initially zero)
  int val2 = 0;                       // variable to store the values from sensor(initially zero)
//===========================================================================================

//ENUMERATION STATES
enum state {
  start,
  randomMovement,
  bumperAvoid,
  IRavoidR,
  IRavoidL,
  IRavoidC,
  ultrasonicAvoid,
  ultrasonicAvoidCenter,
  ballDetect,
  wallFollow,
  score,
  followingLine
};
enum state currentState = start;
//===========================================================================================
//////////////////////   CUSTOM FUNCTIONS     ///////////////////////////////////////////////
////////////////// CALLED INSIDE OF lineFollow() ////////////////////////////////////////////
//===========================================================================================
void largerRight()//Large right turn for line sensor, yellow light
{
  leftMotor.write(1900);    //V8: 1800
  rightMotor.write(1700);   //V8: 1600
  delay(200);
//  pink();
}
//===========================================================================================
void midRight()//Small right turn for line sensor, blue light
{
  leftMotor.write(1800);    //V8.1: 1700
  rightMotor.write(1475);
  delay(100);
//  orange();  
}
//===========================================================================================
void slightRight()//Small right turn for line sensor, blue light
{
  leftMotor.write(1800);
  rightMotor.write(1400);
//  red();  
}
//===========================================================================================
void centerRight()//Drive both motors forward for centered line, green light
{
  leftMotor.write(1700);
  rightMotor.write(1350);
//  white();
}
//===========================================================================================
void center()//Drive both motors forward for centered line, green light
{
  leftMotor.write(1600);
  rightMotor.write(1400);
//  redBlue();
}
//===========================================================================================
void centerLeft()//Drive both motors forward for centered line, green light
{
  leftMotor.write(1650);
  rightMotor.write(1300);
//  purpleWhite();
}
//===========================================================================================
void slightLeft()//Small left turn for line sensor, red light
{
  leftMotor.write(1600);
  rightMotor.write(1200);
//  blue();
}
//===========================================================================================
void midLeft()//Small left turn for line sensor, red light
{
  leftMotor.write(1550);
  rightMotor.write(1200);   //V8.1: 1300
  delay(100);
//  green();
}
//===========================================================================================
void largerLeft()//Large left turn for line sensor, aqua light
{
  leftMotor.write(1300);    //V8: 1400
  rightMotor.write(1000);   //V8: 1100
  delay(200);
//  aqua();
}
//===========================================================================================
void goal()//Stop and pause 
{
  leftMotor.write(1500); 
  rightMotor.write(1500);
//  orange();
}
//===========================================================================================
