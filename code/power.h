																///////////////////////////////////////
																///// 				 Library 						/////
																///// to controlling TETRIX power /////
																/////         version 1.4					/////
																/////				from 04.03.2015       /////
																/////															/////
																/////    			created by					/////
																/////				KRYLOV GEORGII				/////
																/////															/////
																/////				 for FTC Team					/////
																/////					PML30-phi 					/////
																///////////////////////////////////////

#pragma once

//#include "RobotClintrinsics.c" //-> to use "hogCPU()" and "releaseCPU()"

#ifndef resetPowerMotor
	#define resetPowerMotor 0
#endif

int OFF_POSITION = 0;
const float KOEF_NEUTRAL_POZITION = 0.4;
bool isPowerOff = true, isResetPowerInicializate = false;
const ubyte faultStopMotor = 1;
const ubyte waitTime = 60, TernSpeed = 50;

bool inicializate_resetPower(const bool requirement = false){
	if (!isResetPowerInicializate || requirement){
		int oldEncoder;

		// start tern motor to ON position calibrate
		motor[resetPowerMotor] = 0;
		wait10Msec(2);
		nMotorEncoder[resetPowerMotor] = 0;
		oldEncoder = nMotorEncoder[resetPowerMotor];
		hogCPU();
		wait10Msec(2);

		motor[resetPowerMotor] = -TernSpeed;

		do{
			oldEncoder = nMotorEncoder[resetPowerMotor];
			wait10Msec(10);
		}while(abs(nMotorEncoder[resetPowerMotor] - oldEncoder) > faultStopMotor);

		wait10Msec(5);
		motor[resetPowerMotor] = 0;
		isPowerOff = false;
		wait10Msec(5);
		nMotorEncoder[resetPowerMotor] = 0;
		// finish tern motor to ON position calibrate
		PlaySound(soundBlip);
		// start tern motor to OFF position calibrate
		motor[resetPowerMotor] = TernSpeed;

		do{
			oldEncoder = nMotorEncoder[resetPowerMotor];
			wait10Msec(10);
		}	while(abs(nMotorEncoder[resetPowerMotor] - oldEncoder) > faultStopMotor);

		wait10Msec(5);
		motor[resetPowerMotor] = 0;
		isPowerOff = true;
		wait10Msec(5);

		OFF_POSITION = nMotorEncoder[resetPowerMotor];
		PlaySound(soundBlip);
		wait10Msec(5);
		// finish tern motor to OFF position calibrate

		// start rotate motor to neutral position
		motor[resetPowerMotor] = -TernSpeed;

		while (abs(nMotorEncoder[resetPowerMotor]) > OFF_POSITION * (1 - KOEF_NEUTRAL_POZITION));
		motor[resetPowerMotor] = 0;
		releaseCPU();
	  PlaySound(soundDownwardTones);
		wait10Msec(5);
		// finish rotate motor to neutral position

		isResetPowerInicializate = true;
		return true;
	}else{
		return false;
	}
}

bool OFF_power(const bool requirement = false){
	if (!isPowerOff || requirement){
		int oldEncoder;

		//start off power
		hogCPU();
		motor[resetPowerMotor] = TernSpeed;

		do{
			oldEncoder = nMotorEncoder[resetPowerMotor];
			wait1Msec(waitTime);
		}while(abs(nMotorEncoder[resetPowerMotor] - oldEncoder) > faultStopMotor);

		wait1Msec(waitTime);
		motor[resetPowerMotor] = 0;
		wait1Msec(waitTime);
		isPowerOff = true;
		//finish off power

		// start rotate motor to neutral position
		motor[resetPowerMotor] = -TernSpeed;
		while (nMotorEncoder[resetPowerMotor] > OFF_POSITION * (1 - KOEF_NEUTRAL_POZITION));

		motor[resetPowerMotor] = 0;
		releaseCPU();
		PlaySound(soundLowBuzz);
		wait1Msec(waitTime);
		// finish rotate motor to neutral position

		return true;
	}else{
		return false;
	}
}

bool ON_power(const bool requirement = false){
	if (isPowerOff || requirement){
		int oldEncoder;

		//start on power
		hogCPU();
		motor[resetPowerMotor] = -TernSpeed;
		wait1Msec(waitTime);

		do{
			oldEncoder = nMotorEncoder[resetPowerMotor];
			wait1Msec(waitTime);
		}while(abs(nMotorEncoder[resetPowerMotor] - oldEncoder) > faultStopMotor);

		wait1Msec(waitTime);
		motor[resetPowerMotor] = 0;
		PlaySound(soundDownwardTones);
		wait1Msec(waitTime);
		isPowerOff = false;
		//finish on power

		// start rotate motor to neutral position
		motor[resetPowerMotor] = TernSpeed;
		while (nMotorEncoder[resetPowerMotor] < OFF_POSITION * KOEF_NEUTRAL_POZITION);

		motor[resetPowerMotor] = 0;
		releaseCPU();
		wait1Msec(waitTime);
		// finish rotate motor to neutral position

		return true;
	}else{
		return false;
	}
}
