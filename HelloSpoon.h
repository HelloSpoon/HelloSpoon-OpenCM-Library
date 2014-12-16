/*
 Code based on:
 Dynamixel Pro library for OpenCM-9.04 made by ROBOTIS, LTD.

 Modified to work only with HelloSpoon robot.

 Modifications made by Luis G III for HelloSpoon robot.
 Webpage: http://hellospoonrobot.com
 Twitter: @HelloSpoon
 Youtube: http://youtube.com/user/hellospoonrobot

 This file can be used and be modified by anyone, 
 don't forget to say thank you to OP!
 */

#ifndef HELLOSPOON_H_
#define HELLOSPOON_H_

/*EEPROM Area*/
#define XL_MODEL_NUMBER_L           0
#define XL_MODEL_NUMBER_H           1
#define XL_VERSION                  2
#define XL_ID                       3
#define XL_BAUD_RATE                4
#define XL_RETURN_DELAY_TIME        5
#define XL_CW_ANGLE_LIMIT_L         6
#define XL_CW_ANGLE_LIMIT_H         7
#define XL_CCW_ANGLE_LIMIT_L        8
#define XL_CCW_ANGLE_LIMIT_H        9
#define XL_CONTROL_MODE             11
#define XL_LIMIT_TEMPERATURE        12
#define XL_DOWN_LIMIT_VOLTAGE       13
#define XL_UP_LIMIT_VOLTAGE         14
#define XL_MAX_TORQUE_L             15
#define XL_MAX_TORQUE_H             16
#define XL_RETURN_LEVEL             17
#define XL_ALARM_SHUTDOWN           18

/*RAM Area*/
#define XL_TORQUE_ENABLE            24
#define XL_LED                      25
#define XL_D_GAIN    				27
#define XL_I_GAIN      				28
#define XL_P_GAIN    				29
#define XL_GOAL_POSITION_L          30
#define XL_GOAL_SPEED_L             32
#define XL_GOAL_TORQUE 		        35
#define XL_PRESENT_POSITION         37
#define XL_PRESENT_SPEED            39
#define XL_PRESENT_LOAD             41
#define XL_PRESENT_VOLTAGE          45
#define XL_PRESENT_TEMPERATURE      46
#define XL_REGISTERED_INSTRUCTION   47
#define XL_MOVING                   49
#define XL_HARDWARE_ERROR           50
#define XL_PUNCH                    51

#include "libpandora_types.h"

typedef struct data {
    int             iID;
    int				iAddr;
    int             iLength;
    int             iError;
    byte  			iData[8];
} BulkData, *PBulkData;


class HelloSpoon{
	
	private:
	byte usedDxlPro;
	BulkData mBulkData[32];

	public:
	HelloSpoon();
	virtual ~HelloSpoon();	

	void begin();
	void deactivateTrunk();
	void activateTrunk();
	
	byte TorqueON(byte id);
	byte TorqueOFF(byte id);
	byte moveServo(byte id, word value);
	byte setServoSpeed(byte id, word value);
	byte setServoTorque(byte id, word value);
	byte LED(byte id, char led_color[]);

	word getSpoonLoad();
};

#endif
