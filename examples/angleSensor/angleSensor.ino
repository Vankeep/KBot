#include <KBot.h>

KBot bot;

uint8_t servoName;
String name;

void setup(){
  bot.begin();
  bot.angleSensor1.begin(Connector::Name::XP9);

  name = "SRV1";
  servoName = ServoPins::Name::SRV1;

  bot.sensorBTN1.setText("SRV1");
  bot.sensorBTN2.setText("SRV2");
  bot.sensorBTN3.setText("SRV3");
  bot.sensorBTN4.setText("SRV4");
}

void loop(){
  bot.update();

  if(bot.sensorBTN1.isClick()){
    name = "SRV1";
    servoName = ServoPins::Name::SRV1;
  } else if(bot.sensorBTN2.isClick()){
    name = "SRV2";
    servoName = ServoPins::Name::SRV2;
  } else if(bot.sensorBTN3.isClick()){
    name = "SRV3";
    servoName = ServoPins::Name::SRV3;
  } else if(bot.sensorBTN4.isClick()){
    name = "SRV4";
    servoName = ServoPins::Name::SRV4;
  }

  int angle1 = bot.angleSensor1.getAngle();
  bot.servo.setAngle(ServoPins::getName(servoName), angle1);
  bot.oled.printStr1(name + " = " + String(angle1) + " gradus");
}