
/*----------------------------------------------------------------------------------------------------*\
|*                                   - My basic movement functions -                                  *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*                                                                                                    *|
|*    This file contains some basic movement functions :)                                     			  *|
|*                                                                                                    *|
|*
\*----------------------------------------------------------------------------------------------------*/
//ummal 27.7 robot um dekk 10.2
//(27.7/10,2)*deg
const float diameter=27.6;
const float diameter_wheel=10.2;
const int threshold = 1500;
const int power=127;

void pause(){
	motor[rightMotor] = 0;
	motor[leftMotor]  = 0;
	wait1Msec(500);
}

void drive(int distance, int power, int resistance, bool direction){
	SensorValue[rightEncoder] = 0;
  SensorValue[leftEncoder] = 0;
	int degrees = (360/32)*(distance-resistance);
	int di = (direction) ? (1) : (-1);
	while(SensorValue[rightEncoder]*di < degrees)
  	{
    	motor[rightMotor] = power*di;
    	motor[leftMotor] = power*di;
  	}
  pause();
}

void turn(int deg,bool direction){
	SensorValue[rightEncoder] = 0;
  SensorValue[leftEncoder] = 0;
  float turn_degrees=(diameter/diameter_wheel)*deg;
	int di = (direction) ? (1) : (-1);
	while(SensorValue[rightEncoder]*di < turn_degrees)
  	{
    	motor[rightMotor] = -60*di;
			motor[leftMotor]  = 60*di;
  	}
  pause();
}
void follow_line(){
	if(SensorValue(lineFollowerRIGHT) > threshold)
    {
      // counter-steer right:
      motor[leftMotor]  = 50;
      motor[rightMotor] = -50;
    }
    // CENTER sensor sees dark:
    if(SensorValue(lineFollowerCENTER) > threshold)
    {
      // go straight
      motor[leftMotor]  = 30;
      motor[rightMotor] = 30;
    }
    // LEFT sensor sees dark:
    if(SensorValue(lineFollowerLEFT) > threshold)
    {
      // counter-steer left:
      motor[leftMotor]  = -50;
      motor[rightMotor] = 50;
  	}
}

void follow_line_dist(int distance, float resistance, bool direction){
	SensorValue[rightEncoder] = 0;
  SensorValue[leftEncoder] = 0;
	float real_dist = (360/32)*(distance-resistance);
	int di = (direction) ? (1) : (-1);
	while((SensorValue[rightEncoder]+SensorValue[leftEncoder]*-1)/2*di < real_dist){
		if(SensorValue(lineFollowerRIGHT) > threshold)
	    {
	      // counter-steer right:
	      motor[leftMotor]  = 50;
	      motor[rightMotor] = -50;
	    }
	    // CENTER sensor sees dark:
	    if(SensorValue(lineFollowerCENTER) > threshold)
	    {
	      // go straight
	      motor[leftMotor]  = 30;
	      motor[rightMotor] = 30;
	    }
	    // LEFT sensor sees dark:
	    if(SensorValue(lineFollowerLEFT) > threshold)
	    {
	      // counter-steer left:
	      motor[leftMotor]  = -50;
	      motor[rightMotor] = 50;
	  	}
	  }
	  pause();
}
void search_line(bool direction){
	int di = (direction) ? (1) : (-1);
	turn(20,direction);
	while(SensorValue(lineFollowerRIGHT) < threshold && SensorValue(lineFollowerCENTER) < threshold && SensorValue(lineFollowerLEFT) < threshold){
			motor[rightMotor] = -50*di;
			motor[leftMotor]  = 50*di;
	}
	 pause();
}

void arm(int arm_num, int num){
	while(SensorValue[potentiometer]>10+arm_num && SensorValue[potentiometer]>arm_num-10){
			motor[port7] = 127*num;
		}
		motor[port7]=0;
	if (num == -1){
		while(SensorValue[potentiometer]<10+arm_num && SensorValue[potentiometer]<arm_num-10){
			motor[port7] = 127*num;
		}
			motor[port7] = 127;
			wait1Msec(20);
			motor[port7]=0;
	}
}

void claw(int claw_num){
	if(claw_num == -1){
			motor[clawMotor] = 127*claw_num;
			wait1Msec(400);
			motor[clawMotor] = 0;
	}
	else{
			motor[clawMotor] = 127*claw_num;
			wait1Msec(100);
			motor[clawMotor] = 0;
	}
}

/*task holdArm()
{
	int initial = SensorValue[potentiometer];

	while(true)
	{
		while(SensorValue(potentiometer) == 0)
			motor[armMotor] = 50;

		motor[armMotor] = 0;
	}
}*/
