#include <M5Stack.h>
#define TFT_GREY 0x5AEB
uint32_t targetTime = 0;
static uint8_t conv2d(const char *p);

// uint8_t hh = conv2d(__TIME__), mm = conv2d(__TIME__ + 3);
// uint8_t ss = conv2d(__TIME__ + 6);
int hh = 0, mm = 0, ss = 0, ms = 0;

byte omm = 99, oss = 99, oms = 99;
byte xcolon = 0, xsecs = 0, xms = 0;
unsigned int colour = 0;

void setup(void)
{
    M5.begin();
    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
    targetTime = millis() + 1000;
}

void loop()
{
    if (targetTime < millis())
    {
        targetTime = millis() + 1000;
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
            xpos += M5.Lcd.drawChar(':', xpos, ypos - 8, 7);
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
                M5.Lcd.drawChar(':', xcolon, ypos - 8, 7);
                xpos += M5.Lcd.drawChar(':', xsecs, ysecs, 7);
                M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
            }
            else
            {
                M5.Lcd.drawChar(':', xcolon, ypos - 8, 7);
                xpos += M5.Lcd.drawChar(':', xsecs, ysecs, 7);
            }
            if (ss < 10)
                xpos += M5.Lcd.drawChar('0', xpos, ysecs, 7);
            M5.Lcd.drawNumber(ss, xpos, ysecs, 7);
        }
        xms = xpos;
        if (oms != ms)
        {
            oms = ms;
            xpos = xms;
            xpos += M5.Lcd.drawChar('.', xms, ysecs, 7);
            if (ms < 10)
                xpos += M5.Lcd.drawChar('0', xpos, ysecs, 7);
            M5.Lcd.drawNumber(ms, xpos, ysecs, 7);
        }
    }
}
static uint8_t conv2d(const char *p)
{
    uint8_t v = 0;
    if ('0' <= *p && *p <= '9')
        v = *p - '0';
    return 10 * v + *++p - '0';
}
