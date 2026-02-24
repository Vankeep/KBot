# Установка и настройка Arduino IDE для работы с библотекой KBot

## Установка Arduino IDE

1. Скачайте Arduino IDE версии 2.x с официального сайта: https://www.arduino.cc/en/software
2. Установите согласно инструкциям для вашей ОС

## Добавление платы M5Stack

1. Откройте Arduino IDE
2. Перейдите в `File` → `Preferences`

![Preferences](img/img1.png)

3. В поле `Additional Boards Manager URLs` вставьте ссылку:
   ```
   https://static-cdn.m5stack.com/resource/arduino/package_m5stack_index.json
   ```

![Preferences](img/img2.png)

4. Откройте `Tools` → `Board` → `Boards Manager`
5. Найдите и установите:

   - `M5Stack` версия `2.1.4`

![Preferences](img/img4.png)
   
## Установка библиотеки M5
1. Слева нажмите на "Library Manager"
2. В строке поиска введите `M5Unified`
3. Выберите версию `0.2.13`
4. Нажмите **INSTALL**


![Preferences](img/img5.png)

В появившемся окне нажать **INSTALL ALL**

![Preferences](img/img6.png)

## Установка библиотеки KBot
Открыть https://github.com/Vankeep/KBot

1. Нажмите кнопку **Code**
2. Выберите **Download ZIP**


![Preferences](img/img7.png)

Сохраните в загрузки.

Откройте Arduino IDE. Далее `Sketch` → `Include Library` → `Add .ZIP Library`

![Preferences](img/img8.png)

## Финальная настройка

Для того чтобы прошить M5Core2 необходимо выбрать плату в Arduino IDE. 

`Tools` → `Board` → `M5Stack` → `M5Core2`

![Preferences](img/img9.png)

После выбора платы необходимо выбрать порт подключения устройства.

### Способ 1: Использование селектора плат (рекомендуется для IDE 2.x)
1. В верхней части окна Arduino IDE найдите выпадающий список с платами
2. Нажмите на него - отобразится список доступных портов
3. Если плата определена автоматически, рядом с портом будет отображено её название
4. Выберите нужный порт одним кликом

### Способ 2: Через меню Tools
1. Откройте меню `Tools` → `Port`
2. Наведите курсор на `Port` для отображения всех доступных портов
3. Для Arduino устройств обычно отображается название платы после порта
4. Нажмите на нужный порт для выбора


**Примечание:** Если в меню `Tools` → `Port` ничего не отображается, это означает что Arduino IDE не обнаружила подключенных устройств. Убедитесь что:
- Устройство подключено к компьютеру через USB-кабель
- Устройство включено
- Установлены необходимые драйверы

Подробнее: https://support.arduino.cc/hc/en-us/articles/4406856349970


**После выполнения всех шагов библиотека KBot будет готова к использованию!**
