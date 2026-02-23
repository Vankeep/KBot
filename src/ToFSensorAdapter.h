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

class ToFSensorAdapter {
public:
    void begin(uint8_t address = 0x29);
    long getDistanceMm(); 

private:
    uint8_t _address;
    long _lastDistance = 0;
    long _candidateDistance = -1;
    unsigned long _candidateTime = 0;

    uint16_t _readRangeMm();
    void _writeByteAt(uint8_t reg, uint8_t data);
    void _readBlockAt(uint8_t reg, uint8_t count, uint8_t* buf);

    static const unsigned long DEBOUNCE_MS = 50;
    static const int TOLERANCE = 10;
};