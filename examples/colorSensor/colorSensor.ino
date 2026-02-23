#include <KBot.h>

KBot bot;

void setup() {
    bot.begin();
    // Калибловка при включении по белому листу
    bot.colorSensor.calibrateWhite();
    
    bot.timer1.startEvery(500);
}

void loop() {
    bot.update();

    if (bot.timer1.isReady()) {
        int r, g, b;
        bot.colorSensor.getRGB(r, g, b);

        const char* color = "???";
        if      (bot.colorSensor.isRed(r, g, b))   color = "RED";
        else if (bot.colorSensor.isGreen(r, g, b)) color = "GREEN";
        else if (bot.colorSensor.isBlue(r, g, b))  color = "BLUE";
        else if (bot.colorSensor.isWhite(r, g, b)) color = "WHITE";
        else if (bot.colorSensor.isBlack(r, g, b)) color = "BLACK";

        char buf[32];
        snprintf(buf, sizeof(buf), "%s %d %d %d", color, r, g, b);
        bot.oled.printStr1(buf);
    }
}