#include <stdlib.h>
#include "epd1in54_V2.h"
#include<SPI.h>


unsigned char WF_Full_1IN54[159] =
{											
0x80,	0x48,	0x40,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0x40,	0x48,	0x80,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0x80,	0x48,	0x40,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0x40,	0x48,	0x80,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0xA,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x8,	0x1,	0x0,	0x8,	0x1,	0x0,	0x2,					
0xA,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x22,	0x22,	0x22,	0x22,	0x22,	0x22,	0x0,	0x0,	0x0,			
0x22,	0x17,	0x41,	0x0,	0x32,	0x20
};

Epd::~Epd()
{
};

Epd::Epd()
{
	reset_pin = RST_PIN;
	dc_pin = DC_PIN;
	cs_pin = CS_PIN;
	busy_pin = BUSY_PIN;
	width = EPD_WIDTH;
	height = EPD_HEIGHT;
};


void Epd::SendCommand(unsigned char command)
{
	digitalWrite(dc_pin, LOW);
	digitalWrite(CS_PIN, LOW);
    SPI.transfer(command);
    digitalWrite(CS_PIN, HIGH);
}

void Epd::SendData(unsigned char data)
{
	digitalWrite(dc_pin, HIGH);
	digitalWrite(CS_PIN, LOW);
    SPI.transfer(data);
    digitalWrite(CS_PIN, HIGH);
}

void Epd::WaitUntilIdle(void)
{
	while(digitalRead(busy_pin) == 1) {      //LOW: idle, HIGH: busy
		delay(100);
	}
	delay(200);
}

int Epd::LDirInit(void)
{
	/* this calls the peripheral hardware interface, see epdif */
	if (IfInit() != 0) {
		return -1;
	}
	/* EPD hardware init start */
	Reset();

	WaitUntilIdle();
	SendCommand(0x12);  //SWRESET
	WaitUntilIdle();

	SendCommand(0x01); //Driver output control
	SendData(0xC7);
	SendData(0x00);
	SendData(0x00);

	SendCommand(0x11); //data entry mode
	SendData(0x03);

  SendCommand(0x44);
  /* x point must be the multiple of 8 or the last 3 bits will be ignored */
  SendData((0 >> 3) & 0xFF);
  SendData((199 >> 3) & 0xFF);
  SendCommand(0x45);
  SendData(0 & 0xFF);
  SendData((0 >> 8) & 0xFF);
  SendData(199 & 0xFF);
  SendData((199 >> 8) & 0xFF);

	SendCommand(0x3C); //BorderWavefrom
	SendData(0x01);

	SendCommand(0x18);
	SendData(0x80);

	SendCommand(0x22); // //Load Temperature and waveform setting.
	SendData(0XB1);
	SendCommand(0x20);

	SendCommand(0x4E);   // set RAM x address count to 0;
	SendData(0x00);
	SendCommand(0x4F);   // set RAM y address count to 0X199;
	SendData(0xC7);
	SendData(0x00);
	WaitUntilIdle();

	//lut
	SendCommand(0x32);
	for(unsigned char i=0; i<153; i++)
		SendData(WF_Full_1IN54[i]);
	WaitUntilIdle();
	
    SendCommand(0x3f);
    SendData(WF_Full_1IN54[153]);
	
    SendCommand(0x03);
    SendData(WF_Full_1IN54[154]);
	
    SendCommand(0x04);
    SendData(WF_Full_1IN54[155]);
	SendData(WF_Full_1IN54[156]);
	SendData(WF_Full_1IN54[157]);
	
	SendCommand(0x2c);
    SendData(WF_Full_1IN54[158]);

	return 0;
}


void Epd::Reset(void)
{
	digitalWrite(reset_pin, HIGH);
	delay(20);
	digitalWrite(reset_pin, LOW);                //module reset
	delay(5);
	digitalWrite(reset_pin, HIGH);
	delay(20);
}

void Epd::Display(const unsigned char* frame_buffer)
{
	int w = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
	int h = EPD_HEIGHT;

	if (frame_buffer != NULL) {
		SendCommand(0x24);
		for (int j = 0; j < h; j++) {
			for (int i = 0; i < w; i++) {
				SendData(pgm_read_byte(&frame_buffer[i + j * w]));
			}
		}
	}

	SendCommand(0x22);
	SendData(0xc7);
	SendCommand(0x20);
	WaitUntilIdle();
}

void Epd::Sleep()
{
	SendCommand(0x10); //enter deep sleep
	SendData(0x01);
	delay(200);

	digitalWrite(reset_pin, LOW);
}

int Epd::IfInit(void) {
    pinMode(CS_PIN, OUTPUT);
    pinMode(RST_PIN, OUTPUT);
    pinMode(DC_PIN, OUTPUT);
    pinMode(BUSY_PIN, INPUT); 

    SPI.begin();
    SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
    return 0;
}