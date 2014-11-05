#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S2,     touchB,         sensorTouch)
#pragma config(Sensor, S3,     touchF,         sensorTouch)
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

task stage()
{
	while(SensorValue[touchB] < 1)
	{}
  //open central stage cracker
}

task tube ()
{
  while(SensorValue[touchB] < 1)
  {}
  servo[servoTube] = 255;
}

task elevator()
{
	while(nMotorEncoder[UL] < 14000)
	{
    motor[UR] = -100;
    motor[UL] = 100;
  }
}

task motion()
{
	while(SensorValue[touchB] < 1)
	{
	  motor[FR] = 100;
    motor[BR] = 100;
    motor[FL] = 100;
    motor[BL] = 100;
  }

  while(nMotorEncoder[FR] < 1000)
  {
    motor[FR] = 100;
    motor[BR] = 100;
    motor[FL] = -100;
    motor[BL] = -100;
  }

  while(SensorValue[touchF] < 1)
	{
	  motor[FR] = -100;
    motor[BR] = -100;
    motor[FL] = -100;
    motor[BL] = -100;
  }
}

task main()
{
	ServoSetup();

  //waitForStart();

	StartTask(stage);
	StartTask(tube);
	StartTask(motion);
	StartTask(elevator);

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
