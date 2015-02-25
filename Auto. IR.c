#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     IR,         sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     Compass,        sensorI2CHiTechnicCompass)
#pragma config(Sensor, S4,     HTSPB,          sensorI2CCustom9V)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     Right,         tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     Left,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     Intake,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     none,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     Conveyor,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     Lift,          tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C2_1,    Gripper,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    lock,                 tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma DebuggerWindows("debugStream")
#pragma DebuggerWindows("nxtLCDscreen")

#include "drivers/HTSPB-driver.h"
#include "drivers/PID.h"
//#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#define START_RED     "Red"
#define START_BLUE    "Blue"
#define START_FLOOR  "FLOOR"
#define START_RAMP "RAMP"
#define MIN (X, Y) (((X)<(Y) ?(X) : (Y)
#define MAX (A, B) (((A)>(B) ?(X) : (Y)
string startColor;
string startPosition;
int hasbeeninit = 0;
bool SwitchState =false;//initialize switchstate as false
int GoalPosition =0;//must be initialized as zero so it can overide when/if LocateInfaRedBeacon() produces no change

task printf();
void getUserInput();
void initializeRobot();
void Routine1();
void Routine2();
void Routine3();
void RoutineERR();
void locateInfaRedBeacon();
void RunLift(float nStage);
void Drive(int distance, int power);
void Turn(int Angle);// +360 to -360
void BumpConveyor();
void Test();
task main()
{
//	Test();
//	startTask(printf);
		getUserInput();
		initializeRobot();

	if(startPosition == START_RAMP)
	{
  Drive(-105, 40);
	wait10Msec(150);
	servo[Gripper]=0;
	wait10Msec(100);
	servo[lock]=225;
	wait10Msec(200);
	servo[lock]=127;
	wait10Msec(200);
	Turn(32);
	wait10Msec(50);
	Drive(101, 85);
	wait10Msec(50);
	Turn(-90);
	Runlift(1);
	wait10Msec(50);
	BumpConveyor();
	}
	if(startPosition==START_FLOOR)
	{
		Drive(33, 60);
		wait10Msec(80);
		Turn(90);
		wait10Msec(80);
		if(SensorValue(IR)==5)
		{
			Turn(-90);
			wait10Msec(80);
			Drive(-2, 50);
			//wait10Msec(80);
			//RunLift(4);
			//wait10Msec(80);
		 // BumpConveyor();
		 // wait10Msec(80);
		 // RunLift(0);
		  wait10Msec(80);
		  Turn(90);
		  wait10Msec(80);
		  Drive(12,60);
		  wait10Msec(80);
		  Turn(90);
		  wait10Msec(80);
		  Drive(27,100);
		}
		else
		{
			Drive(-27,60);
			wait10Msec(80);
			Turn(45);
			wait10Msec(80);
			if(SensorValue(IR)==5)
			{
				Turn(-90);
				wait10Msec(80);
				Drive(-14,60);
				wait10Msec(80);
				//RunLift(4);
				//wait10Msec(80);
		  //	BumpConveyor();
		  //	wait10Msec(80);
		  //	RunLift(0);
		  //	wait10Msec(80);
		  	Turn(-90);
		  	wait10Msec(80);
		  	Drive(12,60);
		  	wait10Msec(80);
		  	Turn(-90);
		  	wait10Msec(80);
		  	Drive(27,100);
			}

			else
			{
				wait10Msec(80);
				Turn(35);
				wait10Msec(80);
				Drive(-27,60);
				wait10Msec(80);
				Turn(78);
				wait10Msec(80);
				Drive(-3,50);
				wait10Msec(80);
				RunLift(4);
				wait10Msec(80);
				Drive(-4,50);
				wait10Msec(80);
		  	BumpConveyor();
		  	wait10Msec(80);
		  	Drive(4,50);
		  	wait10Msec(80);
		  	RunLift(0);
		  	wait10Msec(80);
		  	Turn(90);
		  	wait10Msec(80);
		  	Drive(12,60);
		  	wait10Msec(80);
		  	Turn(90);
		  	wait10Msec(80);
		  	Drive(20,100);
			}
		}
	}
	//waitForStart();
	//locateInfaRedBeacon();//determins GoalPosition
	//for(int Count=0; Count<3; Count++)
	//{
	//	if(GoalPosition==1){
	//	Routine1();
	//	break;
	//	}
	//	else if(GoalPosition==2){
	//	Routine2();
	//	break;
	//	}
	//	else if(GoalPosition==3){
	//	Routine3();
	//	break;
	//	}
	//	else if(GoalPosition==0){
	//	RoutineERR();
	//	break;
	//	}
	//

	//	Test();
//	waitForStart();
//	locateInfaRedBeacon();//determins GoalPosition

	/*    hows this for instead of your routine stuffs     -David

	int fabulus =0;

	while (int fabulus==0)
  {
   	if(SensorValue[IR]==5)
		{
		Routine1();
		break;
		}
		else
		{
		Drive(5);//change number
		Turn(-45);//change number
		Drive(5);//change number
		}

		if(SensorValue[IR]==5)
		{
		Routine2();
		break;
		}
		else
		{
		Drive(5);//change number
		Turn(-45);//change number
		Drive(5);//change number
		}

	if(SensorValue[IR]==5)
		{
		Routine3();
		break;
		}
		else
		{
		Drive(5);//change number
		Turn(-45);//change number
		Drive(5);//change number
		}
		int fabulus++;

  }

	if(SensorValue[IR]==5)
		{
		RoutineERR();
		break;
		}
	*/




	for(int Count=0; Count<3; Count++)
	{
		if(GoalPosition==1)
		{
		Routine1();
		break;
		}

		else if(GoalPosition==2)
		{
		Routine2();
		break;
		}

		else if(GoalPosition==3)
		{
		Routine3();
		break;
		}

		else if(GoalPosition==0)
		{
		RoutineERR();
		break;
		}
	}
//clearDebugStream();
}

task printf()
{
	while(true)
	{
	clearDebugStream();
	writeDebugStreamLine("startPosition: %s", startPosition);
	writeDebugStreamLine("startColor:    %s", startColor);
	writeDebugStreamLine("GoalPosition: %i", GoalPosition);
	wait10Msec(100);
	clearDebugStream();
	}
}
void initializeRobot()
{
	servo[Gripper]=80;
}
void getUserInput()
{
 disableDiagnosticsDisplay();
  nxtDisplayCenteredTextLine(1, "FLOOR or RAMP?");
  nxtDisplayCenteredTextLine(7, "FLOOR RAMP");
  while(true)
  {
    if(nNxtButtonPressed == 2)
    {
      startPosition = START_FLOOR;
      nxtDisplayCenteredTextLine(1, "FLOOR");
      nxtDisplayCenteredTextLine(7, "");
      break;
    }
    else if(nNxtButtonPressed == 1)
    {
      startPosition = START_RAMP;
      nxtDisplayCenteredTextLine(1, "RAMP");
      nxtDisplayCenteredTextLine(7, "");
      break;
    }
  }
  playSound(soundFastUpwardTones);
  wait10Msec(200);
	nxtDisplayCenteredTextLine(0, "%s", startPosition);
}

void Routine1()
{
//Turn(-90);
//Drive(1.5);
//RunLift(4);
//Drive(-1.5);
//BumpConveyor();
//Drive(1.5);
//RunLift(-4);
//Drive(-1.5);
//Turn(90);
//Drive(12);
//Turn(90);
//Drive(36);
//RunLift(1);
}
void Routine2()
{

}
void Routine3()
{

}
void RoutineERR()
{

}
void locateInfaRedBeacon()
{
//determine start Position(FLOOR = floor, RAMP = ramp)
	//if(startPosition == START_FLOOR)
	//{
	////drive out of start Position and into GoalPosition_1
	//Drive(40);//change number
	//Turn(-90);//change number
	//}
	//else if(startPosition == START_RAMP)
	//{
	////drive out of start Position and into GoalPosition_1
	//Drive(80);
	//Turn(-45);
	//Drive(-50);//change number
	//Turn(-45);//change number
	//Drive(-25);//change number
	//}

//if IR at GoalPosition 1 SET(int GoalPosition =1)and return;
	//if(SensorValue[IR]==5)
	//{
	//GoalPosition=1;
	//return;
	//}
	//RunLift(4);//is this like routine one?  -David

//if IR at GoalPosition 1 SET(int GoalPosition =1)and return;
//else drive out of GoalPosition1 and into GoalPosition_2


//check IR when robot has reached GoalPosition_2
//if IR at GoalPosition 2 SET(int GoalPosition =2)and return;
//else drive out of GoalPosition2 and into GoalPosition_3
//check IR when robot has reached GoalPosition_3
//if IR at GoalPosition 3 SET(int GoalPosition =1)and return;
}

void RunLift(float nStage)
{
	int inputdata = HTSPBreadADC(HTSPB, 0, 10);
	//the first time in a program this is called, initialize the lift
	if(hasbeeninit==0)	//initialize the lift
	{
//initialize the lift
		motor[Lift]=100;
		wait1Msec(500);
		motor[Lift]=0;
		while(true)
		{
			//check switch state
			int inputdata = HTSPBreadADC(HTSPB, 0, 10);//refreshed per cycle.
	    SwitchState = (int)inputdata >512;//boolean algebra.

	    if(inputdata==-1)//this is the fault state for the HTSPB reading analog.
	    {
	    //report error
	    writeDebugStreamLine("S4 Fault");
	    nxtDisplayCenteredBigTextLine(3, "S4 Fault");
	    break;	//exit the function
	    }
	    if(SwitchState==false)//if switch open
	    {
	    	//move down until switch is pressed
	    	motor[Lift]=-20;
	    	writeDebugStreamLine("STATE:%i",SwitchState);
	    }
	    else if(SwitchState==true)// if switch closed
	    	{
	    	motor[Lift]=0;
	    	nMotorEncoder[Lift]=0;
	    	writeDebugStreamLine("STATE:%i",SwitchState);
	    	break;//exit and begin PID control
	    }
	 	}
//confirm initialization
		hasbeeninit= -1;//keeps from initializing more than once
		writeDebugStreamLine("STATE:%i",SwitchState);//reports switch information
		writeDebugStreamLine("initialization complete");
	}
	wait10Msec(100);
//determine target for PID
	float Range=22.5;//mechanical rotations of the motor shaft to extend full length of lift
	float Stages=4;//number of stages
	float ppr= 1120;//pulse per revolution for the andymark motor
	float PhysicalHeight =22;//bottom of manipulator in cm
	float ENCcm =round((Range *ppr)/115); //en per cm
	float nTarget=(nStage/Stages)*(Range *ppr);
	//loop until within tolerance.
	while(abs(nTarget-nMotorEncoder[Lift])>Tolerance+5)//--TEST added 5 becuase Tolerance to low?
	{
		writeDebugStreamLine("Target:%i, status:%i",nTarget, nMotorEncoder[Lift]);
		motor[Lift]=PID(nTarget,nMotorEncoder[Lift]);
	}
	motor[Lift]=0;


	//************************************LOGIC-TEST************************************//
	//int SIM =0;
	//while(abs(nTarget-SIM)>Tolerance)
	//{
	//	writeDebugStreamLine("Target:%i, status:%i",nTarget, SIM);
	//	motor[Lift]=PID(nTarget,SIM);
	//	SIM++;
	//	SIM++;
	//	wait1Msec(2);
	//	clearDebugStream();
	//}
	//motor[Lift]=0;
	//*********************************************************************************//
	return;
}

void Drive(int distance, int power)
{
	int C=2*(PI)*2;
	int Target= (1120/C)*distance;//en/in
	nMotorEncoder[Right]=0;
	if(distance>1)//forwards
	{
		while(nMotorEncoder[Right]<=Target)
		{
		writeDebugStreamLine("Value :%i, Target: %i",nMotorEncoder[Right], Target);
		motor[Right]=power;
		motor[Left]=power;
		}
		motor[Right]=0;
		motor[Left]=0;
	}
	else if(distance<1)//backwards
	{
		while(nMotorEncoder[Right]>=Target)
		{
		writeDebugStreamLine("Value :%i, Target: %i",nMotorEncoder[Right]*-1, Target);
		motor[Right]=-power;
		motor[Left]=-power;
		}
		motor[Right]=0;
		motor[Left]=0;
	}
}
void Turn(int Angle)//clockwise is negitive
{

	float circumfrence = 2*(PI)*2;
	int ppr = 1120;
	int enc_in=ppr/circumfrence;//result
  nMotorEncoder[motorE]=0;
  nMotorEncoder[motorD]=0;
	float WheelbaseRadius = 6.05;



//	writeDebugStreamLine("Target:%i",Target);

  //1/2 rot= 45deg = 1120enc
	if(Angle<0)//negitive angle
	{
		float ArcLength=degreesToRadians(abs(Angle))*WheelbaseRadius;//result
		int Target= -1*round(ArcLength*enc_in);//goal
		writeDebugStreamLine("Target:%i",Target);
		//left
		while(nMotorEncoder[motorE]> Target)
		{
			writeDebugStreamLine("Value :%i, Target: %i",nMotorEncoder[motorE], Target);
			motor[Right]=75;
			motor[Left]=-75;
		}
		motor[Right]=0;
		motor[Left]=0;
	}
	else if(Angle>0)
	{
		float ArcLength=degreesToRadians(abs(Angle))*WheelbaseRadius;//result
		int Target= round(ArcLength*enc_in);//goal
		writeDebugStreamLine("Target:%i",Target);
	//right
		while(nMotorEncoder[motorE]< Target)
		{
		writeDebugStreamLine("Value :%i, Target: %i",nMotorEncoder[motorE], Target);
		motor[Right]=-75;
		motor[Left]=75;
		}
		motor[Right]=0;
		motor[Left]=0;
	}
}
void BumpConveyor()
{
motor[Conveyor]=20;
wait10Msec(200);
motor[Conveyor]=0;
wait10Msec(50);
motor[Conveyor]=30;
wait10Msec(0.75);
motor[Conveyor]=0;
}

void Test()
{
		Drive(60, 60);
	//clearDebugStream();
	////while(true)
	//{
	//	writeDebugStreamLine("IR: %i",SensorValue(IR));
	//}

}
