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

#include "dxl_pro.h"
#include "HelloSpoon.h"

extern uint8 gbIsDynmixelUsed;

byte mResult;

word readWord(byte bID, int wAddress);
byte writeWord(byte bID, int wAddress, word wData);

HelloSpoon::HelloSpoon() {
	// TODO Auto-generated constructor stub

}

HelloSpoon::~HelloSpoon() {
	// TODO Auto-generated destructor stub
}

void HelloSpoon::begin(){
	int i=0;
	uint32 Baudrate = 0;
	//TxDString("[DXL]start begin\r\n");

	//change GPIO D9(PA9),D10(PA10) -> D20(PB6), D21(PB7) in USART1 using AFIO
	afio_remap(AFIO_REMAP_USART1);
	//must be declare as SWJ_NO_NJRST because dxl bus use PB5 as DXL_DIR in Half Duplex USART and also use SWJ
	afio_cfg_debug_ports(AFIO_DEBUG_FULL_SWJ_NO_NJRST);

	 gpio_set_mode(PORT_TXRX_DIRECTION, PIN_TXRX_DIRECTION, GPIO_OUTPUT_PP);
	 gpio_write_bit(PORT_TXRX_DIRECTION, PIN_TXRX_DIRECTION, 0 );// RX Enable


	 // initialize GPIO D20(PB6), D21(PB7) as DXL TX, RX respectively
	 gpio_set_mode(PORT_DXL_TXD, PIN_DXL_TXD, GPIO_AF_OUTPUT_PP);
	 gpio_set_mode(PORT_DXL_RXD, PIN_DXL_RXD, GPIO_INPUT_FLOATING);


	 //Initialize USART 1 device
	 usart_init(USART1);

	 //Calculate baudrate, refer to ROBOTIS support page.
	 //Baudrate = 2000000 / (baud + 1);
	 Baudrate = dxl_get_baudrate(3);

	usart_set_baud_rate(USART1, STM32_PCLK2, Baudrate);
	nvic_irq_set_priority(USART1->irq_num, 0);//[ROBOTIS][ADD] 2013-04-10 set to priority 0
	usart_attach_interrupt(USART1,dxlProInterrupt);
	usart_enable(USART1);

	gbIsDynmixelUsed = 0;  //[ROBOTIS]2012-12-13 to notify end of using dynamixel classic to uart.c
	clearBuffer256Ex();
	mResult= 0;
	for(i=0; i<32; i++){
		mBulkData[i].iID = 0;
		mBulkData[i].iAddr = 0; //get address
		mBulkData[i].iLength = 0;
		mBulkData[i].iError = 0; //Error code
		mBulkData[i].iData[0] = 0; //DATA1
		mBulkData[i].iData[1] = 0; //DATA2
		mBulkData[i].iData[2] = 0; //DATA3
		mBulkData[i].iData[3] = 0; //DATA4
	}
}

byte HelloSpoon::moveServo(byte id, word value){

	byte res;

	if(id == 1){
		res = writeWord(id, 30, value);
	}

	else if(id == 2){
		res = writeWord(id, 30, value);
		res = writeWord(id + 1, 30, 1024 - value);
	}

	else if (id == 3){
		res = writeWord(id + 1, 30, value);
	}

	else if (id == 4){
		res = writeWord(id + 1, 30, value);
	}

	return res;
}

byte HelloSpoon::setServoSpeed(byte id, word value){
	byte res;

	if(id == 1){
		res = writeWord(id, 32, value);
	}

	else if(id == 2){
		res = writeWord(id, 30, value);
		res = writeWord(id + 1, 32, value);
	}

	else if (id == 3){
		res = writeWord(id + 1, 32, value);
	}

	else if (id == 4){
		res = writeWord(id + 1, 32, value);
	}

	return res;
}

byte HelloSpoon::LED(byte id, char led_color[]){
	int val = 0;
	byte res;

	if(led_color[0] == 'r'){
		val = 1;
	}

	else if(led_color[0] == 'g'){
		val = 2;
	}

	else if(led_color[0] == 'y'){
		val = 3;
	}

	else if(led_color[0] == 'b'){
		val = 4;
	}

	else if(led_color[0] == 'p'){
		val = 5;
	}

	else if(led_color[0] == 'c'){
		val = 6;
	}

	else if(led_color[0] == 'w'){
		val = 7;
	}

	if(id == 1){
		res = writeWord(id, 25, val);
	}

	else if(id == 2){
		res = writeWord(id, 25, val);
		res = writeWord(id + 1, 25, val);
	}

	else if (id == 3){
		res = writeWord(id + 1, 25, val);
	}

	else if (id == 4){
		res = writeWord(id + 1, 25, val);
	}

	return res;
}

word HelloSpoon::getSpoonLoad(){
	word load;
	load = readWord(5, 41);
	return load;
}

word readWord(byte bID, int wAddress){
	mResult = 0;

	gbpParameterEx[0]	= (unsigned char)DXL_LOBYTE(wAddress);
	gbpParameterEx[1]	= (unsigned char)DXL_HIBYTE(wAddress);
	gbpParameterEx[2]	= 2; //2byte
	gbpParameterEx[3]	= 0;
	if(txrx_PacketEx(bID, INST_READ_EX, 4)){
		mResult = 1;
		return(DXL_MAKEWORD(gbpRxBufferEx[9], gbpRxBufferEx[10]));
	}else{
		mResult = 0;
		return 0xff;
	}

}

byte writeWord(byte bID, int wAddress, word wData){
	mResult = 0;
	//insert wAddress to parameter bucket
	gbpParameterEx[0]	= (unsigned char)DXL_LOBYTE(wAddress);
	gbpParameterEx[1]	= (unsigned char)DXL_HIBYTE(wAddress);
	//insert data to parameter bucket
	gbpParameterEx[2]	= DXL_LOBYTE(wData);
	gbpParameterEx[3]	= DXL_HIBYTE(wData);

	mResult = txrx_PacketEx(bID, INST_WRITE_EX, 4); //// parameter length 4 = 2(address)+2(data)
	clearBuffer256Ex();

	return mResult;
}
