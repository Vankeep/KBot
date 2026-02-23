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
#include "ColorSensorAdapter.h"
#include <M5Unified.h>
#include <Wire.h>

// TCS34725 registers
#define TCS34725_ENABLE     0x00
#define TCS34725_ATIME      0x01
#define TCS34725_CONTROL    0x0F
#define TCS34725_ID         0x12
#define TCS34725_CDATAL     0x14
#define TCS34725_RDATAL     0x16
#define TCS34725_GDATAL     0x18
#define TCS34725_BDATAL     0x1A

// ENABLE register bits
#define TCS34725_PON        0x01
#define TCS34725_AEN        0x02

void ColorSensorAdapter::begin(uint8_t address) {
    _address = address;
    _wr = _wg = _wb = 1;
    _calibrated = false;
    _isConnected = false;

    // Check I2C ACK
    Wire.beginTransmission(_address);
    if (Wire.endTransmission() != 0) return;

    // Verify chip ID (TCS34725 returns 0x44 or 0x4D)
    Wire.beginTransmission(_address);
    Wire.write(COMMAND_BIT | TCS34725_ID);
    Wire.endTransmission(false);
    Wire.requestFrom(_address, (uint8_t)1);
    uint8_t id = Wire.read();
    if (id != 0x44 && id != 0x4D) return;

    _isConnected = true;

    // Power ON
    _writeByteAt(TCS34725_ENABLE, TCS34725_PON);
    delay(3);
    // Enable RGBC
    _writeByteAt(TCS34725_ENABLE, TCS34725_PON | TCS34725_AEN);

    // Integration time: 154ms
    _writeByteAt(TCS34725_ATIME, 0xC0);
    // Gain: 4x
    _writeByteAt(TCS34725_CONTROL, 0x01);

    delay(200);
}

void ColorSensorAdapter::calibrateWhite() {
    if (!_isConnected) return;

    uint32_t sumR = 0, sumG = 0, sumB = 0;

    for (uint8_t i = 0; i < NUM_SAMPLES; i++) {
        delay(160);
        sumR += _readWordAt(TCS34725_RDATAL);
        sumG += _readWordAt(TCS34725_GDATAL);
        sumB += _readWordAt(TCS34725_BDATAL);
    }

    _wr = sumR / NUM_SAMPLES;
    _wg = sumG / NUM_SAMPLES;
    _wb = sumB / NUM_SAMPLES;

    if (_wr == 0) _wr = 1;
    if (_wg == 0) _wg = 1;
    if (_wb == 0) _wb = 1;

    _calibrated = true;
}

void ColorSensorAdapter::getRGB(int &r, int &g, int &b) {
    if (!_isConnected || !_calibrated) {
        r = g = b = 0;
        return;
    }

    uint16_t rawR = _readWordAt(TCS34725_RDATAL);
    uint16_t rawG = _readWordAt(TCS34725_GDATAL);
    uint16_t rawB = _readWordAt(TCS34725_BDATAL);

    uint32_t rr = (uint32_t)rawR * 255 / _wr;
    uint32_t gr = (uint32_t)rawG * 255 / _wg;
    uint32_t br = (uint32_t)rawB * 255 / _wb;

    r = (rr > 255) ? 255 : (int)rr;
    g = (gr > 255) ? 255 : (int)gr;
    b = (br > 255) ? 255 : (int)br;
}

bool ColorSensorAdapter::isRed(int r, int g, int b) {
    return r > g && r > b
        && (r - g) > COLOR_DIFF_THRESHOLD
        && (r - b) > COLOR_DIFF_THRESHOLD;
}

bool ColorSensorAdapter::isGreen(int r, int g, int b) {
    return g > r && g > b
        && (g - r) > COLOR_DIFF_THRESHOLD
        && (g - b) > COLOR_DIFF_THRESHOLD;
}

bool ColorSensorAdapter::isBlue(int r, int g, int b) {
    return b > r && b > g
        && (b - r) > COLOR_DIFF_THRESHOLD
        && (b - g) > COLOR_DIFF_THRESHOLD;
}

bool ColorSensorAdapter::isWhite(int r, int g, int b) {
    return r > 200 && g > 200 && b > 200;
}

bool ColorSensorAdapter::isBlack(int r, int g, int b) {
    return r < 30 && g < 30 && b < 30;
}

void ColorSensorAdapter::_writeByteAt(uint8_t reg, uint8_t data) {
    Wire.beginTransmission(_address);
    Wire.write(COMMAND_BIT | reg);
    Wire.write(data);
    Wire.endTransmission();
}

uint16_t ColorSensorAdapter::_readWordAt(uint8_t reg) {
    Wire.beginTransmission(_address);
    Wire.write(COMMAND_BIT | reg);
    Wire.endTransmission(false);

    Wire.requestFrom(_address, (uint8_t)2);
    uint8_t lo = Wire.read();
    uint8_t hi = Wire.read();
    return ((uint16_t)hi << 8) | lo;
}