#include <KBot.h>

KBot bot;

void setup(){
  bot.begin();
}

void loop(){
  bot.update();
  int mm = bot.ultrasonic.getDistanceMm();
  bot.oled.printStr1("Dist = " + String(mm) + " mm");
}