#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
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
#pragma config(Servo,  srvo_S2_C1_4,    servoMvClaws2,        tServoStandard)
#pragma config(Servo,  srvo_S2_C1_5,    servoMvClaws3,        tServoStandard)
#pragma config(Servo,  srvo_S2_C1_6,    servoBall2,           tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard             !!*//
#include "JoystickDriver.c"
int a = -50;

void R(int nr) // control of right wheel pair
{
	motor[FR] = nr;
	motor[BR] = nr;
}

void L(int nl)// control of left wheel pair
{
	motor[FL] = nl;
	motor[BL] = nl;
}

void Servosetup() // initialization of servos and motors
{
	motor[FR] = 0;
	motor[BR] = 0;
	motor[FL] = 0;
	motor[BL] = 0;
	motor[UR] = 0;
  motor[UL] = 0;
  motor[URT] = 0;
  motor[ULT] = 0;
	servo[servoBall] = 230;
	servo[servoBall2] = 0;
	servo[servoTube] = 70;
	servo[servoMvClaws] = 70;
	servo[servoMvClaws2] = 140;
	servo[servoMvClaws3] = 263 - ServoValue[servoMvClaws];
	nMotorEncoder[FR] = 0;
	nMotorEncoder[FL] = 0;
	nMotorEncoder[BR] = 0;
	nMotorEncoder[BL] = 0;
	nMotorEncoder[UR] = 0;
	motor[motorB]= 0;
	motor[motorC] = 0;
	nMotorEncoder[UL] = 0;
	nMotorEncoder[URT] = 0;
	nMotorEncoder[ULT] = 0;
}

task Ball() // control of gripper for balls
{
	float b = 50;

	while (true)
	{
   if(joy2Btn(2) > 0)
   {
     a = -a;
     motor[motorB] = 50 + a;
		 motor[motorC] = 50 + a;
     while (joy2Btn(2) > 0)
     	 wait1Msec(1);
   }
   if (joy2Btn(4) > 0)
   {
     b = -b;
     motor[motorB] = -50 + b;
		 motor[motorC] = -50 + b;
     while (joy2Btn(4) > 0)
     	 wait1Msec(1);
   }
 }
}

task Ball_side()
{
	servo[servoBall2] = 170;
	servo[servoBall] = 230 - servo[servoBall2];
	while (true)
	{
		servo[servoBall] = 230 - servo[servoBall2];
		if (joy1Btn(1) > 0)
		{
			servo[servoBall2] = 60;
			servo[servoBall] = 230 - servo[servoBall2];
	  }
		if (joy1Btn(3) > 0)
		{
			servo[servoBall2] = 170;
			servo[servoBall] = 230 - servo[servoBall2];
	  }
	}
}

task MvClaw() // control of mechanism that capture rolling goals
{
  int clse = 17,opn = 50;
  //servo[servoMvClaws] = opn;
  while (true)
  {
  	servo[servoMvClaws3] = 260 - ServoValue[servoMvClaws];
  	if(joy1Btn(5) == 1)
  	{
			servo[servoMvClaws] = clse;
		}
    if(joy1Btn(7) == 1)
    {
  		servo[servoMvClaws] = opn;
  	}
  }
}

task MvClaw2() // control of additional gripper for rolling goals
{
  int clse = 0,opn = 140;
  //servo[servoMvClaws] = opn;
  while (true)
  {
  	if(joy1Btn(4) == 1)
		servo[servoMvClaws2] = clse;
    if(joy1Btn(6) == 1)
  	servo[servoMvClaws2] = opn;
  }
}

task tube () // control of mechanism overturning the bucket
{
	const unsigned char  r2 = 245, start_val = 80;
	int state = 23;

	while(true)
	{
  	if(joystick.joy1_y1 < -90)
  	{
	  	servo[servoTube] = start_val;
	  }
    if(joystick.joy1_y1 > 90)
    {
  	  servo[servoTube] = r2;
  	}
  	if (joy1Btn(2) > 0)
  	{
  		state = -state;
  		servo[servoTube] = 222 + state;
  		while (joy1Btn(2) > 0)
  			wait1Msec(1);
  	}
  }
}

task elevator() // control of lift
{
	while(true)
	{
	/*if(nMotorEncoder[UL] < 0)
	{
		motor[UR] = -100;
    motor[UL] = 100;
	}
	else*/
	//{
		/*if(nMotorEncoder[UL] > 25000)
	  {
	  	motor[UR] = 100;
      motor[UL] = -100;
	  }
	  else*/
	 // {
	    if(abs(joystick.joy1_y2) > 90 )
	    {
	    	a = -50;
     		motor[motorB] = 50 + a;
		 		motor[motorC] = 50 + a;
	    	motor[UR] = 100 * joystick.joy1_y2 / abs(joystick.joy1_y2);
        motor[UL] = -100 * joystick.joy1_y2 / abs(joystick.joy1_y2);
        motor[URT] = 100 * joystick.joy1_y2 / abs(joystick.joy1_y2);
        motor[ULT] = -100 * joystick.joy1_y2 / abs(joystick.joy1_y2);
	    }
	    else
	    {
    		motor[UR] = 0;
        motor[UL] = 0;
        motor[URT] = 0;
        motor[ULT] = 0;
    	}
    //}
  }
}


task  motion() // control of robot's moving
{
  float k = 0;
while(true)
{
		 motor[FR] = 0;
		 motor[BR] = 0;
		 motor[FL] = 0;
		 motor[BL] = 0;
    /*while(abs(joystick.joy2_y1) + abs(joystick.joy2_x1) > 10)
	  {
	    motor[FR] = (-joystick.joy2_y1 + joystick.joy2_x1) * 100 / 128;
      motor[BR] = (-joystick.joy2_y1 + joystick.joy2_x1) * 100 / 128;
      motor[FL] = (-joystick.joy2_y1 - joystick.joy2_x1) * 100 / 128;
      motor[BL] = (-joystick.joy2_y1 - joystick.joy2_x1) * 100 / 128;
    }
   /* else
    {
    	if(abs(joystick.joy2_y1) + abs(joystick.joy2_x1) > 10 && joy2Btn(10) == 1)
      {
      	motor[BR] = (-joystick.joy2_y1 + joystick.joy2_x1) * 100 / 128 * k;
        motor[BL] = (-joystick.joy2_y1 - joystick.joy2_x1) * 100 / 128 * k;
        motor[FR] = 0;
        motor[FL] = 0;
      }*/
  if((joy2Btn(6) == 1) || (joy2Btn(7) == 1))
  {
  	k = 1;
  }
  else
  {
  	k = 0;
  }

  while(joystick.joy2_TopHat == 0)
	{
    R(-100 + 80 * k);
    L(-100 + 80 * k);
  }
  while(joystick.joy2_TopHat == 1)
	{
    R(0);
    L(-100);
  }
  while(joystick.joy2_TopHat == 2)
	{
    R(100 - 30 * k);
    L(-100 + 30 * k);
  }
  while(joystick.joy2_TopHat == 3)
	{
	  R(100);
    L(0);
  }
  while(joystick.joy2_TopHat == 4)
	{
    R(100 - 80 * k);
    L(100 - 80 * k);
  }
  while(joystick.joy2_TopHat == 5)
	{
	  R(0);
    L(100);
  }
  while(joystick.joy2_TopHat == 6)
	{
    R(-100 + 30 * k);
    L(100 - 30 * k);
  }
  while(joystick.joy2_TopHat == 7)
	{
	  R(-100);
    L(0);
  }
  while(joystick.joy2_TopHat == -1)
	{
    R(0);
    L(0);
  }

}
}

task main()
{
  Servosetup();
  waitForStart();
  StartTask(MvClaw);
  StartTask(MvClaw2);
 // StartTask(Claw);
	StartTask(Ball);
	StartTask(Ball_side);
	StartTask(tube);
	StartTask(motion);

	StartTask(elevator);
	while(true)
	{
		getJoystickSettings(joystick);
  }
}
