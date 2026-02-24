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
#include "BuzzerAdapter.h"
#include <M5Unified.h>

void BuzzerAdapter::begin(Pins::Name name) {
    if(_isBegin == true) {
        LOG_ERR("Buzzer уже проинициализирован. Повторная инициализация игнорируется");
        return;
    }

    _pin = Pins::rigthPin(name);
    _ledChannel = 0;

    ledcSetup(_ledChannel, 4000, 10);
    ledcAttachPin(_pin, _ledChannel);
    ledcWrite(_ledChannel, 0);

    _isBegin = true;
    LOG_INFO("Buzzer проинициализирован");
}

void BuzzerAdapter::tick() {
    if(_isBegin == false) return;
    if(_playing == false) return;

    if(_toneEndTime > 0 && millis() >= _toneEndTime) {
        ledcWrite(_ledChannel, 0);
        _playing = false;
        _toneEndTime = 0;
    }
}

void BuzzerAdapter::tone(int frequency, unsigned long duration) {
    if(_isBeginAdapter() == false) return;
    if(_isValidFrequency(frequency) == false) return;

    ledcSetup(_ledChannel, frequency, 10);
    ledcAttachPin(_pin, _ledChannel);
    ledcWrite(_ledChannel, 512);

    _playing = true;

    if(duration > 0) {
        _toneEndTime = millis() + duration;
    } else {
        _toneEndTime = 0;
    }
}

void BuzzerAdapter::noTone() {
    if(_isBeginAdapter() == false) return;

    ledcWrite(_ledChannel, 0);
    _playing = false;
    _toneEndTime = 0;
}

bool BuzzerAdapter::_isValidFrequency(int frequency) {
    if(frequency >= 20 && frequency <= 20000) {
        return true;
    } else {
        LOG_ERR("bot.buzzer.tone. Аргумент frequency не может быть менее 20 или более 20000");
        return false;
    }
}

bool BuzzerAdapter::_isBeginAdapter() {
    if(_isBegin == false) {
        LOG_ERR("Buzzer не было вызова begin. Класс не проинициализирован");
    }
    return _isBegin;
}