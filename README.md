# KBot

Библиотека для образовательного робототехнического конструктора.
![Preferences](img/img0.png)

## Содержание

- [Установка и настройка Arduino IDE](#установка-и-настройка-arduino-ide)
  - [Установка](#установка)
  - [Добавление плат ESP32 и M5Stack](#добавление-плат-esp32-и-m5stack)
- [API](#api)
  - [Инициализация](#инициализация)
  - [Ультразвуковой датчик расстояния (Sonic)](#ультразвуковой-датчик-расстояния-sonic)
  - [Датчик расстояния ToF](#датчик-расстояния-tof-time-of-flight)
  - [Датчик угла](#датчик-угла-angle-sensor)
  - [Кнопки и концевые выключатели](#кнопки-и-концевые-выключатели-switch)
  - [Моторы](#моторы-wheels)
  - [Сервоприводы](#сервоприводы-servo)
  - [Светодиоды платы](#светодиоды-платы-mboard-led)
  - [OLED дисплей](#oled-дисплей)
  - [Сенсорные кнопки экрана](#сенсорные-кнопки-экрана-sensor-button)
  - [Таймеры](#таймеры-timer)
  - [Таблица совместимости датчиков и разъемов](#таблица-совместимости-датчиков-и-разъемов)
- [Лицензия](#лицензия)

## Установка и настройка Arduino IDE

### Установка

1. Скачать Arduino IDE 2.x с официального сайта: https://www.arduino.cc/en/software
2. Установить согласно инструкциям для вашей ОС

### Добавление плат ESP32 и M5Stack

1. Открыть Arduino IDE
2. Перейти в `File` → `Preferences
    
    ![Preferences](img/img1.png)
3. В поле `Additional Boards Manager URLs` вставить ссылку:
   https://static-cdn.m5stack.com/resource/arduino/package_m5stack_index.json  

    ![Preferences](img/img2.png)
4. Открыть `Tools` → `Board` → `Boards Manager`
5. Найти и установить:
   - `M5Stack` версия `2.1.4`

   ![Preferences](img/img3.png)
    - `esp32` версия `2.0.17`

   ![Preferences](img/img4.png)
6. TODO архив в библитеками

7. Установка библотеки KBot.
 
    Скопировать папку `KBot` в директорию библиотек Arduino:
   - Windows: `Documents/Arduino/libraries/`
   - macOS: `Documents/Arduino/libraries/`
   - Linux: `~/Arduino/libraries/`
2. Перезапустить Arduino IDE

# API

### Инициализация

```cpp
#include <KBot.h>

KBot bot;

void setup() {
    bot.begin();
}

void loop() {
    bot.update();
}
```

## Ультразвуковой датчик расстояния (Sonic)

**Подключение:** I2C порт

**Методы:**
- `long getDistanceMm()` - Получить расстояние до объекта в миллиметрах

## Датчик расстояния ToF (Time-of-Flight)

**Подключение:** I2C порт

**Методы:**
- `int getDistance()` - Получить расстояние до объекта в миллиметрах

## Датчик угла (Angle Sensor)

**Подключение:** Разъемы XP8, XP9, XP10, XP11

**Доступные объекты:** `angleSensor1`, `angleSensor2`, `angleSensor3`, `angleSensor4`

**Методы:**
- `void begin(Pins::Name pin)` - Инициализация датчика на указанном разъеме
- `int getAngle()` - Получить угол поворота в градусах (0-180)

## Кнопки и концевые выключатели (Switch)

**Подключение:** Разъемы XP8, XP9, XP10, XP11, XP13

**Доступные объекты:**
- `button1`, `button2` - кнопки
- `limitSwitch1`, `limitSwitch2` - концевые выключатели

**Методы:**
- `void begin(Pins::Name pin)` - Инициализация на указанном разъеме с подтяжкой
- `bool isPressed()` - Возвращает true один раз при нажатии
- `bool isReleased()` - Возвращает true один раз при отпускании
- `bool isHeld()` - Возвращает true пока кнопка удерживается

## Моторы (Wheels)

**Подключение:** Встроенные разъемы моторов XP14A, XP15A, XP14B, XP15B

**Методы:**
- `void drive(int left, int right)` - Управление левыми и правыми моторами (-200...200)
- `void drive(Wheel::Name motor, int speed)` - Управление отдельным мотором (-200...200)
- `void stop(Wheel::Name motor)` - Остановить один мотор
- `void stopAll()` - Остановить все моторы

**Константы моторов:**
- `Wheel::XP14A`
- `Wheel::XP15A`
- `Wheel::XP14B`
- `Wheel::XP15B`

## Сервоприводы (Servo)

**Подключение:** Разъемы SRV1, SRV2, SRV3, SRV4

**Методы:**
- `void setAngle(Servos::Name servo, int angle)` - Установить угол сервопривода (0-180)
- `int getAngle(Servos::Name servo)` - Получить текущий угол сервопривода
- `void goHome()` - Вернуть все сервоприводы в начальное положение (90°)

**Константы сервоприводов:**
- `Servos::SRV1` - Разъем SRV1 (GPIO 2)
- `Servos::SRV2` - Разъем SRV2 (GPIO 4)
- `Servos::SRV3` - Разъем SRV3 (GPIO 19)
- `Servos::SRV4` - Разъем SRV4 (GPIO 12)

## Светодиоды платы (MBoard LED)

**Подключение:** Встроенные светодиоды DA9, DA14, DA20, DA26

**Методы:**
- `void color(Led::Name led, int red, int green, int blue)` - Установить RGB цвет светодиода (0-255)
- `void color(Led::Name led, Led::Color color)` - Установить цвет из предустановленных
- `void colorAll(Led::Color color)` - Установить цвет всех светодиодов
- `void off(Led::Name led)` - Выключить один светодиод
- `void offAll()` - Выключить все светодиоды

**Константы светодиодов:**
- `Led::DA9`, `Led::DA14`, `Led::DA20`, `Led::DA26`

**Предустановленные цвета:**
- `Led::RED`, 
- `Led::GREEN`, 
- `Led::BLUE`
- `Led::YELLOW`, 
- `Led::CYAN`, 
- `Led::MAGENTA`
- `Led::BLACK` (выключен)

## OLED дисплей

**Подключение:** I2C порт

**Методы:**
- `void printStr1(...)` - Вывод данных в строку 1
- `void printStr2(...)` - Вывод данных в строку 2
- `void printStr3(...)` - Вывод данных в строку 3
- `void printStr4(...)` - Вывод данных в строку 4
- `void clear()` - Очистить дисплей

**Что можно выводить:**
Все функции `printStr1`, `printStr2`, `printStr3`, `printStr4` умеют выводить:
- Текст: `oled.printStr1("Привет")`
- Целые числа: `oled.printStr2(123)`
- Большие числа: `oled.printStr3(987654L)`
- Дробные числа: `oled.printStr4(3.14)` или `oled.printStr4(3.14159, 3)` (3 цифры после запятой)

**Пример:**
```cpp
int distance = 42;
float temperature = 23.5;

oled.printStr1("Датчик:");
oled.printStr2(distance);           // выведет: 42
oled.printStr3(temperature);        // выведет: 23.50
oled.printStr4(temperature, 1);     // выведет: 23.5
```

## Сенсорные кнопки экрана (Sensor Button)

**Подключение:** Встроенные в экран M5Stack

**Доступные объекты:** `sensorBTN1`, `sensorBTN2`, `sensorBTN3`, `sensorBTN4`

**Методы:**
- `void setText(const char* text)` - Установить текст на кнопке
- `bool isClick()` - Проверить нажатие кнопки

## Таймеры (Timer)

**Доступные объекты:** `timer1`, `timer2`, `timer3`, `timer4`

**Методы:**
- `void startOnce(uint32_t ms)` - Запустить однократный таймер
- `void startEvery(uint32_t ms)` - Запустить периодический таймер
- `void stop()` - Остановить таймер
- `void reset()` - Сбросить таймер
- `bool isReady()` - Проверить готовность таймера (сработал)
- `bool isActive()` - Проверить активен ли таймер
- `bool isDone()` - Проверить завершен ли таймер

## Таблица совместимости датчиков и разъемов

| Датчик/Устройство | Разъемы |
|------------------|---------|
| Ultrasonic Sensor | I2C |
| ToF Sensor | I2C |
| Angle Sensor | XP8, XP9, XP10, XP11, XP12, XP13 |
| Button/Limit Switch | XP8, XP9, XP10, XP11, XP12, XP13 |
| OLED Display | I2C |
| Servo | SRV1, SRV2, SRV3, SRV4 |
| Motors | XP14A, XP15A, XP14B, XP15B (встроенные) |
| LED | DA9, DA14, DA20, DA26 (встроенные) |
| Sensor Buttons | Встроенные в экран |

## Лицензия

Образовательный проект Kobak
