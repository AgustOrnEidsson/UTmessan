
task start_by_light(){
	int tel = 1;
	while(1==1){
		if(SensorValue(lightSensor) < 400 && tel==1)
		{
			StartTask(linefollower);
			tel = 0;
			//StartTask(main);
		}
		else if(SensorValue(lightSensor) > 400)
		{
			StopTask(linefollower);
			motor[leftMotor] = 0;
			motor[rightMotor] = 0;
			motor[armMotor] = 0;
			motor[clawMotor] = 0;
			tel = 1;
			//StartTask(main);
		}
	}
}
task start(){
	while(1==1){
		if(vexRT[Btn7D] == 1)
		{
			StartTask(linefollower);
			//StartTask(main);
		}
		else if(vexRT[Btn7U] == 1)
		{
			StartTask(controller);
			//StartTask(main);
		}
		else if(vexRT[Btn8D] == 1||SensorValue(Button)==1)
		{
			StopTask(linefollower);
			StopTask(controller);
			StopTask(start_by_light);
			motor[leftMotor] = 0;
			motor[rightMotor] = 0;
			motor[armMotor] = 0;
			motor[clawMotor] = 0;
		}
			//StartTask(main);
	}
}
