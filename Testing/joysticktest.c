#include "joystickdriver.c"

float factor = .1969;

task main()
{
	getJoystickSettings(joystick);
	while(true)
	{
		//motor[LBoomMotor] = joystick.joy1_y1 / factor;
		writeDebugStreamLine("%f", joystick.joy1_y1 * factor);
		//motor[RBoomMotor] = joystick.joy1_y2 / factor;
		writeDebugStreamLine("%f", joystick.joy1_y2 * factor);
	}

}
