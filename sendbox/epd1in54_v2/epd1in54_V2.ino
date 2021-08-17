#include <SPI.h>
#include "epd1in54_V2.h"
#include "epdpaint.h"

Epd epd;
unsigned char image[1024];
Paint paint(image, 0, 0);

int prevPosition = 5;

#define COLORED     0
#define UNCOLORED   1

void setup(){
    epd.LDirInit();
    epd.Clear();

    int a = 40;
    
    paint.SetWidth(a);
    paint.SetHeight(a);
    a = a - 1;
  
    paint.Clear(UNCOLORED);
    paint.DrawVerticalLine(0,0, a, COLORED);
    paint.DrawVerticalLine(a,0, a, COLORED);

    paint.DrawHorizontalLine(0,0, a, COLORED);
    paint.DrawHorizontalLine(0,a, a, COLORED);
    
    //paint.DrawLine(0, 0, a, a, COLORED);
    //paint.DrawLine(0, a, a, 0, COLORED);
    epd.SetFrameMemory(paint.GetImage(), 0, 40, paint.GetWidth(), paint.GetHeight());
    epd.SetFrameMemory(paint.GetImage(), 40, 0, paint.GetWidth(), paint.GetHeight());
    epd.SetFrameMemory(paint.GetImage(), 40, 40, paint.GetWidth(), paint.GetHeight());
    epd.SetFrameMemory(paint.GetImage(), 80, 40, paint.GetWidth(), paint.GetHeight());
    epd.SetFrameMemory(paint.GetImage(), 120, 40, paint.GetWidth(), paint.GetHeight());
    epd.SetFrameMemory(paint.GetImage(), 160, 40, paint.GetWidth(), paint.GetHeight());
    
    epd.SetFrameMemory(paint.GetImage(), 40, 80, paint.GetWidth(), paint.GetHeight());
    epd.SetFrameMemory(paint.GetImage(), 40, 120, paint.GetWidth(), paint.GetHeight());
    epd.SetFrameMemory(paint.GetImage(), 40, 160, paint.GetWidth(), paint.GetHeight());


    //epd.SetFrameMemory(paint.GetImage(), 40, 160, paint.GetWidth(), paint.GetHeight());
  
    epd.DisplayFrame();
    epd.HDirInit();
    epd.Sleep();
}

void loop(){
  
}

//void setup()
//{
//  pinMode(PD1, OUTPUT);
//  
//  initPositionPins();
//}

//void loop()
//{
//  digitalWrite(PD1, 0);
//  int rotation  = getPosition();
//  if(rotation != prevPosition){
//    prevPosition = rotation;
//    //drow
//    epd.LDirInit();
//    epd.Clear();
//    
//    paint.SetWidth(64);
//    paint.SetHeight(64);
//    paint.SetRotate(rotation);
//  
//    paint.Clear(UNCOLORED);
//    paint.DrawLine(0, 32, 32, 64, COLORED);
//    paint.DrawLine(1, 32, 33, 64, COLORED);
//    paint.DrawLine(2, 32, 34, 64, COLORED);
//    paint.DrawLine(32, 64, 64, 32, COLORED);
//    paint.DrawLine(33, 64, 65, 32, COLORED);
//    paint.DrawLine(34, 64, 66, 32, COLORED);
//    epd.SetFrameMemory(paint.GetImage(), 68, 68, paint.GetWidth(), paint.GetHeight());
  
//    epd.DisplayFrame();
//    epd.HDirInit();
//    epd.Sleep();
//    digitalWrite(PD1, 1);
//  }
//  delay(500);
//}


//void initPositionPins(){
//    pinMode(PD4, OUTPUT);
//    pinMode(PD3, OUTPUT);
//    pinMode(PD2, OUTPUT);  
//}

//int getPosition(){
//    pinMode(PD4, INPUT);
//    pinMode(PD3, OUTPUT);
//    pinMode(PD2, OUTPUT);  
//    digitalWrite(PD3, 0);
//    digitalWrite(PD2, 1);
//    if(digitalRead(PD4) == 0)
//      return 0;
//    digitalWrite(PD3, 1);
//    digitalWrite(PD2, 0);     
//    if(digitalRead(PD4) == 0)
//      return 2;    
//    pinMode(PD4, OUTPUT);
//    pinMode(PD3, INPUT);    
//    digitalWrite(PD4, 1);
//    if(digitalRead(PD3) == 0)
//      return 1;        
//    return 3;
//}
