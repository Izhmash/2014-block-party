#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     backLeftMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     frontLeftMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     backRightMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     frontRightMotor, tmotorTetrix, openLoop, reversed)

#include "joystickdriver.c"

task main()
{
	getJoystickSettings(joystick);
	while(true)
		motor[frontRightMotor] = joystick.joy1_y1;

}
