#include "JoystickDriver.c"

task main()
{

  while(true)
  {
    GetJoystickSettings()
    if(joy1Btn(1))
      motor[lift]++
    if(joy1Btn(0))
      motor[lift]--
  }
}
