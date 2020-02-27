#include <M5Stack.h>
#define TFT_GREY 0x5AEB
uint32_t targetTime = 0;
int mm = 0, ss = 0;

byte omm = 99, oss = 99;
byte xcolon = 0, xsecs = 0;
bool run = false;
unsigned int colour = 0;

void setup()
{
  M5.begin();
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
  targetTime = millis() + 1000;
}

void loop()
{
  if (mm == 0 && ss == 0)
    run = false;
  if (run)
  {
    if (targetTime < millis())
    {
      targetTime = millis() + 1000;
      ss--;
      if (ss < 0 && mm != 0)
      {
        ss = 59;
        omm = mm;
        mm--;
      }
    }
    int xpos = 80;
    int ypos = 85;
    int ysecs = ypos + 24;
    if (omm != mm)
    {
      omm = mm;
      if (mm < 10)
        xpos += M5.Lcd.drawChar('0', xpos, ypos, 7);
      xpos += M5.Lcd.drawNumber(mm, xpos, ypos, 7);
      xsecs = xpos;
    }
    if (oss != ss)
    {
      oss = ss;
      xpos = xsecs;
      if (ss % 2)
      {
        M5.Lcd.setTextColor(0x39C4, TFT_BLACK);
        M5.Lcd.drawChar(':', xsecs, ypos, 7);
        xpos += M5.Lcd.drawChar(':', xsecs, ypos, 7);
        M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
      }
      else
      {
        M5.Lcd.drawChar(':', xsecs, ypos, 7);
        xpos += M5.Lcd.drawChar(':', xsecs, ypos, 7);
      }
      if (ss < 10)
        xpos += M5.Lcd.drawChar('0', xpos, ypos, 7);
      xpos += M5.Lcd.drawNumber(ss, xpos, ypos, 7);
    }
    if (mm == 0 && ss == 0)
    {
      while (!M5.BtnA.wasPressed() && !M5.BtnB.wasPressed() && !M5.BtnC.wasPressed())
      {
        M5.Speaker.tone(600);
        delay(50);
        M5.Speaker.mute();
        M5.Speaker.tone(200);
        delay(50);
        M5.Speaker.mute();
        delay(50);
        M5.update();
      }
      M5.Speaker.mute();
      delay(50);
    }
  }
  else
  {
    int xpos = 80;
    int ypos = 85;
    if (mm < 10)
      xpos += M5.Lcd.drawChar('0', xpos, ypos, 7);
    xpos += M5.Lcd.drawNumber(mm, xpos, ypos, 7);
    xsecs = xpos;
    xpos += M5.Lcd.drawChar(':', xsecs, ypos, 7);
    if (ss < 10)
      xpos += M5.Lcd.drawChar('0', xpos, ypos, 7);
    xpos += M5.Lcd.drawNumber(ss, xpos, ypos, 7);
  }
  if (M5.BtnA.wasPressed() && !run)
  {
    if (mm < 59)
      mm++;
    else
      mm = 0;
  }
  if (M5.BtnB.wasPressed() && !run)
  {
    if (ss < 59)
      ss++;
    else
      ss = 0;
  }
  if (M5.BtnC.wasPressed())
    run = !run;
  if (M5.BtnA.pressedFor(5000) && !run)
    mm = 0;
  if (M5.BtnB.pressedFor(5000) && !run)
    ss = 0;
  if (M5.BtnC.pressedFor(5000))
  {
    mm = 0;
    ss = 0;
    run = false;
  }
  M5.update();
}
