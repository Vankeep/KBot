#include <KBot.h>

KBot bot;

bool isKbotGo;

void setup(){
    bot.begin();

    isKbotGo = false;
    bot.sensorBTN1.setText("KBot GO");
}

void loop(){
    bot.update();

    if (bot.sensorBTN1.isClick()) {
        if(isKbotGo){
            bot.wheel.stopAll();
            bot.sensorBTN1.setText("KBot GO");
            bot.oled.printStr1("Wheels stop");
        } else {
            bot.wheel.drive(50, 50);
            bot.sensorBTN1.setText("KBot STOP");
            bot.oled.printStr1("Wheels drive 50 50 ");
        }

        isKbotGo = !isKbotGo;
    }
}