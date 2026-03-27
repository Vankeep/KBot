/*
 * Пример использования внешней кнопки для определения нажатий
 *
 * Подключение:
 * 1. Подключите кнопку к разъему XP8
 * 2. Загрузите скетч на M5Stack Core2
 * 3. На экране будут отображаться события: нажатие, отпускание, удержание
 */

#include <KBot.h>  // Подключаем библиотеку для работы с роботом KBot

KBot bot;  // Создаем объект робота

void setup(){
    bot.begin();  // Инициализируем робота
    bot.button1.begin(Connector::Name::XP8);  // Подключаем кнопку к разъему XP8
}

void loop(){
    bot.update();  // Обновляем состояние всех датчиков и кнопок (вызываем каждый цикл!)

    // Проверяем различные события кнопки
    bool isPressed = bot.button1.isPressed();   // true в момент нажатия кнопки (один раз)
    bool isReleased = bot.button1.isReleased(); // true в момент отпускания кнопки (один раз)
    bool isHeld = bot.button1.isHeld();         // true пока кнопка удерживается нажатой

    // Запускаем таймеры для показа событий на экране
    if(isPressed) bot.timer1.startOnce(100);   // Показываем "isPressed" на 100мс
    if(isReleased) bot.timer2.startOnce(100);  // Показываем "isReleased" на 100мс

    // Выводим события на экран (тернарный оператор: условие ? если_true : если_false)
    bot.oled.printStr1(bot.timer1.isActive() ? "isPressed" : "");   // Первая строка
    bot.oled.printStr2(bot.timer2.isActive() ? "isReleased" : "");  // Вторая строка
    bot.oled.printStr3(isHeld ? "isHeld" : "");  // Третья строка

    // Останавливаем таймеры когда они истекли
    if(bot.timer1.isDone()) bot.timer1.stop();
    if(bot.timer2.isDone()) bot.timer2.stop();
}