#include <M5Stack.h>
#define TFT_GREY 0x5AEB
uint32_t targetTime = 0;
static uint8_t conv2d(const char *p);
int hh = 0, mm = 0, ss = 0, ms = 0;

byte omm = 99, oss = 99, oms = 101;
byte xcolon = 0, xsecs = 0, xms = 0;
bool run = false;
unsigned int colour = 0;

void setup(void)
{
    M5.begin();
    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
    targetTime = millis() + 10;
}

void loop()
{
    if(run)
    {
    if (targetTime < millis())
    {
        targetTime = millis() + 10;
        ms++;
        if (ms == 100)
        {
            ms = 0;
            oss = ss;
            ss++;
            if (ss == 60)
            {
                ss = 0;
                omm = mm;
                mm++;
                if (mm > 59)
                {
                    mm = 0;
                    hh++;
                    if (hh > 23)
                    {
                        hh = 0;
                    }
                }
            }
        }
        int xpos = 0;
        int ypos = 85;
        int ysecs = ypos + 24;
        if (omm != mm)
        {
            omm = mm;
            if (hh < 10)
                xpos += M5.Lcd.drawChar('0', xpos, ypos, 7);
            xpos += M5.Lcd.drawNumber(hh, xpos, ypos, 7);
            xcolon = xpos;
            xpos += M5.Lcd.drawChar(':', xpos, ypos, 7);
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
                M5.Lcd.drawChar(':', xcolon, ypos, 7);
                xpos += M5.Lcd.drawChar(':', xsecs, ypos, 7);
                M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
            }
            else
            {
                M5.Lcd.drawChar(':', xcolon, ypos, 7);
                xpos += M5.Lcd.drawChar(':', xsecs, ypos, 7);
            }
            if (ss < 10)
                xpos += M5.Lcd.drawChar('0', xpos, ypos, 7);
           xpos += M5.Lcd.drawNumber(ss, xpos, ypos, 7);
           xms = xpos;
        }
        if (oms != ms)
        {
            xpos = xms;
           oms = ms;
           xpos+=M5.Lcd.drawChar('.',xpos,ypos,7);
            if (ms < 10)
                xpos += M5.Lcd.drawChar('0', xpos, ypos, 7);
            xpos+=M5.Lcd.drawNumber(ms, xpos, ypos, 7);
        }
    }
    }
    else
    {
      int xpos = 0;
      int ypos = 85;
            if (hh < 10)
                xpos += M5.Lcd.drawChar('0', xpos, ypos, 7);
            xpos += M5.Lcd.drawNumber(hh, xpos, ypos, 7);
            xcolon = xpos;
            xpos += M5.Lcd.drawChar(':', xpos, ypos, 7);
            if (mm < 10)
                xpos += M5.Lcd.drawChar('0', xpos, ypos, 7);
            xpos += M5.Lcd.drawNumber(mm, xpos, ypos, 7);
            xsecs = xpos;
            xpos += M5.Lcd.drawChar(':', xsecs, ypos, 7);
             if (ss < 10)
                xpos += M5.Lcd.drawChar('0', xpos, ypos, 7);
           xpos += M5.Lcd.drawNumber(ss, xpos, ypos, 7);
           xms = xpos;
           xpos = xms;
           oms = ms;
           xpos+=M5.Lcd.drawChar('.',xpos,ypos,7);
            if (ms < 10)
                xpos += M5.Lcd.drawChar('0', xpos, ypos, 7);
            xpos+=M5.Lcd.drawNumber(ms, xpos, ypos, 7);
    }
    if(M5.BtnA.wasPressed()) run = true;
    if(M5.BtnB.wasPressed()) run = false;
    if(M5.BtnC.wasPressed())
    {
      hh = 0;
      mm = 0;
      ss = 0;
      ms = 0;
      run = false;
    }
    M5.update();
}
