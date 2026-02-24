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
#include "ToFSensorAdapter.h"
#include <M5Unified.h>
#include <Wire.h>

#define VL53L0X_REG_SYSRANGE_START          0x00
#define VL53L0X_REG_RESULT_RANGE_STATUS     0x14

void ToFSensorAdapter::begin(uint8_t address) {
    // TODO добавить проверкку на инициализицию
    _address = address;
    _lastDistance = 0;
    _candidateDistance = -1;
    _candidateTime = 0;
}

long ToFSensorAdapter::getDistanceMm() {
    // TODO добавить проверкку на инициализицию
    uint16_t raw = _readRangeMm();
    if (raw == 0 || raw > 2000) return _lastDistance;

    long distance = (long)raw;
    unsigned long now = millis();

    if (abs(distance - _lastDistance) > TOLERANCE) {
        if (_candidateDistance >= 0 && abs(distance - _candidateDistance) <= TOLERANCE) {
            if (now - _candidateTime >= DEBOUNCE_MS) {
                _lastDistance = distance;
                _candidateDistance = -1;
            }
        } else {
            _candidateDistance = distance;
            _candidateTime = now;
        }
    } else {
        _candidateDistance = -1;
    }

    return (_lastDistance - 20) < 0 ? 0 : _lastDistance - 20 ;
}

uint16_t ToFSensorAdapter::_readRangeMm() {
    uint8_t buf[12] = {0};

    _writeByteAt(VL53L0X_REG_SYSRANGE_START, 0x01);

    _readBlockAt(VL53L0X_REG_RESULT_RANGE_STATUS, 12, buf);

    uint16_t dist = ((uint16_t)(buf[10] & 0xFF) << 8) | (buf[11] & 0xFF);
    return dist;
}

void ToFSensorAdapter::_writeByteAt(uint8_t reg, uint8_t data) {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();
}

void ToFSensorAdapter::_readBlockAt(uint8_t reg, uint8_t count, uint8_t* buf) {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.endTransmission(false);

    Wire.requestFrom(_address, count);
    for (uint8_t i = 0; i < count && Wire.available(); i++) {
        buf[i] = Wire.read();
    }
}