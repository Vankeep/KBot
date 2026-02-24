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
#include "AngleSensorAdapter.h"
#include <M5Unified.h>
#include <math.h>

void AngleSensorAdapter::begin(Pins::Name name) {
    if(name == Pins::Name::XP9 || name == Pins::Name::XP10 || 
       name == Pins::Name::XP11 || name == Pins::Name::XP8){
        if(_isBegin == true) {
            LOG_ERR("Angle Sensor уже проинициализирован. Повторная инициализация игнорируется");
            return;
        }
        _isBegin = true;
        _pin = Pins::leftPin(name);
        pinMode(_pin, INPUT);
        _lastAngle = 90;
        _candidateAngle = -1;
        _candidateTime = 0;
        LOG_INFO("Angle Sensor проинициализирован");
    } else {
        LOG_ERR_VAL("bot.angleSensor.begin. Неподдерживаемый пин: ", (int)name);
        LOG_ERR("bot.angleSensor.begin Используйте XP8, XP9, XP10 или XP11");
    }
}

int AngleSensorAdapter::getAngle() {
    if(_isBeginAdapter() == false) return 0;
    int rawValue = analogRead(_pin);
    int angle = (int)(rawValue * (180.0 / 4095.0));

    // TODO подтянуть из конфига
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;

    unsigned long now = millis();

    if (abs(angle - _lastAngle) > TOLERANCE) {
        if (_candidateAngle >= 0 && abs(angle - _candidateAngle) <= TOLERANCE) {
            if (now - _candidateTime >= DEBOUNCE_MS) {
                _lastAngle = angle;
                _candidateAngle = -1;
            }
        } else {
            _candidateAngle = angle;
            _candidateTime = now;
        }
    } else {
        _candidateAngle = -1;
    }

    return _lastAngle;
}

bool AngleSensorAdapter::_isBeginAdapter() const {
    if(_isBegin == false) {
        LOG_ERR("Angle Sensor не было вызова begin. Класс не проинициализирован");
        return false;
    }
    return true;
}