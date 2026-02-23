#include <KBot.h>

KBot bot;

Led::Color colors[6] = {
  Led::Color::RED,
  Led::Color::GREEN,
  Led::Color::BLUE,
  Led::Color::YELLOW,
  Led::Color::CYAN,
  Led::Color::MAGENTA
};

int offset = 0;

void setup() {
  bot.begin();
  bot.rgbLed.begin(Pins::Name::XP11, 6);
  bot.rgbLed.setBrightness(125);
  bot.timer1.startEvery(200);
}

void loop() {
  bot.update();

  if (bot.timer1.isReady()) {
    for (int i = 0; i < bot.rgbLed.getNumLeds(); i++) {
      int colorIndex = (i + offset) % 6;
      bot.rgbLed.setColor(i + 1, colors[colorIndex]);
    }
    offset = (offset + 1) % 6;
  }
}