#include <KBot.h>

KBot bot;

void setup(){
  bot.begin();
}

void loop(){
  bot.update();
  bot.wheel.drive(50, 50);
  // bot.wheel.drive(-80, -80);
  // bot.wheel.drive(Wheel::Name::XP14A, 50);
  // bot.wheel.drive(Wheel::Name::XP15A, -50);
  // bot.wheel.drive(Wheel::Name::XP14B, 50);
  // bot.wheel.drive(Wheel::Name::XP15B, -50);
}