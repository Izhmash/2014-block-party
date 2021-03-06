 #pragma config(Sensor, S4,     HTIRS2,                  sensorI2CCustom)
#pragma config(Sensor, S2,     IR2,               sensorHiTechnicIRSeeker600)
#pragma config(Sensor, S3,     Sonar,               sensorNone)
#pragma config(Motor,  motorA,          motorL,        tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorC,          motorR,        tmotorNormal, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "rdpartyrobotcdr-v2.2/drivers/HTSMUX-driver.h"
#include "rdpartyrobotcdr-v2.2/drivers/HTIRS2-driver.h"

int _dirDC = 0;
int _dirAC = 0;
int dcS1, dcS2, dcS3, dcS4, dcS5 = 0;
int acS1, acS2, acS3, acS4, acS5 = 0;

//const tMUXSensor HTIRS2 = msensor_S1_1;

task main()
{

//HTIRS2readAllDCStrength(S1,dcS1,dcS2,dcS3,dcS4,dcS5);
  while(true)
  {
    // Read the current non modulated signal direction
    _dirDC = HTIRS2readDCDir(HTIRS2);
    if (_dirDC < 0)
      break; // I2C read error occurred

    // read the current modulated signal direction
    _dirAC = HTIRS2readACDir(HTIRS2);
    if (_dirAC < 0)
      break; // I2C read error occurred

    // Read the individual signal strengths of the internal sensors
    // Do this for both unmodulated (DC) and modulated signals (AC)
    if (!HTIRS2readAllDCStrength(HTIRS2, dcS1, dcS2, dcS3, dcS4, dcS5))
      break; // I2C read error occurred
    if (!HTIRS2readAllACStrength(HTIRS2, acS1, acS2, acS3, acS4, acS5 ))
      break; // I2C read error occurred

      while( SensorValue(HTIRS2) < 5 && SensorValue(HTIRS2) > 0)
      {
        motor[motorR] = 2555;
      }
      while( SensorValue(HTIRS2) > 5)
      {
        motor[motorL] = 2555;
      }
      //if(!SensorValue(HTIRS2))
      while( SensorValue(HTIRS2) == 5)
      {
        motor[motorR] = 2555;
        motor[motorL] = 2555;
        //if(SensorValue(Sonar) < 50)
        //{
        //  PlaySound(soundFastUpwardTones);
        //}
      }

      while( SensorValue(IR2) < 5 && SensorValue(IR2) > 0)
      {
        motor[motorL] = -2555;
      }
      while( SensorValue(IR2) > 5)
      {
        motor[motorR] = -2555;
      }
      //if(!SensorValue(HTIRS2))
      while( SensorValue(IR2) == 5)
      {
        motor[motorR] = -2555;
        motor[motorL] = -2555;
        //if(SensorValue(Sonar) < 50)
        //{
        //  PlaySound(soundFastUpwardTones);
        //}
      }
      motor[motorR] = 0;
      motor[motorL] = 0;
  }
}
