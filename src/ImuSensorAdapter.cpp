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
#include "ImuSensorAdapter.h"
#include <Wire.h>
#include <math.h>

bool ImuSensorAdapter::_isBeginAdapter() {
    if (_isBegin == false) {
        Serial.println("ERR: bot.imu. IMU датчик не обнаружен");
    }
    return _isBegin;
}

void ImuSensorAdapter::begin(uint8_t address) {
    _address = address;

    uint8_t whoAmI = _readReg(REG_WHO_AM_I);
    Serial.print("IMU WHO_AM_I: 0x");
    Serial.println(whoAmI, HEX);

    if (whoAmI != 0x19) {
        _isBegin = false;
        Serial.println("WARN: bot.imu. MPU6886 не обнаружен на шине I2C");
        return;
    }

    // Сброс датчика
    _writeReg(REG_PWR_MGMT_1, 0x80);
    delay(100);

    // Выход из sleep, тактирование от внутреннего генератора
    _writeReg(REG_PWR_MGMT_1, 0x01);
    delay(10);

    // Включить акселерометр и гироскоп (все оси)
    _writeReg(REG_PWR_MGMT_2, 0x00);
    delay(10);

    // Sample Rate Divider = 0 (максимальная частота)
    _writeReg(REG_SMPLRT_DIV, 0x00);

    // DLPF = 1 (184 Hz bandwidth для гироскопа)
    _writeReg(REG_CONFIG, 0x01);

    // Гироскоп: +-500 dps
    _writeReg(REG_GYRO_CONFIG, 0x08);

    // Акселерометр: +-2g
    _writeReg(REG_ACCEL_CONFIG, 0x00);

    // Акселерометр DLPF: bandwidth ~218 Hz
    _writeReg(REG_ACCEL_CONFIG2, 0x01);

    delay(50);

    _isBegin = true;
    Serial.println("OK: bot.imu. MPU6886 инициализирован");
}

void ImuSensorAdapter::tick() {
    if (_isBegin == false) return;

    unsigned long now = millis();
    if (now - _lastUpdateTime < UPDATE_INTERVAL_MS) return;
    _lastUpdateTime = now;

    uint8_t rawAccel[6] = {0};
    _readBlock(REG_ACCEL_XOUT_H, 6, rawAccel);

    int16_t rawAx = (int16_t)((rawAccel[0] << 8) | rawAccel[1]);
    int16_t rawAy = (int16_t)((rawAccel[2] << 8) | rawAccel[3]);
    int16_t rawAz = (int16_t)((rawAccel[4] << 8) | rawAccel[5]);

    float ax = (float)rawAx / 16384.0f;
    float ay = (float)rawAy / 16384.0f;
    float az = (float)rawAz / 16384.0f;

    _accelX = (int)(ax * 1000);
    _accelY = (int)(ay * 1000);
    _accelZ = (int)(az * 1000);

    uint8_t rawGyro[6] = {0};
    _readBlock(REG_GYRO_XOUT_H, 6, rawGyro);

    int16_t rawGx = (int16_t)((rawGyro[0] << 8) | rawGyro[1]);
    int16_t rawGy = (int16_t)((rawGyro[2] << 8) | rawGyro[3]);
    int16_t rawGz = (int16_t)((rawGyro[4] << 8) | rawGyro[5]);

    _gyroX = (int)((float)rawGx / 65.5f);
    _gyroY = (int)((float)rawGy / 65.5f);
    _gyroZ = (int)((float)rawGz / 65.5f);

    _pitch = (int)(atan2(ax, sqrt(ay * ay + az * az)) * 180.0f / M_PI);
    _roll  = (int)(atan2(ay, sqrt(ax * ax + az * az)) * 180.0f / M_PI);
}

int ImuSensorAdapter::getPitch()  { if (!_isBeginAdapter()) return 0; return _pitch;  }
int ImuSensorAdapter::getRoll()   { if (!_isBeginAdapter()) return 0; return _roll;   }
int ImuSensorAdapter::getAccelX() { if (!_isBeginAdapter()) return 0; return _accelX; }
int ImuSensorAdapter::getAccelY() { if (!_isBeginAdapter()) return 0; return _accelY; }
int ImuSensorAdapter::getAccelZ() { if (!_isBeginAdapter()) return 0; return _accelZ; }
int ImuSensorAdapter::getGyroX()  { if (!_isBeginAdapter()) return 0; return _gyroX;  }
int ImuSensorAdapter::getGyroY()  { if (!_isBeginAdapter()) return 0; return _gyroY;  }
int ImuSensorAdapter::getGyroZ()  { if (!_isBeginAdapter()) return 0; return _gyroZ;  }

// --- I2C low-level ---

void ImuSensorAdapter::_writeReg(uint8_t reg, uint8_t data) {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();
}

uint8_t ImuSensorAdapter::_readReg(uint8_t reg) {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(_address, (uint8_t)1);
    return Wire.available() ? Wire.read() : 0x00;
}

void ImuSensorAdapter::_readBlock(uint8_t reg, uint8_t count, uint8_t* buf) {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(_address, count);
    for (uint8_t i = 0; i < count && Wire.available(); i++) {
        buf[i] = Wire.read();
    }
}