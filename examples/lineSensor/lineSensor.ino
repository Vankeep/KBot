#include <KBot.h>

KBot bot;

bool isSens1;
bool isSens2;
bool isOledUpdate;

void setup(){
    bot.begin();
    bot.lineSensor1.begin(Pins::Name::XP8);
    bot.lineSensor2.begin(Pins::Name::XP11);
    bot.oled.printStr1("XP8 | XP11");
}

void loop(){
    bot.update();

    if(bot.lineSensor1.isOnLine() != isSens1){
        isSens1 = !isSens1;
        isOledUpdate = true;
    }

    if(bot.lineSensor2.isOnLine() != isSens2){
        isSens2 = !isSens2;
        isOledUpdate = true;
    }

    if(isOledUpdate){
        bot.oled.printStr2(String(isSens1) + "   | " + String(isSens2));
        isOledUpdate = false;
    }
}