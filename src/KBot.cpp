/*
* Copyright (C) 2026 KobakLab
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*/
#include "KBot.h"
#include "state.h"

void KBot::begin() {
    Wire.begin();
    _serialController.init();
    _initConnection();
    auto cfg = M5.config();
    cfg.serial_baudrate = SERIAL_PROTOCOL_BAUD;
    M5.begin(cfg);
    delay(2500);

    M5.Lcd.fillScreen(TFT_BLACK);
    sensorBTN1.init(0);
    sensorBTN2.init(1);
    sensorBTN3.init(2);
    sensorBTN4.init(3);
    oled.begin();

    ultrasonic.begin();

    timer1.begin();
    timer2.begin();
    timer3.begin();
    timer4.begin();

    tof.begin();

    if(colorSensor.begin()){
        LOG_INFO("ColorSensor подключен и проинициализирован");
    } else {
        LOG_INFO("ColorSensor не обнаружен на шине I2C");
    }
        
    if(imu.begin()){
        LOG_INFO("IMU Sensor подключен и проинициализирован");
    } else {
        LOG_INFO("IMU Sensor не обнаружен на шине I2C");
    }

    
    
    State::init();
}

void KBot::update() {

    timer1.update();
    timer2.update();
    timer3.update();
    timer4.update();

    button1.tick();
    button2.tick();
    limitSwitch1.tick();
    limitSwitch2.tick();

    lineSensor1.tick();
    lineSensor2.tick();
    lineSensor3.tick();
    lineSensor4.tick();

    rgbLed.tick();

    buzzer.tick();

    imu.tick();

    _initConnection();

    M5.update();
    
    _serialController.update();
    State::flush();
#ifdef SERIAL_STATE_DEBUG
    State::printState();
#endif
}

void KBot::_initConnection() {
    Wire.beginTransmission(0x20);
    Wire.write((uint8_t)0x03);
    Wire.write((uint8_t)0x00);
    Wire.endTransmission();

    Wire.beginTransmission(0x20);
    Wire.write((uint8_t)0x01);
    Wire.write((uint8_t)0x80);
    Wire.endTransmission();
}