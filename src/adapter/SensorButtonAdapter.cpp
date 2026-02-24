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
#include "SensorButtonAdapter.h"

void SensorButtonAdapter::begin(uint8_t slot) {
    _w = 152;
    _h = 48;
    _x = 4 + (slot % 2) * 160;
    _y = 4 + (slot / 2) * 60;
    snprintf(_text, sizeof(_text), "BTN %d", slot + 1);
    _draw();
    _isBegin = true;
    LOG_INFO_F("%s проинициализирован", _objName);
}

void SensorButtonAdapter::setText(const char* text) {
    strncpy(_text, text, sizeof(_text) - 1);
    _text[sizeof(_text) - 1] = '\0';
    _draw();
}

bool SensorButtonAdapter::isClick() {
    auto t = M5.Touch.getDetail();
    bool touched = (t.isPressed() &&
                    t.x >= _x && t.x <= _x + _w &&
                    t.y >= _y && t.y <= _y + _h);

    if (touched && !_lastState) {
        _lastState = true;
        _draw(true);
    }
    if (!touched && _lastState) {
        _lastState = false;
        _draw(false);
        return true; 
    }
    return false;
}

void SensorButtonAdapter::_draw(bool pressed) {
    uint16_t bg = pressed ? 0xCE40 : 0x2945;  
    uint16_t border = 0x7BCF;                 
    uint16_t fg    = TFT_WHITE;

    M5.Lcd.fillRoundRect(_x, _y, _w, _h, 8, bg);
    M5.Lcd.drawRoundRect(_x, _y, _w, _h, 8, border);
    M5.Lcd.setTextColor(fg, bg);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextDatum(MC_DATUM);
    M5.Lcd.drawString(_text, _x + _w / 2, _y + _h / 2);
}