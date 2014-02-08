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

#include "BotSystems.h"
#include "PolarJoystick.h"

#define STOP 0
#define IN 1
#define OUT -1

float Y1, Y2, X1, X2;
//float factor = .63;
//float factor = .1969;
//float factor = .7874;  //limits to 100
//float factor = .007874;  //limits to 1
byte mag = STOP;

task main()
{
	initSystems();

	while(true)
	{
		getJoystickSettings(joystick);  //Try inside and outside the loop

		//-------------------------------------Holonomic------------------------------------------

		Y1 = (float)joystick.joy1_y1 / 1.28;
		Y2 = (float)joystick.joy1_y2 / 1.28;
		X1 = (float)joystick.joy1_x1 / 1.28;
		X2 = (float)joystick.joy1_x2 / 1.28;

		/*Y1 = joystick.joy1_y1 * -factor;
		Y2 = joystick.joy1_y2 * -factor;
		X1 = joystick.joy1_x1 * factor;
		X2 = joystick.joy1_x2 * factor;*/

		//-------------------Polar Joystick Testing---------------------------//
		eraseDisplay();
		nxtDisplayCenteredTextLine(1, "mag: " "%f", getMagnitude(X1,Y1));
		nxtDisplayCenteredTextLine(3, "rads: " "%f", getDirRads(X1,Y1));
		nxtDisplayCenteredTextLine(5, "degrees: " "%f", getDirDegrees(X1,Y1));

		/*
		 *  Try wheel speed formula c = s*cos((PI/4)-theta)
		 *  s = max motor speed
		 */

		motor[frontRightMotor] = X1 - Y2 + X2;
		motor[backRightMotor] =  X1 - Y2 - X2;
		motor[frontLeftMotor] = X1 + Y2 + X2;
		motor[backLeftMotor] =  X1 + Y2 - X2;

		/*motor[frontRightMotor] = getMagnitude(X1, Y1)*cos((PI/4) - getDirRads(X1, Y1));
		motor[backRightMotor] =  getMagnitude(X1, Y1)*cos((PI/4) - getDirRads(X1, Y1));
		motor[frontLeftMotor] = getMagnitude(X1, Y1)*cos((PI/4) - getDirRads(X1, Y1));
		motor[backLeftMotor] =  getMagnitude(X1, Y1)*cos((PI/4) - getDirRads(X1, Y1));*/

		//--------------------------------------Flag-----------------------------------------------

		if(joy1Btn(8))
			motor[flagMotor] = 100;
		else if(joy1Btn(7))
			motor[flagMotor] = -100;
		else motor[flagMotor] = 0;

		//---------------------------------------M4---------------------------------------------------

		if(joy2Btn(3))														//Button B pressed => FULL POWER!!!/3000
		{
			pullBack(3000);											//3000 = Pull back distance
		}
		if(joy2Btn(4))														//Button Y pressed => medium high power/2300
		{
			pullBack(2300);
		}
		if(joy2Btn(1))														//Button x pressed => medium low power/1500
		{
			pullBack(1500);
		}
		if(joy2Btn(2))														//Button a pressed => low power/1000
		{
			pullBack(1000);
		}
		//}
		if(joy2Btn(8))															//Fires the servo hit - return when right trigger button pressed again
		{
			fire();
		}
		//----------------------------------------Boom----------------------------------------------

		motor[LBoomMotor] = joystick.joy2_y1 / 1.28;
		motor[RBoomMotor] = joystick.joy2_y1 / 1.28;

		//---------------------------------------Magazine-------------------------------------------

		if(joy1Btn(6) || joy2Btn(6))
			mag = IN;
		if(joy1Btn(5) || joy2Btn(5))
			mag = OUT;
		if(joy1Btn(5) && joy1Btn(6) || joy2Btn(5) && joy2Btn(6))
			mag = STOP;

		if(mag == IN)
		{
			motor[magLeft] = 100;
			motor[magRight] = 100;
		}
		else if(mag == OUT)
		{
			motor[magLeft] = -100;
			motor[magRight] = -100;
		}
		else
		{
			motor[magLeft] = 0;
			motor[magRight] = 0;
		}
		//---------------------------------------Extras---------------------------------------------

		if(joy1Btn(10) || joy2Btn(10)) stopAllMotors();
		//PlayTone((rand() % (700-500)) + 500, 5);     //rand() % (max-min)) + min;

		wait1Msec(100);
	}
}
