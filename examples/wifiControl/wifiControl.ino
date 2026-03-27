/*
 * Пример использования WiFi Control Panel для управления роботом с телефона
 *
 * Подключение:
 * 1. Загрузите скетч на M5Stack Core2
 * 2. На телефоне подключитесь к WiFi сети "kbot" (пароль: "12345678")
 * 3. Откройте браузер и перейдите по адресу, показанному на экране M5Stack
 * 4. Используйте джойстик для управления роботом
 */

#include <KBot.h>

KBot bot;

void setup() {
    bot.begin();

    // Инициализация WiFi точки доступа
    bot.wifiControl.begin("kbot", "12345678", IPAddress(10, 0, 0, 1));
    
    // Рисуем на экране данные для подключения и адрес пульта
    bot.oled.printStr1("wifi name:" + String(bot.wifiControl.getSSID()));
    bot.oled.printStr2("wifi password:" + String(bot.wifiControl.getPassword()));
    bot.oled.printStr3("url: http://" + String(bot.wifiControl.getIPAddress()));
}

void loop() {
    bot.update();

    // Получение значений от джойстика
    int left, right;
    bot.wifiControl.getMotorValues(left, right);

    // Управление моторами
    bot.wheel.drive(left, right);
}
