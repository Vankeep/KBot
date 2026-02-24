#include <KBot.h>

KBot bot;

void setup(){
  bot.begin();
  bot.servo.setAngle(ServoPin::Name::SRV1, 0);
}

void loop(){
  bot.update();

  if(bot.servo.getAngle(ServoPin::Name::SRV1) == 0){
    bot.servo.setAngle(ServoPin::Name::SRV1, 180);
  } 
  
  if(bot.servo.getAngle(ServoPin::Name::SRV1) == 180){
    bot.servo.setAngle(ServoPin::Name::SRV1, 0);
  }

}