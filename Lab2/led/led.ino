#include <M5Stack.h>
int ledAPin = 21;
int ledBPin = 22;
int ledAState = LOW;
int ledBState = LOW;
int i;
void setup()
{
    // put your setup code here, to run once:
    M5.begin();
    for (i = 16; i <= 22; i++)
    {
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
    }
    M5.update();
}

void loop()
{
    // put your main code here, to run repeatedly:
    if (M5.BtnA.wasPressed())
    {
        ledAState = !ledAState;
        digitalWrite(ledAPin, ledAState);
    }
    else if (M5.BtnB.wasPressed())
    {
        ledBState = !ledBState;
        digitalWrite(ledBPin, ledBState);
    }
    else if (M5.BtnC.wasPressed())
    {
        int t = 50;
        for (i = 16; i <= 23; i++)
        {
            digitalWrite(i, LOW);
            delay(t);
            digitalWrite(i, HIGH);
        }
    }
    M5.update();
}