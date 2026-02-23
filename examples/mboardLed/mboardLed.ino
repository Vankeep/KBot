#include <KBot.h>

KBot bot;

bool isKbotGo;

void setup(){
    bot.begin();
}

void loop(){
    bot.update();
    bot.mboardLed.color(Led::Name::DA9, Led::Color::RED);
}