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
#include <cstdint>

class ColorSensorAdapter {
public:
    ColorSensorAdapter(const char* objName);
    void begin(uint8_t address = 0x29);
    void calibrateWhite();
    void getRGB(int &r, int &g, int &b);

    bool isRed(int r, int g, int b);
    bool isGreen(int r, int g, int b);
    bool isBlue(int r, int g, int b);
    bool isWhite(int r, int g, int b);
    bool isBlack(int r, int g, int b);

private:
    char _objName[32];
    uint8_t _address;
    bool _calibrated;
    bool _isBegin = false;

    // White reference
    uint16_t _wr, _wg, _wb;

    void _writeByteAt(uint8_t reg, uint8_t data);
    uint16_t _readWordAt(uint8_t reg);

    static constexpr uint8_t COMMAND_BIT = 0x80;
    static constexpr uint8_t NUM_SAMPLES = 10;
    static constexpr int COLOR_DIFF_THRESHOLD = 5;

    bool _isBeginAdapter() const;
};