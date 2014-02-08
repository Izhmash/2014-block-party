// ROBOTC I2C Tutorial Step 7

task main ()
{

	nMaxDataFiles = 100;
	// Arrays to hold I2C message sent to slave and response
	sbyte I2Cmessage[4];
	sbyte I2Creply[1];

	// Configure port S1 to be a low speed I2C sensor.
	SetSensorType(S1, sensorI2CCustom);

	// Set the I2C slave address
	I2Cmessage[1] = 0x02;

	// Set the register we're interested in reading
	I2Cmessage[2] = 0x42;

	// Set the message size
	I2Cmessage[0] = 2;

	// Loop until the batteries run out.
	int n;
	do
	{
		// Send our message to the sensor and wait 20ms
		sendI2CMsg(S1, &I2Cmessage[0], 1);
		wait1Msec(20);

		// Read the slave's response into the array
		// and print it to the screen and wait 100ms
		// before looping around again.
		readI2CReply(S1, &I2Creply[0], 1);
		int temp = I2Creply[0];
		AddToDatalog(0,temp);
		nxtDisplayBigTextLine(3, "%d", I2Creply[0]);
		wait1Msec(100);
		n++;
	}
	while(n < 100);
	SaveNxtDatalog();
}
