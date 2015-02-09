#ifndef PID_H_
#define PID_H_
/*
Credit where credit is due:
Dave Hawes -- introducing me to the concept
David cohen-- showing me the real world application
Sue shields-- helping me find the "dependant" form of I, this greatly simplified the process.
*/


//Define parameter
#define Kp 0.1//tuning for p
#define Ki 0.1//tuning for i
#define Kd 0.2//tuning for d
#define Tolerance 5//how close is close enough?
#define dt 0.001 //duration of loop
#define max_out 100 //ouput limits
#define min_out -100//^^^^^^^^^^^^


float PID(float setpoint,float ProcessValue)
{
	static float init_error= 0;
	static float integral=0;
	float error;
	float derivative;
	float PIDoutput;
//Caculate P
		error = setpoint -ProcessValue;
		//stop integration if error too smal
		if(abs(error)> Tolerance)
		{
//Calculate I
		integral =integral+ error*dt;
		}
//Calculate D
		derivative= (error -init_error)/dt;
//COMPUTE PID
		PIDoutput=Kp*error+ Ki*integral+ Kd*derivative;

		//limits the Range of PIDoutput to ensure not out of range
		if(PIDoutput< min_out)
		{
		PIDoutput= min_out;
		}
		else if(PIDoutput> max_out)
		{
		PIDoutput= max_out;
		}
	//Update error, this program has to be run in a loop so that error can be corected over time
	init_error= error;
	return PIDoutput;
}
#endif PID_H_
