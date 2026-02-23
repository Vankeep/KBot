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

class OledAdapter {
public:
    void init();
    void printStr1(const String& text);
    void printStr1(const char* text);
    void printStr1(int value);
    void printStr1(long value);
    void printStr1(float value, uint8_t decimals = 2);
    void printStr1(double value, uint8_t decimals = 2);

    void printStr2(const String& text);
    void printStr2(const char* text);
    void printStr2(int value);
    void printStr2(long value);
    void printStr2(float value, uint8_t decimals = 2);
    void printStr2(double value, uint8_t decimals = 2);

    void printStr3(const String& text);
    void printStr3(const char* text);
    void printStr3(int value);
    void printStr3(long value);
    void printStr3(float value, uint8_t decimals = 2);
    void printStr3(double value, uint8_t decimals = 2);

    void printStr4(const String& text);
    void printStr4(const char* text);
    void printStr4(int value);
    void printStr4(long value);
    void printStr4(float value, uint8_t decimals = 2);
    void printStr4(double value, uint8_t decimals = 2);

    void clear();

private:
    void _drawLine(uint8_t line, const char* text);
};
