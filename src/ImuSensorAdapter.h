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
#include <stdint.h>

class ImuSensorAdapter {
public:
    void begin(uint8_t address = 0x68);
    void tick();

    int getPitch();
    int getRoll();
    int getAccelX();
    int getAccelY();
    int getAccelZ();
    int getGyroX();
    int getGyroY();
    int getGyroZ();

private:
    uint8_t _address = 0x68;
    bool _isBegin = false;
    bool _isBeginAdapter();

    int _pitch = 0;
    int _roll  = 0;
    int _accelX = 0;
    int _accelY = 0;
    int _accelZ = 0;
    int _gyroX = 0;
    int _gyroY = 0;
    int _gyroZ = 0;

    unsigned long _lastUpdateTime = 0;
    static const unsigned long UPDATE_INTERVAL_MS = 50;

    // MPU6886 registers
    static const uint8_t REG_WHO_AM_I    = 0x75;
    static const uint8_t REG_PWR_MGMT_1  = 0x6B;
    static const uint8_t REG_PWR_MGMT_2  = 0x6C;
    static const uint8_t REG_SMPLRT_DIV  = 0x19;
    static const uint8_t REG_CONFIG      = 0x1A;
    static const uint8_t REG_GYRO_CONFIG = 0x1B;
    static const uint8_t REG_ACCEL_CONFIG  = 0x1C;
    static const uint8_t REG_ACCEL_CONFIG2 = 0x1D;
    static const uint8_t REG_ACCEL_XOUT_H = 0x3B;
    static const uint8_t REG_GYRO_XOUT_H  = 0x43;

    void _writeReg(uint8_t reg, uint8_t data);
    uint8_t _readReg(uint8_t reg);
    void _readBlock(uint8_t reg, uint8_t count, uint8_t* buf);
};