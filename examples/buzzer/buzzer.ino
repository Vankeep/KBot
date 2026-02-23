#include <KBot.h>

KBot bot;

// мелодия марио
int mario[] = {
    659, 659,   0, 659,   0, 523, 659,   0, 784,   0,   0, 392
//   Ми   Ми       Ми        До   Ми        Соль           Соль
};
int marioLength = 12;  // сколько нот в мелодии
int noteIndex = 0;      // какую ноту сейчас играем
bool melodyDone = false; // мелодия закончилась?

void setup() {
    bot.begin();
    bot.buzzer.begin(Pins::Name::XP11);

    //три ноты вверх
    bot.buzzer.tone(1000, 100);
    delay(150);
    bot.buzzer.tone(1500, 100);
    delay(150);
    bot.buzzer.tone(2000, 300);
    delay(500);

    bot.timer1.startEvery(200);
}

void loop() {
    bot.update();

    //каждые 200 мсек играем след ноту
    if(bot.timer1.isReady() && melodyDone == false) {

        if(noteIndex < marioLength) {
            // если 0 пауза, иначе — играем ноту
            if(mario[noteIndex] == 0) {
                bot.buzzer.noTone();
            } else {
                bot.buzzer.tone(mario[noteIndex], 150);
            }
            noteIndex++;
        } else {
            bot.buzzer.noTone();
            melodyDone = true;
        }
    }
}