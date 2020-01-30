#include <M5Stack.h>
void setup(){
  M5.begin();
  M5.Speaker.tone(262);
  delay(1000);
  M5.Speaker.mute();
}
