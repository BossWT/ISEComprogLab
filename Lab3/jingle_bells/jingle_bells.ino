#include <M5Stack.h>
void setup()
{
  M5.begin();
  M5.update();
  Serial.begin(9600);
}
int index = 0;
void loop()
{
 const int nC4 = 262;
  const int nD4 = 294;
  const int nE4 = 330;
  const int nF4 = 349;
  const int nG4 = 392;
  const int nA4 = 440;
  const int nB4 = 494;
  const int nD5 = 588;
  const int nE5 = 660;
  const int nF5 = 698;
  const int note[] = {nE4,nE4,nE4,nE4,nE4,nE4,nE4,nG4,nC4,nD4,nE4,nF4,nF4,nF4,nF4,nF4,nE4,nE4,nE4,nD4,nD4,nE4,nD4,nD4};
  if(index == 24)
  {
  index = 0;
  }
    if(M5.BtnA.wasPressed())
    {
    M5.Speaker.tone(note[index]);
    index++;
    }
    if(M5.BtnA.isReleased())
    {
    M5.Speaker.mute();
    }
     M5.update();
  }
}
