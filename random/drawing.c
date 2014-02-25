#include "JoystickDriver.c"

int x;
int y;

task main()
{
	getJoystickSettings(joystick);
	int min = 1000;
	int max = 6000;
	eraseDisplay();
	disableDiagnosticsDisplay();

	x = 20;
	y = 20;

	while(true)
	{
		getJoystickSettings(joystick);

		y += joystick.joy1_y1 / 20;
		x += joystick.joy1_x1 / 20;

		nxtSetPixel(x, y);

		if(joy1Btn(2))
		{
			y = 20;
			x = 20;
		}

		wait1Msec(50);
	}
}
