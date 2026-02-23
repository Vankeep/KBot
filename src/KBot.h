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
#pragma once
#include "config.h"
#include <M5Unified.h>
#include <Wire.h>
#include "SonicAdapter.h"
#include "WheelsAdapter.h"
#include "SerialController.h"
#include "ServoAdapter.h"
#include "SensorButtonAdapter.h"
#include "OledAdapter.h"
#include "MboardLedAdapter.h"
#include "Timer.h"
#include "AngleSensorAdapter.h"
#include "SwitchAdapter.h"
#include "ToFSensorAdapter.h"
#include "LineSensorAdapter.h"
#include "ColorSensorAdapter.h"
#include "RgbLedAdapter.h"
#include "BuzzerAdapter.h"
#include "ImuSensorAdapter.h"

class KBot {
public:
    SonicAdapter ultrasonic;
    WheelsAdapter wheel;
    ServoAdapter servo;
    SensorButtonAdapter sensorBTN1;
    SensorButtonAdapter sensorBTN2;
    SensorButtonAdapter sensorBTN3;
    SensorButtonAdapter sensorBTN4;
    OledAdapter oled;
    MboardLedAdapter mboardLed;
    Timer timer1;
    Timer timer2;
    Timer timer3;
    Timer timer4;
    AngleSensorAdapter angleSensor1;
    AngleSensorAdapter angleSensor2;
    AngleSensorAdapter angleSensor3;
    AngleSensorAdapter angleSensor4;
    SwitchAdapter button1;
    SwitchAdapter button2;
    SwitchAdapter limitSwitch1;
    SwitchAdapter limitSwitch2;
    ToFSensorAdapter tof;
    LineSensorAdapter lineSensor1;
    LineSensorAdapter lineSensor2;
    LineSensorAdapter lineSensor3;
    LineSensorAdapter lineSensor4;
    ColorSensorAdapter colorSensor;
    RgbLedAdapter rgbLed;
    BuzzerAdapter buzzer;
    ImuSensorAdapter imu;

    void begin();
    void update();
private:
    SerialController _serialController;
    void _initConnection();
};
