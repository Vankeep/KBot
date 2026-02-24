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
#include <M5Unified.h>

class SensorButtonAdapter {
public:
    SensorButtonAdapter(const char* objName);
    void begin(uint8_t slot);
    void setText(const char* text);
    bool isClick();

private:
    char _objName[32];
    int16_t _x, _y, _w, _h;
    char _text[20];
    bool _lastState = false;
    void _draw(bool pressed = false);
};
