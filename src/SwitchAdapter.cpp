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
#include "SwitchAdapter.h"
#include <M5Unified.h>

void SwitchAdapter::begin(Pins::Name name, bool pullUp) {
    if(name == Pins::Name::XP8 || name == Pins::Name::XP9 ||
       name == Pins::Name::XP10 || name == Pins::Name::XP11 || name == Pins::Name::XP13){
        if(_isBegin == true) {
            LOG_INFO_F("%s уже проинициализирован. Повторная инициализация игнорируется", _objName);
            return;
        }
        _isBegin = true;
        _pin = Pins::leftPin(name);
        _pullUp = pullUp;
        pinMode(_pin, _pullUp ? INPUT_PULLUP : INPUT);
        _state = false;
        _stableState = false;
        _debouncing = false;
        _pressFlag = false;
        _releaseFlag = false;
        LOG_INFO_F("%s проинициализирован", _objName);
    } else {
        LOG_ERR_F("%s Неподдерживаемый пин: %d Используйте XP8, XP9, XP10, XP11 или XP13", _objName, (int)name);
    }
}

void SwitchAdapter::tick() {
    if(_isBegin == false) return;
    bool raw = digitalRead(_pin);
    bool current = _pullUp ? !raw : raw;

    unsigned long now = millis();

    if (current != _stableState) {
        if (!_debouncing) {
            _debouncing = true;
            _debTimer = now;
        } else if (now - _debTimer >= DEBOUNCE_MS) {
            _stableState = current;
            _debouncing = false;

            if (_stableState) {
                _pressFlag = true;
            } else {
                _releaseFlag = true;
            }
        }
    } else {
        _debouncing = false;
    }

    _state = _stableState;
}

bool SwitchAdapter::isPressed() {
    if(_isBeginAdapter() == false) return false;
    if (_pressFlag) {
        _pressFlag = false;
        return true;
    }
    return false;
}

bool SwitchAdapter::isReleased() {
    if(_isBeginAdapter() == false) return false;
    if (_releaseFlag) {
        _releaseFlag = false;
        return true;
    }
    return false;
}

bool SwitchAdapter::isHeld() {
    if(_isBeginAdapter() == false) return false;
    return _state;
}
