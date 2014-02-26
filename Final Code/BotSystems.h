#include "JoystickDriver.c"
#include "hitechnic-eopd.h"
#include "hitechnic-superpro.h"

void pullBack(int distance);
void fire();
void stopAllMotors();
void initSystems();

static bool armed = false;

//Load: Press a button on the right low-to-high(a,x,y,b) then press the right trigger to load to power
//Fire!: Press right trigger again to fire

void pullBack(int distance)
{
	nMotorEncoder[M4Motor] = 0;          			// reset the Motor Encoder of PULLBACK
	while(nMotorEncoder[M4Motor] < distance)  // while the Motor Encoder of Motor B has not yet reached 360 counts:
	{
		motor[M4Motor] = 100;                 //M4Motor at 100 power
	}
	motor[M4Motor] = 0;												// M4Motor is given a power level of 0 (stop)
	armed = true;
}

void fire()																		//Pulses servo to press up cam
{
	servo[camServo1] = 135;  //from 156  //from 125
	servo[camServo2] = 69;  //from 48  //from 79
	wait1Msec(500);
	servo[camServo1] = 56;
	servo[camServo2] = 148;
	armed = false;
}

void initSystems()
{
	servo[camServo1] = 56;  //from 76
	servo[camServo2] = 148;  //from 128
	nMotorEncoder[M4Motor] = 0;
}

void stopAllMotors()
{
	motor[frontLeftMotor] = 0;
	motor[frontRightMotor] = 0;
	motor[backLeftMotor] = 0;
	motor[backRightMotor] = 0;
	motor[flagMotor] = 0;
}
