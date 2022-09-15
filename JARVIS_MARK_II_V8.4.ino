/********************************************************************************************
  =============================================================================================
   ROBOT_WORKING_CODE:
    V1: 3/23/19 Initial code written
    v2: 3/25/19 Created library & added some sensors
    V3: 3/30/19 Added working scoring mechanism
    V3.1: 4/1 changed back settings to obstacle avoidance program
    V3.3: --- Good working version of obstacle avoidance
    v3.4: 4/4 Reverse before center turn and added line following state
    V3.5: 4/4 Changed line follower works well, random works well
    V3.6: 4/4 Slow down line follow command speeds-- Nice but shaky. The motor reverse culprit...
    V3.7: 4/4 Fix the shaky line following
    V3.8: 4/13 Added center ultrasonic sensor
    V3.9: 4/13 Changed the line follwing speeds, added center ultrasonic state & color
    V8.0: 4/15 Current working code in the working code folder
    V8.1: 4/15 Adjusting the issues addressed in the notes below for today
          *UPDATE* All is working well except line follower is losing track at goal
    V8.2: 4/15 Attempt to fix line follower when at the goal (to NOT lose line) but still loses it
    V8.3: 4/15 Added the line follower V9 to replace existing line following directions in linefollow state--*UPDATE* This is trash
    V8.4: 4/15 Added delays in the library for the mid & larger left/right turns. Delay times will need adjustment
  ==============================================================================================
  NOTES:
    For 4/7-4/13: Add ultrasonic goal detection, consider inside bumper(?), permanent wheels,
                  add a millis() jump (ball detection), remodel the fenders, implement goal 
                  scoring function, screw in gate servo,
    4/15: Line follower needs adjustment to keep robot on line near goal.
          Center IR needs to be adjusted to discern between balls & obstacles
          Slow down the turning speed during obstacle avoidance so ball is not ejected (DONE FOR IR SENSORS--Joe)
          Consider center trip wire options
  ==============================================================================================
*********************************************************************************************/


#include <Wire.h>                         // Line following library
#include <NewPing.h>                      // Ultrasonic library
#include <Servo.h>                        // Servo motor library
#include <Adafruit_NeoPixel.h>            // NeoPixel library
#include "colors.h"                       // Contains NeoPixel color data 
#include "robot.h"                        // Custom robot library
#include "Adafruit_VL53L0X.h"             // Library for center IR

Adafruit_VL53L0X lox = Adafruit_VL53L0X();  //Used to make a function call for center IR

//===========================================================================================
///////////////   END OF PREPROCESSOR AND GLOBAL VARIABLES    //////////////////////////////
/////////////////////       SETUP LOOP BEGINS         //////////////////////////////////////
//===========================================================================================

void setup() {
  Serial.begin(9600);                     // start serial for output

  startTime = millis();                   // begin timer for comparison

  //NEOPIXEL SETUP
  strip.begin();                          // initialize the LED ring
  pinMode(A0, OUTPUT);                    // Neopixel is on analog pin A0

  //CONTINUOUS SERVO SETUP
  gateServo.attach(9);                    // Continuous servo "gateServo" is attached on pin 9
  leftMotor.attach(11);                   // Continuous servo "leftMotor" is attached on pin 11
  rightMotor.attach(10);                  // Continuous servo "rightMotor" is attached on pin 10

  //LINE FOLLOWER SETUP
  Wire.begin();                           // join i2c bus (address optional for master)
  t = 0;                                  // Define variable used in line follow
  int lineValue = 0;                      // Initial line value is set to zero

  //LIMIT SWITCHES SETUP--SEE COMMENTS!
  pinMode(leftBumper, INPUT_PULLUP);      // **Logic is reversed: 0 is on, 1 is off b/c of pullup**
  pinMode(rightBumper, INPUT_PULLUP);     // **Logic is reversed: 0 is on, 1 is off b/c of pullup**

  //IR BREAKBEAM SETUP
  pinMode(breakbeamIn, INPUT);            // setup to read from the breakbeam pin defined in robot.h
  digitalWrite(breakbeamIn, HIGH);        // turn on the pullup

  //CENTER IR INITIAL STARTUP STATUS (MUST BE INCLUDED)
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }
}

//===========================================================================================
////////////////////////    END OF SETUP LOOP     ///////////////////////////////////////////
////////////////////////    VOID LOOP BEGINS      ///////////////////////////////////////////
//===========================================================================================

void loop() {
  currentTime = millis();

  updateSensors(&ultrasonicL, &ultrasonicR, &ultrasonicC, &leftIR, &rightIR, &centerIR, &breakBeam, &bumperLeft, &bumperRight);
  //  Serial.print("rightIR:     ");
  //  Serial.print(rightIR);
  //  Serial.print("\tLeft IR:     ");
  //  Serial.print(leftIR);
  //  Serial.print("\tCenterIR:    ");
  //  Serial.println(centerIR);
  switch (currentState) {
//=====================================================================================================
    case start: red();
//===================================================================================================== 
      delay(5000);
      currentState = randomMovement;
      break;
//=====================================================================================================
    case randomMovement: purpleWhite();
//=====================================================================================================
      gateServo.write(0);
      leftMotor.write(1700);//left motor speed setting
      rightMotor.write(1300);//right motor speed setting

      updateSensors(&ultrasonicL, &ultrasonicR, &ultrasonicC, &leftIR, &rightIR, &centerIR, &breakBeam, &bumperLeft, &bumperRight);//called to update sensors to check surroundings

      Wire.requestFrom(9, 16);    // request 16 bytes from slave device #9
      while (Wire.available())    // slave may send less than requested
      {
        data[t] = Wire.read();    // receive a byte as character
        if (t < 15)
          t++;
        else
          t = 0;
      }
      if (breakBeam == 0)//Breakbeam values explained: 0 means ball present and 1 means NO ball present
      {
        if (data[0] < 245 || data[2] < 245 || data[4] < 245 || data[6] < 245 || data[8] < 245 || data[10] < 245 || data[12] < 245 || data[14] < 245)
        {
          currentState = followingLine;
        }
      }
      if (bumperLeft == 0 || bumperRight == 0)      //the following conditionals are used to evaluate how to respond to the environment
      {
        currentState = bumperAvoid;
      }
      if (ultrasonicL < 5 && ultrasonicL > 1)
      {
        currentState = ultrasonicAvoid;
      }
      if (ultrasonicR < 5 && ultrasonicR > 1)
      {
        currentState = ultrasonicAvoid;
      }
      if (ultrasonicC < 6)
      {
        currentState = ultrasonicAvoidCenter;
      }
      if (rightIR < 21)//WAS 24
      {
        currentState = IRavoidR;
      }
      if (leftIR < 20)//WAS 20
      {
        currentState = IRavoidL;
      }
      if (centerIR < 262)//was 261
      {
        currentState = IRavoidC;
      }
      break;
//=====================================================================================================
    case bumperAvoid: blue();
//=====================================================================================================   
      if (bumperLeft == 0 && bumperRight == 1)
      {
        leftMotor.write(1200);    //Reverse
        rightMotor.write(1800);
        delay(500);
        leftMotor.write(1800);    //Sharp right turn
        rightMotor.write(1800);
        delay(300);
        leftMotor.write(1500);    //Stop
        rightMotor.write(1500);
      }
      if (bumperLeft == 1 && bumperRight == 0)
      {
        leftMotor.write(1200);    //Revese
        rightMotor.write(1800);
        delay(500);
        leftMotor.write(1200);    //Sharp left turn
        rightMotor.write(1200);
        delay(300);
        leftMotor.write(1500);    //Stop
        rightMotor.write(1500);
      }
      currentState = randomMovement;
      break;
//=====================================================================================================
    case IRavoidC: green();
//=====================================================================================================
      turnNum = random(1, 3);   //1 is left and 2 is right for turning direction 'if' state

      leftMotor.write(1300);    //Reverse
      rightMotor.write(1700);
      delay(600);

      if (turnNum == 1) {       //V8: left 1200, right 1200
        leftMotor.write(1300);
        rightMotor.write(1300);
        delay(700);             //V8: 600
      }
      if (turnNum == 2) {       //V8: left 1800, right 1800
        leftMotor.write(1700);
        rightMotor.write(1700);
        delay(700);             //V8: 600
      }

      leftMotor.write(1500);    //Stop motors
      rightMotor.write(1500);

      currentState = randomMovement;
      break;
//=====================================================================================================
    case IRavoidR: red();
//=====================================================================================================
      updateSensors(&ultrasonicL, &ultrasonicR, &ultrasonicC, &leftIR, &rightIR, &centerIR, &breakBeam, &bumperLeft, &bumperRight);

      leftMotor.write(1300);      //V8: 1200
      rightMotor.write(1300);     //V8: 1200

      delay(400);                 //V8: 300

      leftMotor.write(1500);
      rightMotor.write(1500);

      currentState = randomMovement;
      break;
//=====================================================================================================
    case IRavoidL: yellow();
//=====================================================================================================
      updateSensors(&ultrasonicL, &ultrasonicR, &ultrasonicC, &leftIR, &rightIR, &centerIR, &breakBeam, &bumperLeft, &bumperRight);

      leftMotor.write(1700);      //V8: 1800
      rightMotor.write(1700);     //V8: 1800

      delay(400);                 //V8: 300
      leftMotor.write(1500);
      rightMotor.write(1500);

      currentState = randomMovement;
      break;
//=====================================================================================================
    case ultrasonicAvoid: redBlue();
//=====================================================================================================     
      if (ultrasonicL < 7 && ultrasonicL > 1)
      {
        rightMotor.write(1800);
        leftMotor.write(1800);
        delay(100);
      }
      if (ultrasonicR < 7 && ultrasonicR > 1)
      {
        rightMotor.write(1200);
        leftMotor.write(1200);
        delay(100);
      }
      if (ultrasonicC < 6)
      {
        leftMotor.write(1200);//reverse
        rightMotor.write(1800);
        delay(500);
        rightMotor.write(1800);
        leftMotor.write(1800);
        delay(500);
      }
      currentState = randomMovement;
      break;
//=====================================================================================================
    case ultrasonicAvoidCenter: pink();
//=====================================================================================================
      if (ultrasonicC < 6)
      {
        leftMotor.write(1200);//reverse
        rightMotor.write(1800);
        delay(500);
        rightMotor.write(1800);
        leftMotor.write(1800);
        delay(500);
      }
      currentState = randomMovement;
      break;
//=====================================================================================================
    case ballDetect: //NO COLOR. THIS FUNCTION IS NOT SET UP TO DO ANYTHING.
//=====================================================================================================
      currentState = randomMovement;
      break;
//=====================================================================================================
    case score: orange();
//=====================================================================================================    
      gateServo.write(1);     //GATE SERVO FULL SPEED INTAKE
      leftMotor.write(1100);  //REVERSE MOTORS FAST
      rightMotor.write(1900);      
      delay(500);             
      leftMotor.write(1300);  //REVERSE MOTORS A BIT SLOWER
      rightMotor.write(1700);      
      delay(250);
      rightMotor.write(1500); //STOP MOTORS
      leftMotor.write(1500);
      delay(100);
      gateServo.write(180);   //GATE SERVO FULL SPEED OUTPUT
      leftMotor.write(1900);  //FORWARD MOTORS
      rightMotor.write(1100);
      delay(500);             //Quick forward delay time V8.1: 500
      leftMotor.write(1500);  //STOP MOTORS
      rightMotor.write(1500);
      delay(250);
      leftMotor.write(1400);  //REVERSE MOTORS
      rightMotor.write(1600); 
      delay(500);
      leftMotor.write(1200); //TURN AROUND
      rightMotor.write(1200);
      delay(700);             //V8.1: 500

      breakBeam = 1;
      currentState = randomMovement;
      break;
//=====================================================================================================
    case followingLine: orangeBlue();
//=====================================================================================================
// data[0] is the farthest left sensor and data[14] is the farthest right sensor on line follower
//-----------------------------------------------------------------------------------------------------
      Wire.requestFrom(9, 16);    // request 16 bytes from slave device #9
      while (Wire.available())    // slave may send less than requested
      {
        data[t] = Wire.read();    // receive a byte as character
        if (t < 15)
          t++;
        else
          t = 0;
      }
      Serial.println(currentState);
      if (data[0] < 245)
      {
        largerLeft();
      }
      if (data[2] < 245)
      {
        midLeft();
      }
      if (data[4] < 245)
      {
        slightLeft();
      }
      if (data[6] < 245)
      {
        center();
      }
      if (data[8] < 245)
      {
        center();
      }
      if (data[10] < 245)
      {
        slightRight();
      }
      if (data[12] < 245)
      {
        midRight();
      }
      if (data[14] < 245)
      {
        largerRight();
      }
//----------------------------------------------------------------------------------------------------
//4/13-Old code for goal: Erase if new code works.     
//      if (data[4] < 245 && data[6] < 245 && data[8] < 245 && data[10] < 245)
//      {
//        goal();
//      }
//----------------------------------------------------------------------------------------------------
//4/13-New code for goal:
      if ((data[4] < 245 || data[6] < 245 || data[8] < 245 || data[10] < 245) && (ultrasonicC > 0 && ultrasonicC < 8))//Changed ult.C from 6 to 8
      {
        currentState = score;
      }
      if (data[0] >= 245 && data[2] >= 245 && data[4] >= 245 && data[6] >= 245 && data[8] >= 245 && data[10] >= 245 && data[12] >= 245 && data[14] >= 245)
      {
        currentState = randomMovement;
      }

      break;
//=====================================================================================================
//=====================================================================================================
  }//END SWITCH
}//END MAIN


//==========================================================================================
////////////////////////    END OF MAIN LOOP      ///////////////////////////////////////////
/////////////////////    CUSTOM FUNCTIONS BEGIN      ////////////////////////////////////////
//===========================================================================================
/*===========================================================================================*/
void updateSensors(int *leftultra, int *rightultra, int *centerultra, float *leftir, float *rightir, float *centerir, int *breakB, int *bumperL, int *bumperR)
{
  int arr[10];
  float sum = 0;
  int w = 0;
  
  //need pointers to pass down values to be updated in our functions
    *leftultra = sonarL.ping_cm();
    *rightultra = sonarR.ping_cm();
    *centerultra = sonarC.ping_cm();
    
    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false);
    for (w = 0; w < 10; w++) {
      if (measure.RangeStatus != 4) {
        arr[w] = measure.RangeMilliMeter;
        sum = sum + arr[w];
      }
    }
    
  *centerir = sum / 10;
  sum = 0;
  for (w = 0; w < 11; w++) {
    arr[w] = ((6787 / (analogRead(irSensorL) - 3)) - 4);
    sum = sum + arr[w];
  }
  *leftir = sum / 10;
  sum = 0;
  for (w = 0; w < 10; w++) {
    arr[w] = ((6787 / (analogRead(irSensorR) - 3)) - 4);
    sum = sum + arr[w];
  }
  *rightir = sum / 10;
  *bumperL = digitalRead(leftBumper);
  *bumperR = digitalRead(rightBumper);
  if (digitalRead(breakbeamIn) == 0)
  {
    *breakB = 0;
  }
  //1 is unbroken
  //0 is broken
}
