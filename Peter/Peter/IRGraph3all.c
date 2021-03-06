#pragma config(Sensor, S2,     light,           sensorLightInactive)
#pragma config(Sensor, S3,     sonar,          sensorSONAR)
#pragma config(Sensor, S4,     IRsense,          sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#include "drivers/LEGOUS-driver.h"
#include "I:\student\R_Robotics\12-13\drivers\HTIRS2-driver.h"

int acS1,acS2,acS3,acS4,acS5;
int dcS1,dcS2,dcS3,dcS4,dcS5;

int n = 1;
int SonarValue;
int IRValue1;
int IRValue2;
int IRValue3;
int IRValue4;
int IRValue5;


string acdc;

float oldy;

float oldy1,oldy2,oldy3,oldy4,oldy5;

/*int round(float f)
{
  if(f>0) return (int)(f + 0.5);
  else    return (int)(f - 0.5);
} */

int GetStrongestSensor()
{
  int sensor;
  if(nNxtButtonPressed == kEnterButton)
  {
  HTIRS2readAllDCStrength(IRsense, acS1, acS2, acS3, acS4, acS5);
  }
  else
  {
  HTIRS2readAllACStrength(IRsense, acS1, acS2, acS3, acS4, acS5);
  }
  if(acS1>acS2 && acS1>acS3 && acS1>acS4 && acS1>acS5)
    sensor=1;
  if(acS2>acS1 && acS2>acS3 && acS2>acS4 && acS2>acS5)
    sensor=2;
  if(acS3>acS1 && acS3>acS2 && acS3>acS4 && acS3>acS5)
    sensor=3;
  if(acS4>acS1 && acS2>acS2 && acS2>acS3 && acS2>acS5)
    sensor=4;
  if(acS5>acS1 && acS2>acS2 && acS2>acS3 && acS2>acS4)
    sensor=5;
  return sensor;
}

	//if(abs(acS1-acS2)<20)
	//{
//	  sensor = acS1
	//}

int GetSensorStrength(int Sensor)
{
  if(nNxtButtonPressed == kEnterButton)
  {
  HTIRS2readAllDCStrength(IRsense, acS1, acS2, acS3, acS4, acS5);
  acdc="(DC)";
  }
  else
  {
  HTIRS2readAllACStrength(IRsense, acS1, acS2, acS3, acS4, acS5);
  acdc="(AC)";
  }
  //HTIRS2readAllDCStrength(HTIRS2, acS1, acS2, acS3, acS4, acS5);
  int value;
  switch (Sensor)
    {
    case 1: value = acS1;
      break;

    case 2: value = (acS1 + acS2) / 2;
      break;

    case 3: value = acS2;
      break;

    case 4: value = (acS2 + acS3) / 2;
      break;

    case 5: value = acS3;
      break;

    case 6: value = (acS3 + acS4) / 2;
      break;

    case 7: value = acS4;
      break;

    case 8: value = (acS4 + acS5) / 2;
      break;

    case 9: value = acS5;
      break;

    case -1: return -1;
      break;
    }
  return value;
}

/*task GetIRSensorsStrength()
{
 while(true)
   {
     HTIRS2readAllACStrength(IRsense, acS1, acS2, acS3, acS4, acS5);
     sensorIR = HTIRS2readACDir(IRsense);
    }
}*/


int pos(int i)
{
  int pos = i*(100/5)
  if(i<=5)
  {
    return pos;
  }
  else
  {
    return -1;
  }
}


task main()
{
  ClearTimer(T1);
  while(true)
  {

    /*if(n>100)
    {
      n=1;
      eraseDisplay();
    }*/

    //SonarValue=SensorValue(sonar);
    //IRValue = GetSensorStrength(GetStrongestSensor());
    IRValue1 = GetSensorStrength(1);
    IRValue2 = GetSensorStrength(2);
    IRValue3 = GetSensorStrength(3);
    IRValue4 = GetSensorStrength(4);
    IRValue5 = GetSensorStrength(5);

    //if(nNxtButtonPressed == kEnterButton)
      //acdc="(DC)";
   // else
      //acdc="(AC)";
    nxtDisplayTextLine(1, "Infrared %s: %d %d %d %d %d",acdc, IRValue1, IRValue2, IRValue3, IRValue4, IRValue5);
    float y1 = 64.00000*(IRValue1/255.00);
    float y2 = 64.00000*(IRValue2/255.00);
    float y3 = 64.00000*(IRValue3/255.00);
    float y4 = 64.00000*(IRValue4/255.00);
    float y5 = 64.00000*(IRValue5/255.00);
    //nxtSetPixel(n,y);

    nxtFillRect(0,0,20,y1);
    nxtFillRect(20,0,40,y2);
    nxtFillRect(40,0,60,y3);
    nxtFillRect(60,0,80,y4);
    nxtFillRect(80,0,100,y5);

    /*if(time100[T1]==1)
    {
      ClearTimer(T1);
      nxtDrawLine(n,oldy,n,y);
      n++;
    }*/

    nxtDisplayTextLine(2, "Light: %d", SensorValue(light));
    /*if(oldy != y)
    {
    n++;
    oldy=y;
    }*/

  }
}
