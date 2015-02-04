#include <HelloSpoon.h>

HelloSpoon robot;

int wave = 0;

void setup(){
	
	robot.begin();
	robot.activateTrunk();

  }

void loop(){
	
	if(wave<5){
		robot.moveJoint(4, 300);
		delay(1000);
		robot.moveJoint(4, 450);
		delay(1000);
		wave++;
	}

}
