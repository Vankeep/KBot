#include <KBot.h>

KBot bot;

void setup(){
  bot.begin();
}

void loop(){
  bot.update();
  int mm = bot.tof.getDistance();

  if(mm > 100){
    bot.wheel.drive(50,50);
  } else {
    bot.wheel.drive(0,0);
  }
  bot.oled.printStr1("tof distance = " + String(mm) + " mm");
}