#pragma config(Sensor, in3,    lineFollowerRIGHT,   sensorLineFollower)
#pragma config(Sensor, in2,    lineFollowerCENTER,  sensorLineFollower)
#pragma config(Sensor, in1,    lineFollowerLEFT,    sensorLineFollower)
#pragma config(Sensor, dgtl1,  sonarSensor,         sensorSONAR_cm)
#pragma config(Sensor, in4,    lightSensor,         sensorReflection)
#pragma config(Sensor, dgtl9,  rightEncoder,        sensorQuadEncoder)
#pragma config(Sensor, dgtl11,  leftEncoder,         sensorQuadEncoder)
#pragma config(Motor,  port2,           rightMotor,    tmotorNormal, openLoop)
#pragma config(Motor,  port3,           leftMotor,     tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port6,           clawMotor,     tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port7,           armMotor,      tmotorVex393, openLoop, reversed)
#pragma config(Sensor, dgtl8,    Button,              sensorTouch)
#pragma config(Sensor, in5, potentiometer, sensorPotentiometer)
#pragma config(UART_Usage, UART2, uartVEXLCD, baudRate19200, IOPins, None, None)

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|*                             	    - Triple Sensor Line Tracking -                                   *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program uses 3 VEX Line Follower Sensors to track a black line on a light(er) surface.       *|
|*  There is a two second pause at the beginning of the program.                                      *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Reversing 'rightMotor' (port 2) in the "Motors and Sensors Setup" is needed with the        *|
|*        "Squarebot" mode, but may not be needed for all robot configurations.                       *|
|*    2)  Lighting conditions, line darkness, and surface lightness change from place to place,       *|
|*        so the value of 'threshold' may need to be changed to better suit your environment.         *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor  - Port 2     rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor  - Port 3     leftMotor           VEX 3-wire module     Left side motor                   *|
|*    Analog - Port 1     lineFollowerRIGHT   VEX Light Sensor      Front-right, facing down          *|
|*    Analog - Port 2     lineFollowerCENTER  VEX Light Sensor      Front-center, facing down         *|
|*    Analog - Port 3     lineFollowerLEFT    VEX Light Sensor      Front-left, facing down           *|
\*-----------------------------------------------------------------------------------------------4246-*/


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
#include "../functions/basic_movement.c"
task linefollower(){

  int threshold = 2500;      /* found by taking a reading on both DARK and LIGHT    */
                            /* surfaces, adding them together, then dividing by 2. */
  while(true)
  {
    // RIGHT sensor sees dark:
    if(SensorValue(lineFollowerLEFT) > threshold)
    {
      // counter-steer right:
      motor[leftMotor]  = -31;
      motor[rightMotor] = 31;
    }
    // CENTER sensor sees dark:
    if(SensorValue(lineFollowerCENTER) > threshold)
    {
      // go straight
      motor[leftMotor]  = 31;
      motor[rightMotor] = 31;
    }
    // LEFT sensor sees dark:
    if(SensorValue(lineFollowerRIGHT) > threshold)
    {
      // counter-steer left:
      motor[leftMotor]  = 31;
      motor[rightMotor] = -31;
  	}
	}
}
task controller(){
	while(1 == 1)
  {
    motor[leftMotor]  = (vexRT[Ch3] + vexRT[Ch4])/2;
    motor[rightMotor] = (vexRT[Ch3] - vexRT[Ch4])/2;
    motor[armMotor]  = vexRT[Ch2]/2;

    if(vexRT[Btn6U] == 1)
		{
			motor[clawMotor] = power;
		}
		else if(vexRT[Btn5U] == 1)
		{
			motor[clawMotor] = -power;
		}
		else
		{
			motor[clawMotor] = 0;
		}
  }
}
task display(){
	bLCDBacklight = true;									// Turn on LCD Backlight
	string mainBattery, backupBattery;

	while(true)														// An infinite loop to keep the program running until you terminate it
	{
		clearLCDLine(0);											// Clear line 1 (0) of the LCD
		clearLCDLine(1);											// Clear line 2 (1) of the LCD

		//Display the Primary Robot battery voltage
		displayLCDString(0, 0, "Primary: ");
		sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
		displayNextLCDString(mainBattery);

		//Display the Backup battery voltage
		displayLCDString(1, 0, "Backup: ");
		sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');	//Build the value to be displayed
		displayNextLCDString(backupBattery);

		//Short delay for the LCD refresh rate
		wait1Msec(100);
	}
}
#include "../functions/tasks.c"
task main()
{
	StartTask(start);
	StartTask(display);
	while(1==1){
		}
 }
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
