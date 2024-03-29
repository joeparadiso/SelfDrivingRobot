# SelfDrivingRobot

This repository has the Arduino code for a self driving vehicle

Description:
  This code was used on an Arduino microcontroller and controlled a custom built vehicle for an engineering competition at Grand Valley State University. The           competition was called "The Robo-Sockey Competition", which was a mix between soccer and hockey. The competition was a semester long and included all of the students that were enrolled in Introduction to Engineering II. Students were tasked with creating an Arduino robot from scratch that could navigate itself through obstacles without human assistance. Using a 6-foot-by-6-foot arena, teams have three minutes to compete with each other to deliver the most amount of balls into a goal. 
  
colors.h -- This is the header file that contains the code for changing the LED light colors and patterns on a NeoPixel light ring. The colors and patterns     correspond to different states in the program's state machine code. The colors and patterns were used as a visual way to help troubleshoot the development of the self driving robot and clearly display the current state/message of the robot as it performed its tasks. For instance, when in the 'random movement' state, the LED ring displayed purple and white lights. When the robot encountered an obstacle using one of the multiple infrared sensors, the light would change according to which sensor detected an obstacle. For example, if the infrared sensor detected an obstacle front and center of the vehicle, the LED ring switched from its current color to green which indicates a front-center obstacle. A list of the colors and corresponding states/messages was referenced during testing the robot. The colors can be seen in the main code after each switch case.

robot.h -- This is the header file that contains the global variables, declarations, and definitions for the many parts of the self driving robot and its code. This file also contains custom functions that were used to control the movement of the vehicle.

JARVIS_MARK_II_V8.4.ino -- This is the main program used to control the self driving robot. This program was developed as a state machine where, depending on the environment, the robot would switch to the appropriate state to address the environment. For example, once the robot begins moving, it goes into a random movement state. As it maneuvers the competition arena, it encounters fixed obstacles on the ground. If the obstacle was detected using the limit switch on the front left of the robot, the state switches from randomMovement to bumperAvoid. The bumperAvoid state executes code that is designed to handle fixed obstacles on the ground. Once bumperAvoid has been executed, the state returns to randomMovement until the next event occurs.

![robot_image](https://user-images.githubusercontent.com/82463730/190691295-3c22a76d-eea7-4296-9dc7-c42cc5345149.JPG)
![robot_image2](https://user-images.githubusercontent.com/82463730/190691714-586f9eb8-0394-4ae1-856e-748255ca5787.JPG)
![robot_image3](https://user-images.githubusercontent.com/82463730/190691745-a0e02656-d05f-4675-a05b-f78f5a010c53.JPG)
