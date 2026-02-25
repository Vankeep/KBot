#include <KBot.h>

KBot bot;

String name;
int servoNum;

void setup(){
  bot.begin();
  bot.angleSensor1.begin(Connector::Name::XP9);

  bot.servo1.begin(ServoPin::Name::SRV1);
  bot.servo2.begin(ServoPin::Name::SRV2);
  bot.servo3.begin(ServoPin::Name::SRV3);
  bot.servo4.begin(ServoPin::Name::SRV4);

  name = "SRV1";
  servoNum = 1;

  bot.sensorBTN1.setText("SRV1");
  bot.sensorBTN2.setText("SRV2");
  bot.sensorBTN3.setText("SRV3");
  bot.sensorBTN4.setText("SRV4");
}

void loop(){
  bot.update();

  if(bot.sensorBTN1.isClick()){
    name = "SRV1";
    servoNum = 1;
  } else if(bot.sensorBTN2.isClick()){
    name = "SRV2";
    servoNum = 2;
  } else if(bot.sensorBTN3.isClick()){
    name = "SRV3";
    servoNum = 3;
  } else if(bot.sensorBTN4.isClick()){
    name = "SRV4";
    servoNum = 4;
  }

  int angle1 = bot.angleSensor1.getAngle();

  if(servoNum == 1){
    bot.servo1.setAngle(angle1);
  } else if(servoNum == 2){
    bot.servo2.setAngle(angle1);
  } else if(servoNum == 3){
    bot.servo3.setAngle(angle1);
  } else if(servoNum == 4){
    bot.servo4.setAngle(angle1);
  }

  bot.oled.printStr1(name + " = " + String(angle1) + " gradus");
}