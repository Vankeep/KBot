#include <KBot.h>

KBot bot;

bool isOn;

void setup(){
    bot.begin();
    bot.timer1.startOnce(3000);
    bot.kbotBoardLed.colorAll(Led::Color::GREEN);
    isOn = false;
}

void loop(){
    bot.update();

    if(bot.timer1.isDone()) {
        bot.timer1.stop();
        bot.timer2.startEvery(500);
    }
    
    if(bot.timer2.isReady()){
        if(isOn){
            bot.kbotBoardLed.colorAll(Led::Color::BLACK);
        } else {
            bot.kbotBoardLed.colorAll(Led::Color::MAGENTA);
        }
        isOn = !isOn;
    }
}