#ifndef epd1in54_V2_H
#define epd1in54_V2_H

// Display resolution
#define EPD_WIDTH       200
#define EPD_HEIGHT      200

#define RST_PIN         8
#define DC_PIN          9
#define CS_PIN          10
#define BUSY_PIN        7

class Epd
{
public:
	unsigned long width;
	unsigned long height;

	Epd();
	~Epd();
	int LDirInit(void);

	void SendCommand(unsigned char command);
	void SendData(unsigned char data);
	void WaitUntilIdle(void);
	void Reset(void);
	void Display(const unsigned char* frame_buffer);

	void Sleep(void);
private:
	static int  IfInit(void);
	unsigned int reset_pin;
	unsigned int dc_pin;
	unsigned int cs_pin;
	unsigned int busy_pin;
};

#endif 