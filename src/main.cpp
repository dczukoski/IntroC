/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       uriel and dczukoski                                                    */
/*    Created:      2/3/2026, 6:31:16 PM                                      */
/*    Description:  Intro to C++ up to week 5 - IQ2 project                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the IQ2 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here
motor leftMotor = motor(PORT1, false);
motor rightMotor = motor(PORT7, true);
gyro inert = gyro(PORT8); // we are using gyro mounted upside down because syntax is closer to V5 inertial 
bumper frontBumper = bumper(PORT7);
colorsensor color1 = colorsensor(PORT11); // could be an optical instead
distance lidar = distance(PORT9);
controller controller1 = controller();
motor leftArm = motor(PORT3, false);
motor rightArm = motor(PORT10, true);

// Debugging Function
void brainDisplay(){
    while(true){
        Brain.Screen.clearScreen();
        Brain.Screen.printAt(1, 30, "L Motor %.2f", leftMotor.position(deg));
        Brain.Screen.printAt(30, 30, "R Motor %.2f", rightMotor.position(deg));
        Brain.Screen.printAt(1,50,"Left Arm %f",leftArm.position(degrees));
        Brain.Screen.printAt(30,50,"Right Arm %f",rightArm.position(degrees));
        Brain.Screen.printAt(1, 70, "Inert %.2f", inert.rotation(deg));
        Brain.Screen.printAt(30, 70,"Distance %.2f",lidar.objectDistance(inches));
        Brain.Screen.printAt(1,90, "FrontB %d",frontBumper.pressing());
        Brain.Screen.printAt(20,90, "Line %d",color1.brightness());
        wait(.2, sec);
    }
}

// Simple Motion
void driveForward(double distance){
    leftMotor.resetPosition();
    while(leftMotor.position(deg) < distance){
        leftMotor.spin(forward, 100, pct);
        rightMotor.spin(forward, 100, pct);
        wait(.2, sec);
    }
    leftMotor.stop();
    rightMotor.stop();
}

void driveReverse(double distance){
    leftMotor.resetPosition();
    while(-leftMotor.position(deg) < distance){
        leftMotor.spin(reverse, 100, pct);
        rightMotor.spin(reverse, 100, pct);
        wait(.2, sec);
    }
    leftMotor.stop();
    rightMotor.stop();
}

void turnRight(double turney){
    inert.resetRotation();
    while(inert.rotation(deg) < turney){
        leftMotor.spin(forward, 50, pct);
        rightMotor.spin(reverse, 50, pct);
        wait(.2, sec);
    }
    leftMotor.stop();
    rightMotor.stop();
}

void turnLeft(double turney){
    inert.resetRotation();
    while(-inert.rotation(deg) < turney){
        leftMotor.spin(reverse, 50, pct);
        rightMotor.spin(forward, 50, pct);
        wait(.2, sec);
        }
    leftMotor.stop();
    rightMotor.stop();
}

// Using other sensors
void driveUntilBumperHit(){
    while(frontBumper.pressing() == false){
        leftMotor.spin(forward, 100, pct);
        rightMotor.spin(forward, 100, pct);
        wait(.2, sec);
    }
    leftMotor.stop();
    rightMotor.stop();
}

void goUntilLine() {
   while(color1.brightness() > 30){
        leftMotor.spin(forward, 75, pct);
        rightMotor.spin(forward, 75, pct);
	    wait(.2, sec);
    }
    leftMotor.stop();
    rightMotor.stop();
}

void goForwardMultipleLines(int numberToGoTo) {
	int numberSeen = 0;
    while(numberSeen < numberToGoTo){
        while(color1.brightness() > 30){
            leftMotor.spin(forward, 75, pct);
            rightMotor.spin(forward, 75, pct);
            wait(.2, sec);
        }
        while(color1.brightness() < 30){
            leftMotor.spin(forward, 75, pct);
            rightMotor.spin(forward, 75, pct);
            wait(.2, sec);
        }
        numberSeen++;
	}
    leftMotor.stop();
    rightMotor.stop();
}

void goCloseToObject(double distance) {
   while(lidar.objectDistance(inches) < distance){
        leftMotor.spin(forward, 75, pct);
        rightMotor.spin(forward, 75, pct);
	    wait(.2, sec);
    }
    leftMotor.stop();
    rightMotor.stop();
}

void turnLeftToObject(double minDistance, double maxDistance) {
   while(lidar.objectDistance(inches) > minDistance && lidar.objectDistance(inches) < maxDistance){
        leftMotor.spin(forward, 25, pct);
        rightMotor.spin(reverse, 25, pct);
	   wait(.2, sec);
    }
    leftMotor.stop();
    rightMotor.stop();
}

void turnRightToObject(double minDistance, double maxDistance) {
   while(lidar.objectDistance(inches) > minDistance && lidar.objectDistance(inches) < maxDistance){
        leftMotor.spin(forward, 25, pct);
        rightMotor.spin(reverse, 25, pct);
	   wait(.2, sec);
    }
    leftMotor.stop();
    rightMotor.stop();
}

// Bang Bang Motion
void driveForwardBangBang(double distance){
    leftMotor.resetPosition();
    while(leftMotor.position(deg) < distance * .8 ){
        leftMotor.spin(forward, 100, pct);
        rightMotor.spin(forward, 100, pct);
        wait(.2, sec);
    }
    while(leftMotor.position(deg) < distance){
        leftMotor.spin(forward, 10, pct);
        rightMotor.spin(forward, 10, pct);
        wait(.2, sec);
    }
    leftMotor.stop();
    rightMotor.stop();
}

void driveReverseBangBang(double distance){
    leftMotor.resetPosition();
    while(-leftMotor.position(deg) < distance * .8 ){
        leftMotor.spin(reverse, 100, pct);
        rightMotor.spin(reverse, 100, pct);
        wait(.2, sec);
    }
    while(leftMotor.position(deg) < distance){
        leftMotor.spin(reverse, 10, pct);
        rightMotor.spin(reverse, 10, pct);
        wait(.2, sec);
    }
    leftMotor.stop();
    rightMotor.stop();
}

void turnRightBangBang(double turney){
    inert.resetRotation();
    while(inert.rotation(deg) < turney * .8){
        leftMotor.spin(forward, 100, pct);
        rightMotor.spin(reverse, 100, pct);
        wait(.2, sec);
    }
    while(inert.rotation(deg) < turney){
        leftMotor.spin(forward, 100, pct);
        rightMotor.spin(reverse, 100, pct);
        wait(.2, sec);
    }
    leftMotor.stop();
    rightMotor.stop();
}

void turnLeftBangBang(double turney){
    inert.resetRotation();
    while(-inert.rotation(deg) < turney * .8){
        leftMotor.spin(reverse, 100, pct);
        rightMotor.spin(forward, 100, pct);
        wait(.2, sec);
    }
    while(inert.rotation(deg) < turney){
        leftMotor.spin(reverse, 100, pct);
        rightMotor.spin(forward, 100, pct);
        wait(.2, sec);
    }
    leftMotor.stop();
    rightMotor.stop();
}

// Proportional Motion
void driveForwardProp(double distance){
    leftMotor.resetPosition();
    while(leftMotor.position(deg) < distance){
        int speed = distance - leftMotor.position(deg);
        leftMotor.spin(forward, speed, pct);
        rightMotor.spin(forward, speed, pct);
        wait(.2, sec);
    }
    leftMotor.stop();
    rightMotor.stop();
}

void driveReverseProp(double distance){
    leftMotor.resetPosition();
    while(-leftMotor.position(deg) < distance){
        int speed = distance + leftMotor.position(deg);
        leftMotor.spin(forward, speed, pct);
        rightMotor.spin(forward, speed, pct);
        wait(.2, sec);
    }
    leftMotor.stop();
    rightMotor.stop();
}

void turnRightProp(double turney){
   inert.resetRotation();
   while(inert.rotation(deg) < turney){
        int speed = turney - inert.rotation(deg) + 1; //sometimes need +1 in low power VIQ robots
        leftMotor.spin(forward, speed, pct);
        rightMotor.spin(forward, -speed, pct);
        wait(.2, sec);
    }
   leftMotor.stop();
   rightMotor.stop();
}

void turnLeftProp(double turney){
   inert.resetRotation();
   while(-inert.rotation(deg) < turney){
        int speed = turney + inert.rotation(deg) + 1; //sometimes need +1 in low power VIQ robots
        leftMotor.spin(forward, -speed, pct);
        rightMotor.spin(forward, speed, pct);
        wait(.2, sec);
    }
   leftMotor.stop();
   rightMotor.stop();
}

// Porportional with Ramp Up
void driveForwardPropWithRampUp(int distance){
  leftMotor.resetPosition();
  while(leftMotor.position(degrees) < distance){
    int speed = 0;
    if (leftMotor.position(degrees) < 100) {              //what is the issue when need to move less than 100?
      speed = leftMotor.position(degrees) + 1;
    } else {
      speed = distance - leftMotor.position(degrees);
    }
    leftMotor.spin(forward, speed, pct);
    rightMotor.spin(forward, speed, pct);
  }
  leftMotor.stop();
  rightMotor.stop();
}

// Controller Functions - run as threads
void tankDrive(){
  while(true){
    leftMotor.spin(forward,controller1.AxisA.position(),percent);
    rightMotor.spin(forward,controller1.AxisD.position(),percent);
    wait(20,msec);
  }
}

void splitDrive() {
  while(true){
    leftMotor.spin(forward,controller1.AxisA.position() + controller1.AxisC.position() * .5, pct);
    rightMotor.spin(forward,controller1.AxisA.position() - controller1.AxisC.position() * .5, pct);
    wait(20,msec);
  }
}

int splitDriveDeadZones() {
    while(true){
        int axisAPosition = controller1.AxisA.position();
        if (fabs(axisAPosition) < 5) axisAPosition = 0 ;      
        int axisBPosition = controller1.AxisB.position();
        if (fabs(axisBPosition) < 5) axisBPosition = 0 ;
        int leftMotorPower = axisAPosition + axisBPosition * .5;
        int rightMotorPower = axisAPosition - axisBPosition* .5;
        leftMotor.spin(forward, leftMotorPower, percent);
        rightMotor.spin(forward, rightMotorPower, percent);
    }    
}

void arcadeDrive() {
    while(true) {
        leftMotor.spin(forward, controller1.AxisA.position() + controller1.AxisB.position(), pct);
        rightMotor.spin(forward, controller1.AxisA.position() - controller1.AxisB.position(), pct);
        wait(10,msec);
    }   
}

void armControl(){
    while(true){
        if(controller1.ButtonRUp.pressing()) {   // Arm Up Pressed
            rightArm.spin(forward,50,pct);
            leftArm.spin(forward,50,pct);
        } else if(controller1.ButtonRDown.pressing()) {   // Arm Down Pressed
            rightArm.spin(reverse,50,pct);
            leftArm.spin(reverse,50,pct);
        } else {
            leftArm.stop(hold);
            rightArm.stop(hold);
        }
    }    
}

//Main Function
int main() {
    //Sensor set up - calibrate gyro or intertial
    inert.calibrate(calNormal);
    wait(3, sec);

    //Sensor set up - light up the sensor and let it settle
    color1.setLight(100, pct);
	wait(.25, sec);

    //Start debugging function
    thread t(brainDisplay);

    //Put code here

}