#include <M5Stack.h>

extern unsigned char logo[];
int screen_width = 320;
int screen_height = 240;
int racket_position;
int racket2_position;
long interval;
int ball_x;
int ball_y;
int ball_r;
int accel_x;
int accel_y;
int score;
int score2;
bool run = true;

void start()
{
  M5.Lcd.fillScreen(0x0000);
  interval = 60;
  ball_x = 160;
  ball_y = 120;
  ball_r = 6;
  accel_x = 5;
  accel_y = 5;
  score = 0;
  M5.Lcd.drawBitmap(0, 0, screen_width, screen_height, (uint16_t *)logo);
  M5.Lcd.setTextSize(2);
  long previousMillis = 0;
  long interval = 500;
  int color = 0x0000;
  while (true)
  {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > interval)
    {
      previousMillis = currentMillis;
      color = (color == 0x7bef) ? 0xffff : 0x7bef;
      M5.Lcd.setCursor(35, 200);
      M5.Lcd.setTextColor(color);
      M5.Lcd.print("press any key to play");
    }
    M5.update();
    if (M5.BtnA.wasPressed() || M5.BtnB.wasPressed() || M5.BtnC.wasPressed())
      break;
  }
  M5.Lcd.fillScreen(0x0000);
  M5.Speaker.tone(800);
  delay(100);
  M5.Speaker.tone(1200);
  delay(100);
  M5.Speaker.mute();
  delay(500);
  M5.Lcd.fillScreen(0xffff);
}

void game()
{
  M5.Lcd.fillCircle(ball_x, ball_y, ball_r, 0x7bef);
  long previousMillis = 0;
  while (true)
  {
    int voltage = analogRead(36) * 3400 / 4096;
    int voltage2 = analogRead(35) * 3400 / 4096;
    int percentage = voltage * 100 / 3400;
    int percentage2 = voltage2 * 100 / 3400;
    racket_position = map(percentage, 0, 100, 0, 5);
    racket2_position = map(percentage2, 0, 100, 5, 10);
    int racket_width = 20;
    int racket_height = 40;
    int racket_margin = 10;
    int x, y, x2, y2, color, racket_x, racket_y, racket2_x, racket2_y;
    for (int i = 0; i < 5; i++)
    {
      x = 0;
      y = i * (racket_height + racket_margin);
      color = (i == racket_position) ? RED : WHITE;
      M5.Lcd.fillRect(x, y, racket_width, racket_height, color);
      if (i == racket_position)
      {
        racket_x = x;
        racket_y = y;
      }
    }
    for (int i = 5; i < 10; i++)
    {
      x2 = screen_width - racket_width;
      y2 = (9 - i) * (racket_height + racket_margin);
      color = (i == racket2_position) ? RED : WHITE;
      M5.Lcd.fillRect(x2, y2, racket_width, racket_height, color);
      if (i == racket2_position)
      {
        racket2_x = x2;
        racket2_y = y2;
      }
    }
    M5.Lcd.setTextColor(TFT_BLACK, TFT_WHITE);
    M5.Lcd.drawNumber(score, 100, 20, 2);
    M5.Lcd.drawNumber(score2, 200, 20, 2);
    unsigned long currentMillis = millis();
    if (run)
    {
      if (currentMillis - previousMillis > interval)
      {
        previousMillis = currentMillis;
        M5.Lcd.fillCircle(ball_x, ball_y, ball_r, WHITE);
        ball_x += accel_x;
        ball_y += accel_y;
        M5.Lcd.fillCircle(ball_x, ball_y, ball_r, 0x7bef);
        if (ball_y <= 0)
          accel_y *= -1;
        if (ball_y >= 240)
          accel_y *= -1;
        if ((ball_x + ball_r >= racket2_x) && (ball_y + ball_r >= racket2_y) && (ball_y - ball_r <= racket2_y + racket_height))
        {
          accel_x *= -1;
          accel_y *= 1;
          repulse2();
        }
        if ((ball_x - ball_r <= racket_x + racket_width) && (ball_y + ball_r >= racket_y) && (ball_y - ball_r <= racket_y + racket_height))
        {
          accel_x *= -1;
          accel_y *= 1;
          repulse();
        }
        if (ball_x < 0)
        {
          ball_x = 300;
          ball_y = 120;
          interval = 40;
          score2++;
        }
        if (ball_x > screen_width)
        {
          ball_x = 20;
          ball_y = 120;
          interval = 40;
          score++;
        }
      }
    }
    if (M5.BtnB.wasPressed())
      run = !run;
    if (M5.BtnC.wasPressed())
    {
      score = 0;
      score2 = 0;
      M5.Lcd.fillRect(100, 20, 30, 30, WHITE);
      M5.Lcd.fillRect(200, 20, 30, 30, WHITE);
      M5.Lcd.setTextColor(TFT_BLACK, TFT_WHITE);
      M5.Lcd.drawNumber(score, 100, 20, 2);
      M5.Lcd.drawNumber(score2, 200, 20, 2);
      run = true;
    }
    M5.update();
  }
}

void repulse()
{
  M5.Speaker.tone(1800);
  delay(50);
  M5.Speaker.mute();
  score++;
  interval -= (interval >= 25) ? 5 : 0;
}

void repulse2()
{
  M5.Speaker.tone(1800);
  delay(50);
  M5.Speaker.mute();
  score2++;
  interval -= (interval >= 25) ? 5 : 0;
}

void setup()
{
  M5.begin();
  pinMode(36, INPUT);
  pinMode(35, INPUT);
}

void loop()
{
  start();
  game();
}
