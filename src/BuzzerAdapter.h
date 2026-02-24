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

class BuzzerAdapter {
public:
    BuzzerAdapter(const char* objName);
    void begin(Pins::Name name);
    void tick();
    void tone(int frequency, unsigned long duration = 0);
    void noTone();

private:
    char _objName[32];
    bool _isBegin = false;
    uint8_t _pin = 0;
    int _ledChannel = 0;
    bool _playing = false;
    unsigned long _toneEndTime = 0;

    bool _isBeginAdapter() const;
};