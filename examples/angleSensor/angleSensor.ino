/*
 * Пример использования датчика угла для управления серводвигателями
 *
 * Подключение:
 * 1. Подключите датчик угла к разъему XP9
 * 2. Подключите серводвигатели к портам SRV1, SRV2, SRV3, SRV4
 * 3. Загрузите скетч на M5Stack Core2
 * 4. Выберите нужный сервопривод кнопками на экране
 * 5. Вращайте датчик угла для управления выбранным сервоприводом
 */

#include <KBot.h>  // Подключаем библиотеку для работы с роботом KBot

KBot bot;  // Создаем объект робота

String name;  // Переменная для хранения имени выбранного сервопривода (например, "SRV1")
int servoNum;  // Номер выбранного сервопривода (1, 2, 3 или 4)

void setup(){
  bot.begin();  // Инициализируем робота (запускаем все датчики и моторы)
  
  // Инициализируем датчик угла к разъему XP9
  // Датчик угла возвращает значение от 0 до 360 градусов в зависимости от положения ручки
  bot.angleSensor1.begin(Connector::Name::XP9);

  // Инициализируем все четыре сервопривода
  // SRV1, SRV2, SRV3, SRV4 - порты для подключения серводвигателей на плате KBot
  bot.servo1.begin(ServoPin::Name::SRV1);
  bot.servo2.begin(ServoPin::Name::SRV2);
  bot.servo3.begin(ServoPin::Name::SRV3);
  bot.servo4.begin(ServoPin::Name::SRV4);

  // Устанавливаем начальные значения - выбран первый сервопривод
  name = "SRV1";
  servoNum = 1;

  // Устанавливаем текст на экранные кнопки для выбора сервопривода
  // sensorBTN1-4 - это сенсорные кнопки на экране M5Stack
  bot.sensorBTN1.setText("SRV1");
  bot.sensorBTN2.setText("SRV2");
  bot.sensorBTN3.setText("SRV3");
  bot.sensorBTN4.setText("SRV4");
}

void loop(){
  bot.update();  // Обновляем состояние всех датчиков и кнопок (вызываем каждый цикл!)

  // Проверяем нажатия на экранные кнопки для выбора сервопривода
  // isClick() возвращает true один раз в момент нажатия кнопки
  if(bot.sensorBTN1.isClick()){
    name = "SRV1";  // Запоминаем имя выбранного привода
    servoNum = 1;   // Запоминаем номер выбранного привода
  } else if(bot.sensorBTN2.isClick()){
    name = "SRV2";
    servoNum = 2;
  } else if(bot.sensorBTN3.isClick()){
    name = "SRV3";
    servoNum = 3;
  } else if(bot.sensorBTN4.isClick()){
    name = "SRV4";
    servoNum = 4;
  }

  // Считываем угол поворота датчика угла (значение от 0 до 360 градусов)
  int angle1 = bot.angleSensor1.getAngle();

  // Устанавливаем угол того сервопривода, который выбран
  // Сервопривод получит значение угла от 0 до 180 градусов
  // Если датчик угла возвращает больше 180, сервопривод всё равно получит максимум 180
  if(servoNum == 1){
    bot.servo1.setAngle(angle1);
  } else if(servoNum == 2){
    bot.servo2.setAngle(angle1);
  } else if(servoNum == 3){
    bot.servo3.setAngle(angle1);
  } else if(servoNum == 4){
    bot.servo4.setAngle(angle1);
  }

  // Выводим на экран имя выбранного сервопривода и текущий угол датчика
  bot.oled.printStr1(name + " = " + String(angle1) + " gradus");
}