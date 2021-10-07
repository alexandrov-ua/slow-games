#include <SPI.h>
#include "epd1in54_V2.h"
#include "imagedata.h"
#include <stdio.h>

Epd epd;
#define COLORED     0
#define UNCOLORED   1

void setup()
{
  epd.LDirInit();
  epd.Display(IMAGE_DATA);
  epd.Sleep();
}

void loop()
{

}
