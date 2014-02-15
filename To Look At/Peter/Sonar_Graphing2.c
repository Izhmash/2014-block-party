#pragma config(Sensor, S2,     light,           sensorLightInactive)
#pragma config(Sensor, S3,     sonar,          sensorSONAR)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#include "drivers/LEGOUS-driver.h"

int n = 1;
int SonarValue;
float oldy;
int round(float f)
{
  if(f>0) return (int)(f + 0.5);
  else    return (int)(f - 0.5);
}

task main()
{
  ClearTimer(T1);
  while(true)
  {
    if(n>100)
    {
      n=1;
      //eraseDisplay();
    }
    SonarValue=SensorValue(sonar);
    nxtDisplayTextLine(1, "Sonar: %d", SonarValue);
    float y = 64.00000*(SonarValue/255.00);
    //nxtSetPixel(n,y);
    if(time100[T1]==1)
    {
      ClearTimer(T1);
      //nxtEraseLine(n,0,n,64);
      nxtEraseRect(n,0,n+8,64);
      nxtInvertLine(n+1,0,n+1,64);
      nxtDrawLine(n,oldy,n,y);
      nxtDrawCircle(n,y,5);
      n++;
    }
    nxtDisplayTextLine(2, "Light: %d", SensorValue(light));
    /*if(oldy != y)
    {
    n++;
    oldy=y;
    }*/
  }
}