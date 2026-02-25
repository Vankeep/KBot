#include <KBot.h>

KBot bot;

void setup(){
  bot.begin();
  bot.servo1.begin(ServoPin::Name::SRV1);
  bot.servo1.setAngle(0);
}

void loop(){
  bot.update();

  // getAngle() вернёт 0 только когда сервопривод физически доедет до позиции 0
  if(bot.servo1.getAngle() == 0){
    bot.servo1.setAngle(180);
  } 
  // getAngle() вернёт 180 только когда сервопривод физически доедет до позиции 180
  else if(bot.servo1.getAngle() == 180){
    bot.servo1.setAngle(0);
  }
}