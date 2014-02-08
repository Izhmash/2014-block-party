#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S4, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     IRR,            sensorI2CCustom)
#pragma config(Sensor, S3,     IRL,            sensorI2CCustom)
#pragma config(Motor,  motorA,          magLeft,       tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          magRight,      tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     LBoomMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     RBoomMotor, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     M4Motor,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     flagMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     frontRightMotor,    tmotorTetrix, openLoop)  //change back to C1!!!!!!
#pragma config(Motor,  mtr_S1_C4_2,     backRightMotor,    tmotorTetrix, openLoop, reversed)//change back to C1!!!!!!
#pragma config(Motor,  mtr_S1_C2_1,     backLeftMotor, tmotorTetrix, openLoop)   //change back to C4
#pragma config(Motor,  mtr_S1_C2_2,     frontLeftMotor, tmotorTetrix, openLoop)  //change back to C4
#pragma config(Servo,  srvo_S4_C1_1,    camServo1,            tServoStandard)
#pragma config(Servo,  srvo_S4_C1_2,    camServo2,            tServoStandard)
#pragma config(Servo,  srvo_S4_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S4_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S4_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S4_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
//Shoot when the IR beacon reaches a "sweet spot" in front of the bot

#include "..\Driver Suite\drivers\hitechnic-irseeker-v2.h"
//#include "JoystickDriver.c"  //remove?
#include "BotSystems.h"

//void holonomicBeepAtIR();
//void trackIR();
//void stopAllMotors();
void updateSensors();
void moveForward();
void moveOut();
void aimAtIR();
void approachIR(int d);
void turnLeft();
void turnRight();
void strafeLeft();
void strafeRight();

int getAvgDir();
int getAvgStr(int acSXR, int acSXL);
int getAvgLeftStr();
int getAvgRightStr();

int _dirACL;
int _dirACR;
int acS1L, acS2L, acS3L, acS4L, acS5L;
int acS1R, acS2R, acS3R, acS4R, acS5R;
int avgStr,avgLeftStr, avgRightStr, avgDir, avgStr1, avgStr2, avgStr3, avgStr4, avgStr5;

int distance;

tHTIRS2DSPMode _mode = DSP_1200;

task main()
{
	//waitForStart();
	//getJoystickSettings(joystick);
	//eraseDisplay();
	initSystems();
	/*while(true)
	{
		//eraseDisplay();
		updateSensors();
		avgDir = getAvgDir();
		avgStr1 = getAvgStr(acS1R, acS1L);
		avgStr2 = getAvgStr(acS2R, acS2L);
		avgStr3 = getAvgStr(acS3R, acS3L);
		avgStr4 = getAvgStr(acS4R, acS4L);
		avgStr5 = getAvgStr(acS3R, acS5L);
		//nxtDisplayCenteredTextLine(3, "%d", "%d", avgDir, avgStr);
		nxtDisplayCenteredTextLine(3, "%d", avgStr3);
		nxtDisplayCenteredTextLine(4, "%d", avgDir);
		//aimAtIR();
		//moveOut();
	}*/
	//moveOut();
	aimAtIR();
	approachIR(4);
}

/*
Points at the IR crate
*/
void aimAtIR()  //good zone: both dirs 5, both strengths in 3 from 60-90
{
	//-----------------------------Setup-------------------------------------------------
	updateSensors();
	//pullBack(1500);      //load...

	//-----------------------------Moving the Bot--------------------------------------------

	while(true)
	{
		updateSensors();
		if(_dirACL == 5 && _dirACR == 5) /*stopAllMotors();*/ return;
		else if(avgLeftStr < 15 && avgRightStr < 15) turnLeft();
		else if(avgLeftStr > avgRightStr) turnLeft();
		else/*(avgLeftStr < avgRightStr)*/ turnRight();
	}
	//stopAllMotors();
}

/*
Moves foward until d units of IR strength units has been reached (sector 3)
*/
void approachIR(int d)
{
	updateSensors();

	/*int*/ distance = getAvgStr(acS3R, acS3L);
	int temp = distance - d;
	while(distance > temp)
	{
		updateSensors();
		moveForward();
	  nxtDisplayCenteredBigTextLine(3,"%c", 'a');
		distance = getAvgStr(acS3R, acS3L);
	}
	stopAllMotors();
	//PlaySound(soundBeepBeep);
	//wait1Msec(500);
}

void moveOut()
{
	motor[frontLeftMotor] = 100;
	motor[frontRightMotor] = 100;
	motor[backLeftMotor] = -100;
	motor[backRightMotor] = -100;
	wait1Msec(1250);
	stopAllMotors();
}

void moveForward()
{
	motor[frontLeftMotor] = 100;
	motor[frontRightMotor] = -100;
	motor[backLeftMotor] = 100;
	motor[backRightMotor] = -100;
}

void turnRight()
{
	motor[frontLeftMotor] = 20;
	motor[frontRightMotor] = 20;
	motor[backLeftMotor] = 20;
	motor[backRightMotor] = 20;
}

void turnLeft()
{
	motor[frontLeftMotor] = -20;
	motor[frontRightMotor] = -20;
	motor[backLeftMotor] = -20;
	motor[backRightMotor] = -20;
}

void strafeRight()
{
	motor[frontLeftMotor] = -100;
	motor[frontRightMotor] = -100;
	motor[backLeftMotor] = 100;
	motor[backRightMotor] = 100;
}

void strafeLeft()
{
	motor[frontLeftMotor] = 100;
	motor[frontRightMotor] = 100;
	motor[backLeftMotor] = -100;
	motor[backRightMotor] = -100;
}

/*
Gets the average direction from the two IR sensors
*/
int getAvgDir()
{
	return (_dirACL + _dirACR) / 2;
}

/*
Returns average of all strengths
*/
int getAvgStr()
{
	return getAvgLeftStr() + getAvgRightStr();
}

/*
Parameters: (right IR strength direction, left IR strength directoin
Gets the average of two IR strength directions, each from a different IR sensor
*/
int getAvgStr(int acSXR, int acSXL)
{
	return (acSXR + acSXL) / 2;
}

/*
Returns average of all left strength sectors
*/
int getAvgLeftStr()
{
	return (acS1L + acS2L + acS3L + acS4L + acS5L) / 5;
}

/*
Returns average of all right strength sectors
*/
int getAvgRightStr()
{
	return (acS1R + acS2R + acS3R + acS4R + acS5R) / 5;
}

/*
Updates sensor information
*/
void updateSensors()
{
	HTIRS2setDSPMode(IRL, _mode);
	HTIRS2setDSPMode(IRR, _mode);

	_dirACL = HTIRS2readACDir(IRL);
	_dirACR = HTIRS2readACDir(IRR);

	avgStr = getAvgStr();
	avgLeftStr = getAvgLeftStr();
	avgRightStr = getAvgRightStr();

	HTIRS2readAllACStrength(IRL,  acS1L,  acS2L,  acS3L,  acS4L,  acS5L);
	HTIRS2readAllACStrength(IRR,  acS1R,  acS2R,  acS3R,  acS4R,  acS5R);
}
