#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     FR,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     BR,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     FL,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     BL,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     UR,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     UL,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    servoBall,            tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_2,    servoTube,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

int a = 64;
//float  b = time1[T1];

void Servosetup()
{
	//servos to zero positions
}

task Ball()
{
	while (true)
	{
   if(joy1Btn(2) > 0)
   {
     a = -a;
     servo[servoBall] = 191 + a;
     while (joy1Btn(2) > 0)
     	 wait1Msec(1);
   }
  }
}



task tube ()
{
  while (true)
	{
	 int a = ServoValue[servoTube];
   if(joy1Btn(3) > 0)
     servo[servoTube] = 255;
   else
     servo[servoTube] = 127;
  }
}


/*(task tube()
{
  while (true)
	{
	 getJoystickSettings(joystick);
	 int b = 1;
   if(joy1Btn(3) > 0)
     b = -b;
   if(b == -1)
     servo[servoTube] = 255;
   else
     servo[servoTube] = 0;
  }
}*/

task elevator()
{
	/*if(nMotorEncoder[UL] < 0)
	{
		motor[UR] = -100;
    motor[UL] = 100;
	}
	else
	{
		if(nMotorEncoder[UL] > 14000)
	  {
	  	motor[UR] = 100;
      motor[UL] = -100;
	  }
	  else
	  {
	    if(abs(joystick.joy1_y2) > 90)
	    {
	    	motor[UR] = -100 * joystick.joy1_y2 / abs(joystick.joy1_y2);
        motor[UL] = 100 * joystick.joy1_y2 / abs(joystick.joy1_y2);
	    }
	    else
	    {
    		motor[UR] = 0;
        motor[UL] = 0;
    	}
    }
  }
}

task motion()
{
  if(abs(joystick.joy1_y1 + joystick.joy1_x1) > 10 || abs(joystick.joy1_y1 - joystick.joy1_x1) > 10)
	{
	  motor[FR] = (-joystick.joy1_y1 + joystick.joy1_x1) * 100 / 128;
    motor[BR] = (-joystick.joy1_y1 + joystick.joy1_x1) * 100 / 128;
    motor[FL] = (-joystick.joy1_y1 - joystick.joy1_x1) * 100 / 128;
    motor[BL] = (-joystick.joy1_y1 - joystick.joy1_x1) * 100 / 128;
  }
  else
  {
   	motor[FR] = 0;
    motor[BR] = 0;
    motor[FL] = 0;
    motor[BL] = 0;
  }
}

task main()
{
	ServoSetup();

  //waitForStart();

	StartTask(Ball);
	StartTask(tube);
	StartTask(motion);
	StartTask(elevator);
	while(true)
	{
		getJoystickSettings(joystick);
  }
}
