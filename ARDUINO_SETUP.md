# Установка и настройка Arduino IDE

## Установка Arduino IDE

1. Скачать Arduino IDE 2.x с официального сайта: https://www.arduino.cc/en/software
2. Установить согласно инструкциям для вашей ОС

## Добавление плат ESP32 и M5Stack

1. Открыть Arduino IDE
2. Перейти в `File` → `Preferences`

    ![Preferences](img/img1.png)
3. В поле `Additional Boards Manager URLs` вставить ссылку:
   ```
   https://static-cdn.m5stack.com/resource/arduino/package_m5stack_index.json
   ```

    ![Preferences](img/img2.png)
4. Открыть `Tools` → `Board` → `Boards Manager`
5. Найти и установить:
   - `M5Stack` версия `2.1.4`

   ![Preferences](img/img3.png)
   - `esp32` версия `2.0.17`

   ![Preferences](img/img4.png)
   
## Установка библиотеки M5
1. Слева нажать на "Library Manager"
2. В строке поиска ввести `M5Unified`
3. Выбрать версию `0.2.13`
4. Нажать **INSTALL**

![Preferences](img/img5.png)

В появившемся окне нажать **INSTALL ALL**

![Preferences](img/img6.png)

## Установка библиотеки KBot

1. Скопировать папку `KBot` в директорию библиотек Arduino:
   - Windows: `Documents/Arduino/libraries/`
   - macOS: `Documents/Arduino/libraries/`
   - Linux: `~/Arduino/libraries/`
2. Перезапустить Arduino IDE

После выполнения всех шагов библиотека KBot будет готова к использованию!
