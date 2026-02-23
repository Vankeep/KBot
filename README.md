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

## Инициализация

Каждая программа для робота начинается с этого кода:

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

**Важно:** В функции `loop()` обязательно вызывайте `bot.update()` в начале!

---

## Ультразвуковой датчик расстояния

Измеряет расстояние до объекта с помощью ультразвука (как у летучих мышей).

**Подключение:** I2C порт

**Объект:** `ultrasonic`

**Методы:**
- `long getDistanceMm()` - Получить расстояние до объекта в миллиметрах

**Пример использования:** `sonar.ino`

```cpp
void loop() {
    bot.update();
    int mm = bot.ultrasonic.getDistanceMm();
    bot.oled.printStr1("Dist = " + String(mm) + " mm");
}
```

---

## Датчик расстояния ToF (Time-of-Flight)

Более точный датчик расстояния, использует лазер.

**Подключение:** I2C порт

**Объект:** `tof`

**Методы:**
- `void begin(uint8_t address = 0x29)` - Инициализация датчика (адрес по умолчанию 0x29)
- `long getDistanceMm()` - Получить расстояние до объекта в миллиметрах

**Пример использования:** `tof.ino`

```cpp
void setup() {
    bot.begin();
    // begin() вызывать не обязательно, датчик работает по умолчанию
}

void loop() {
    bot.update();
    int mm = bot.tof.getDistanceMm();
    bot.oled.printStr1("tof distance = " + String(mm) + " mm");
}
```

---

## Датчик угла

Датчик поворота (потенциометр), который измеряет угол от 0 до 180 градусов.

**Подключение:** Разъемы XP8, XP9, XP10, XP11

**Доступные объекты:** `angleSensor1`, `angleSensor2`, `angleSensor3`, `angleSensor4`

**Методы:**
- `void begin(Pins::Name pin)` - Инициализация датчика на указанном разъеме
- `int getAngle()` - Получить угол поворота в градусах (0-180)

**Пример использования:** `angleSensor.ino`

```cpp
void setup() {
    bot.begin();
    bot.angleSensor1.begin(Pins::Name::XP9);
}

void loop() {
    bot.update();
    int angle = bot.angleSensor1.getAngle();
    bot.servo.setAngle(Servos::SRV1, angle);
}
```

---

## Кнопки и концевые выключатели

Датчики нажатия. Кнопка нажимается пальцем, концевой выключатель срабатывает при столкновении.

**Подключение:** Разъемы XP8, XP9, XP10, XP11, XP13

**Доступные объекты:**
- `button1`, `button2` - обычные кнопки
- `limitSwitch1`, `limitSwitch2` - концевые выключатели

**Методы:**
- `void begin(Pins::Name pin, bool pullUp = true)` - Инициализация на указанном разъеме
- `bool isPressed()` - Возвращает true один раз при нажатии
- `bool isReleased()` - Возвращает true один раз при отпускании
- `bool isHeld()` - Возвращает true пока кнопка удерживается

**Пример использования:** `button.ino`

```cpp
void setup() {
    bot.begin();
    bot.button1.begin(Pins::Name::XP8);
}

void loop() {
    bot.update();

    if (bot.button1.isPressed()) {
        bot.oled.printStr1("isPressed");
    }

    if (bot.button1.isHeld()) {
        bot.oled.printStr2("isHeld");
    }
}
```

---

## Датчик линии

Датчик для обнаружения черной линии на белом фоне (или наоборот).

**Подключение:** Разъемы XP8, XP10, XP11, XP13

**Доступные объекты:** `lineSensor1`, `lineSensor2`, `lineSensor3`, `lineSensor4`

**Методы:**
- `void begin(Pins::Name pin)` - Инициализация датчика на указанном разъеме
- `bool isOnLine()` - Возвращает true, если датчик видит линию
- `bool isDetected()` - Возвращает true один раз при обнаружении линии
- `bool isLost()` - Возвращает true один раз при потере линии

**Пример использования:** `lineSensor.ino`

```cpp
void setup() {
    bot.begin();
    bot.lineSensor1.begin(Pins::Name::XP8);
    bot.lineSensor2.begin(Pins::Name::XP11);
}

void loop() {
    bot.update();

    bool line1 = bot.lineSensor1.isOnLine();
    bool line2 = bot.lineSensor2.isOnLine();

    bot.oled.printStr1(String(line1) + " | " + String(line2));
}
```

---

## Датчик цвета

Датчик для распознавания цветов: красный, зеленый, синий, белый, черный.

**Подключение:** I2C порт

**Объект:** `colorSensor`

**Методы:**
- `void begin(uint8_t address = 0x29)` - Инициализация датчика (адрес по умолчанию 0x29)
- `void calibrateWhite()` - Калибровка по белому листу (вызывать при включении!)
- `void getRGB(int &r, int &g, int &b)` - Получить значения RGB цвета
- `bool isRed(int r, int g, int b)` - Проверить, красный ли это цвет
- `bool isGreen(int r, int g, int b)` - Проверить, зеленый ли это цвет
- `bool isBlue(int r, int g, int b)` - Проверить, синий ли это цвет
- `bool isWhite(int r, int g, int b)` - Проверить, белый ли это цвет
- `bool isBlack(int r, int g, int b)` - Проверить, черный ли это цвет

**Пример использования:** `colorSensor.ino`

```cpp
void setup() {
    bot.begin();
    bot.colorSensor.calibrateWhite(); // Калибровка по белому!
}

void loop() {
    bot.update();

    int r, g, b;
    bot.colorSensor.getRGB(r, g, b);

    if (bot.colorSensor.isRed(r, g, b)) {
        bot.oled.printStr1("RED");
    } else if (bot.colorSensor.isGreen(r, g, b)) {
        bot.oled.printStr1("GREEN");
    }
}
```

---

## Моторы

Управление колесами робота. Скорость от -200 (назад) до 200 (вперед).

**Подключение:** Встроенные разъемы моторов XP14A, XP15A, XP14B, XP15B

**Объект:** `wheel`

**Методы:**
- `void drive(int left, int right)` - Управление левыми и правыми моторами (-200...200)
- `void drive(Wheel::Name motor, int speed)` - Управление отдельным мотором (-200...200)
- `void stop(Wheel::Name motor)` - Остановить один мотор
- `void stopAll()` - Остановить все моторы

**Пример использования:** `wheel.ino`

```cpp
void loop() {
    bot.update();

    // Оба мотора вперед на скорости 50
    bot.wheel.drive(50, 50);

    // Или управление отдельными моторами
    bot.wheel.drive(Wheel::Name::XP14A, 50);
    bot.wheel.drive(Wheel::Name::XP15A, -50);
}
```

---

## Сервоприводы

Моторчики, которые поворачиваются на заданный угол от 0 до 180 градусов.

**Подключение:** Разъемы SRV1, SRV2, SRV3, SRV4

**Объект:** `servo`

**Методы:**
- `void setAngle(Servos::Name servo, int angle)` - Установить угол сервопривода (0-180)
- `int getAngle(Servos::Name servo)` - Получить текущий угол сервопривода
- `void goHome()` - Вернуть все сервоприводы в начальное положение (90°)

**Пример использования:** `servo.ino`

```cpp
void setup() {
    bot.begin();
    bot.servo.setAngle(Servos::Name::SRV1, 0);
}

void loop() {
    bot.update();

    if (bot.servo.getAngle(Servos::SRV1) == 0) {
        bot.servo.setAngle(Servos::SRV1, 180);
    } else {
        bot.servo.setAngle(Servos::SRV1, 0);
    }
}
```

---

## Светодиоды платы

4 встроенных RGB светодиода на плате управления.

**Подключение:** Встроенные светодиоды DA9, DA14, DA20, DA26

**Объект:** `mboardLed`

**Методы:**
- `void color(Led::Name led, int red, int green, int blue)` - Установить RGB цвет (0-255 для каждого цвета)
- `void color(Led::Name led, Color::Name color)` - Установить цвет из готовых
- `void colorAll(Color::Name color)` - Установить цвет всех светодиодов
- `void off(Led::Name led)` - Выключить один светодиод
- `void offAll()` - Выключить все светодиоды

**Готовые цвета:** `Led::Color::RED`, `Led::Color::GREEN`, `Led::Color::BLUE`, `Led::Color::YELLOW`, `Led::Color::CYAN`, `Led::Color::MAGENTA`, `Led::Color::BLACK`

**Пример использования:** `mboardLed.ino`

```cpp
void loop() {
    bot.update();

    // Зажечь один светодиод красным
    bot.mboardLed.color(Led::Name::DA9, Led::Color::RED);

    // Или задать свой цвет (красный, зеленый, синий)
    bot.mboardLed.color(Led::Name::DA14, 255, 0, 128);

    // Зажечь все светодиоды
    bot.mboardLed.colorAll(Led::Color::GREEN);
}
```

---

## RGB светодиодная лента

Управление RGB светодиодной лентой (адресные светодиоды WS2812).

**Подключение:** Разъемы XP8, XP9, XP10, XP11, XP12, XP13

**Объект:** `rgbLed`

**Методы:**
- `void begin(Pins::Name pin, int numLeds = 3)` - Инициализация ленты (указать пин и количество светодиодов)
- `void setColor(int pixel, int r, int g, int b)` - Установить цвет одного светодиода (0-255 для каждого цвета)
- `void setColor(int pixel, Color::Name color)` - Установить готовый цвет
- `void setColorAll(int r, int g, int b)` - Установить цвет всех светодиодов
- `void setColorAll(Color::Name color)` - Установить готовый цвет для всех
- `void setBrightness(int brightness)` - Установить яркость (0-255)
- `void clear()` - Выключить все светодиоды
- `int getNumLeds()` - Получить количество светодиодов

**Готовые цвета:** `Led::Color::RED`, `Led::Color::GREEN`, `Led::Color::BLUE`, `Led::Color::YELLOW`, `Led::Color::CYAN`, `Led::Color::MAGENTA`, `Led::Color::BLACK`

**Пример использования:** `rgbLed.ino`

```cpp
void setup() {
    bot.begin();
    bot.rgbLed.begin(Pins::Name::XP11, 6); // 6 светодиодов на пине XP11
}

void loop() {
    bot.update();

    // Зажечь первый светодиод красным
    bot.rgbLed.setColor(0, Led::Color::RED);

    // Зажечь все светодиоды синим
    bot.rgbLed.setColorAll(0, 0, 255);
}
```

---

## OLED дисплей

Экран для вывода текста и чисел (4 строки).

**Подключение:** I2C порт

**Объект:** `oled`

**Методы:**
- `void printStr1(...)` - Вывод данных в строку 1
- `void printStr2(...)` - Вывод данных в строку 2
- `void printStr3(...)` - Вывод данных в строку 3
- `void printStr4(...)` - Вывод данных в строку 4
- `void clear()` - Очистить весь дисплей

**Что можно выводить:**

Все функции `printStr1-4` умеют выводить:
- Текст: `bot.oled.printStr1("Привет")`
- Целые числа: `bot.oled.printStr2(123)`
- Большие числа: `bot.oled.printStr3(987654L)`
- Дробные числа: `bot.oled.printStr4(3.14)` или с указанием точности `bot.oled.printStr4(3.14159, 3)`

**Пример:**

```cpp
int distance = 42;
float temperature = 23.5;

bot.oled.printStr1("Датчик:");
bot.oled.printStr2(distance);           // выведет: 42
bot.oled.printStr3(temperature);        // выведет: 23.50
bot.oled.printStr4(temperature, 1);     // выведет: 23.5
```

---

## Сенсорные кнопки экрана M5Stack

4 кнопки на сенсорном экране M5Stack. На них можно вывести текст.

**Подключение:** Встроенные в экран M5Stack

**Доступные объекты:** `sensorBTN1`, `sensorBTN2`, `sensorBTN3`, `sensorBTN4`

**Методы:**
- `void setText(const char* text)` - Установить текст на кнопке
- `bool isClick()` - Проверить, нажата ли кнопка (возвращает true один раз при нажатии)

**Пример использования:** `sensorButton.ino`

```cpp
void setup() {
    bot.begin();
    bot.sensorBTN1.setText("START");
    bot.sensorBTN2.setText("STOP");
}

void loop() {
    bot.update();

    if (bot.sensorBTN1.isClick()) {
        bot.wheel.drive(50, 50);
    }

    if (bot.sensorBTN2.isClick()) {
        bot.wheel.stopAll();
    }
}
```

---

## Таймеры

Таймеры для отсчета времени. Можно запустить на одно срабатывание или повторяющийся.

**Доступные объекты:** `timer1`, `timer2`, `timer3`, `timer4`

**Методы:**
- `void startOnce(uint32_t ms)` - Запустить таймер на один раз (время в миллисекундах)
- `void startEvery(uint32_t ms)` - Запустить повторяющийся таймер (время в миллисекундах)
- `void stop()` - Остановить таймер
- `void reset()` - Сбросить таймер
- `bool isReady()` - Проверить, сработал ли таймер (true один раз при срабатывании)
- `bool isActive()` - Проверить, работает ли таймер
- `bool isDone()` - Проверить, завершился ли таймер

**Пример использования:** `timer.ino`

```cpp
void setup() {
    bot.begin();
    bot.timer1.startOnce(3000);  // Запустить на 3 секунды
}

void loop() {
    bot.update();

    if (bot.timer1.isDone()) {
        bot.timer1.stop();
        bot.timer2.startEvery(500);  // Повторять каждые 0.5 секунды
    }

    if (bot.timer2.isReady()) {
        // Этот код выполнится каждые 0.5 секунды
        bot.mboardLed.colorAll(Color::RED);
    }
}
```

---

## Таблица совместимости датчиков и разъемов

| Датчик/Устройство | Разъемы подключения |
|------------------|---------------------|
| Ультразвуковой датчик | I2C |
| ToF датчик расстояния | I2C |
| Датчик цвета | I2C |
| OLED дисплей | I2C |
| Датчик угла | XP8, XP9, XP10, XP11 |
| Кнопка / Концевой выключатель | XP8, XP9, XP10, XP11, XP13 |
| Датчик линии | XP8, XP10, XP11, XP13 |
| RGB светодиодная лента | XP8, XP9, XP10, XP11, XP12, XP13 |
| Сервопривод | SRV1, SRV2, SRV3, SRV4 |
| Моторы | XP14A, XP15A, XP14B, XP15B (встроенные) |
| Светодиоды платы | DA9, DA14, DA20, DA26 (встроенные) |
| Сенсорные кнопки | Встроенные в экран M5Stack |

## Лицензия

Образовательный проект Kobak