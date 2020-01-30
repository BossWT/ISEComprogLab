#include <M5Stack.h>
const int nC4 = 262;
const int nD4 = 294;
const int nE4 = 330;
const int nF4 = 349;
const int nG4 = 392;
const int nA4 = 440;
const int nB4 = 494;
const int nC5 = 524;
const int nD5 = 588;
const int nE5 = 660;
const int nF5 = 698;
const int note[] = {0,nD5,nC5,nD5,nF4,nC5,nA4,nA4,nA4};
const int duration[] = {4,4,4,4,4,4,4,4,4};
void setup(){
  M5.begin();
}
void loop()
{
  for(int i=0;i<9;i++)
  {
    int wait=1000/duration[i];
    M5.Speaker.tone(note[i]);
    delay(wait);
    M5.Speaker.mute();
    delay(50);
  }
  M5.Speaker.mute();
  delay(2000);
  M5.update();
}
