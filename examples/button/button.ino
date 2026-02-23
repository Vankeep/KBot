#include <KBot.h>

KBot bot;

void setup(){
    bot.begin();
    bot.button1.begin(Pins::Name::XP8);
}

void loop(){
    bot.update();

    bool isPressed = bot.button1.isPressed();
    bool isReleased = bot.button1.isReleased();
    bool isHeld = bot.button1.isHeld();

    if(isPressed) bot.timer1.startOnce(100);
    if(isReleased) bot.timer2.startOnce(100);

    bot.oled.printStr1(bot.timer1.isActive() ? "isPressed" : "");
    bot.oled.printStr2(bot.timer2.isActive() ? "isReleased" : "");
    bot.oled.printStr3(isHeld ? "isHeld" : "");

    if(bot.timer1.isDone()) bot.timer1.stop();
    if(bot.timer2.isDone()) bot.timer2.stop();
}