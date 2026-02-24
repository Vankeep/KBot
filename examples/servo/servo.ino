#include <KBot.h>

KBot bot;

void setup(){
  bot.begin();
  bot.servo.setAngle(ServoPins::Name::SRV1, 0);
}

void loop(){
  bot.update();

  if(bot.servo.getAngle(ServoPins::Name::SRV1) == 0){
    bot.servo.setAngle(ServoPins::Name::SRV1, 180);
  } 
  
  if(bot.servo.getAngle(ServoPins::Name::SRV1) == 180){
    bot.servo.setAngle(ServoPins::Name::SRV1, 0);
  }

}