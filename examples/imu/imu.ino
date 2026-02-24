#include <KBot.h>

KBot bot;

void setup() {
    bot.begin();
    bot.timer1.startEvery(100);
}

void loop() {
    bot.update();

    if (bot.timer1.isReady()) {
        int pitch = bot.imu.getPitch();
        int roll  = bot.imu.getRoll();
        int ax    = bot.imu.getAccelX();
        int ay    = bot.imu.getAccelY();
        int az    = bot.imu.getAccelZ();

        char buf[32];

        snprintf(buf, sizeof(buf), "Naklon: %d", pitch);
        bot.oled.printStr1(buf);

        snprintf(buf, sizeof(buf), "Kren:   %d", roll);
        bot.oled.printStr2(buf);

        snprintf(buf, sizeof(buf), "X:%d Y:%d", ax, ay);
        bot.oled.printStr3(buf);

        snprintf(buf, sizeof(buf), "Z:%d", az);
        bot.oled.printStr4(buf);
    }
}