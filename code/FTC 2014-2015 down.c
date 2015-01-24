#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S3,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     Sonar,          sensorSONAR)
#pragma config(Motor,  mtr_S1_C1_1,     FR,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     BR,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     FL,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     BL,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     UL,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     ULT,           tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     UR,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     URT,           tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S2_C1_1,    servoBall,            tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C1_2,    servoTube,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servoMvClaws,         tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

//int a = 64;

void Servosetup()
{
	servo[servoBall] = 127;
	servo[servoTube] = 70;
	servo[servoMvClaws] = 235;
	nMotorEncoder[FR] = 0;
	nMotorEncoder[FL] = 0;
	nMotorEncoder[BR] = 0;
	nMotorEncoder[BL] = 0;
	nMotorEncoder[UR] = 0;
	nMotorEncoder[UL] = 0;
	motor[FR] = 0;
  motor[BR] = 0;
  motor[FL] = 0;
  motor[BL] = 0;
  motor[UR] = 0;
  motor[UL] = 0;
  motor[URT] = 0;
  motor[ULT] = 0;

}

void moving(int pow, int IR)
{
	while (SensorValue[IR] != IR && SensorValue[IR] != 0)
	{
   	motor[FR] = pow;
    motor[BR] = pow;
    motor[FL] = pow;
    motor[BL] = pow;
    nxtDisplayBigTextLine(1, "%i", SensorValue[IR]);
  }
}

/*void rotate(int l_turn)
{
	nMotorEncoder[BR] = 0;
	while((nMotorEncoder[BL] / 1024) * 3.14159265 * 10 < l_turn)
	{
	  motor[FR] = -100;
    motor[BR] = -100;
    motor[FL] = 100;
    motor[BL] = 100;
  }

  motor[FR] = 0;
  motor[BR] = 0;
  motor[FL] = 0;
  motor[BL] = 0;
}*/

void turn_left(int l_turn)
{
	nMotorEncoder[BR] = 0;
	while((nMotorEncoder[BR] / 1024) * 3.14159265 * 10 < l_turn)
	{
	  motor[FL] = 100;
    motor[BL] = 100;
  }

  motor[FR] = 0;
  motor[BR] = 0;
  motor[FL] = 0;
  motor[BL] = 0;
}

void turn_right(int l_turn)
{
	nMotorEncoder[BL] = 0;
	while((nMotorEncoder[BL] / 1024) * 3.14159265 * 10 < l_turn)
	{
	  motor[FL] = -100;
    motor[BL] = -100;
  }

  motor[FR] = 0;
  motor[BR] = 0;
  motor[FL] = 0;
  motor[BL] = 0;
}

void motion_IRC()
{
 /* while (SensorValue[Sonar] > 16)
    moving(50);*/
  motor[FR] = 0;
  motor[BR] = 0;
  motor[FL] = 0;
  motor[BL] = 0;

}

void motion_IRL()
{
	int IR;
  turn_left(12);
  IR = SensorValue[IR];
  nxtDisplayBigTextLine(1, "%i", IR);// or 1.2 * 1024
  moving(20, 8);
  motor[FR] = -100;
  motor[BR] = -100;
  motor[FL] = -100;
  motor[BL] = -100;
  while (SensorValue[IR] != 5 && SensorValue[IR] != 0)
    turn_right(1);
  motion_IRC();
  motor[FR] = 0;
  motor[BR] = 0;
  motor[FL] = 0;
  motor[BL] = 0;
}

void motion_IRR()
{
  turn_right(24);
  nxtDisplayBigTextLine(1, "%i", SensorValue[IR]);// or 1.2 * 1024
  moving(30, 2);
  motor[FR] = -100;
  motor[BR] = -100;
  motor[FL] = -100;
  motor[BL] = -100;
  while (SensorValue[IR] != 5 && SensorValue[IR] != 0)
  	turn_left(1);
  motion_IRC();
  motor[FR] = 0;
  motor[BR] = 0;
  motor[FL] = 0;
  motor[BL] = 0;
}

void elevator()
{
	//int enc = nMotorEncoder[UL];
	nMotorEncoder[UL] = 0;
	motor[UR] = 100;
  motor[UL] = -100;
  motor[URT] = 100;
  motor[ULT] = -100;
  wait1Msec(1000);
  if(-nMotorEncoder[UL] < 10)
  {
    while(true)
    {
  	  motor[UR] = 0;
      motor[UL] = 0;
      motor[URT] = 0;
      motor[ULT] = 0;
    }
  }

 	while(-nMotorEncoder[UL] < 14000)
	{
    motor[UR] = -100;
  	motor[UL] = 100;
    motor[URT] = -100;
    motor[ULT] = 100;
  }

  servo[servoTube] = 245;
  wait1Msec(3500);
  servo[servoTube] = 70;
 	while(-nMotorEncoder[UL] > 0)
	{
    motor[UR] = 100;
  	motor[UL] = -100;
    motor[URT] = 100;
    motor[ULT] = -100;
  }

}

task main()
{
 // waitForStart();

	if (SensorValue[IR] == 4)
		motion_IRL();
	if (SensorValue[IR] == 5)
		motion_IRC();
	if (SensorValue[IR] == 6)
		motion_IRR();
//  elevator();


	while(true)
	{
		motor[FR] = 0;
    motor[BR] = 0;
    motor[FL] = 0;
    motor[BL] = 0;
    motor[UR] = 0;
    motor[UL] = 0;
  }
}
