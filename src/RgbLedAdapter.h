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
#include <Adafruit_NeoPixel.h>

class RgbLedAdapter {
public:

    void begin(Pins::Name name, int numLeds = 3);
    void tick();
    void setColor(int pixel, int r, int g, int b);
    void setColor(int pixel, Led::Color color);
    void setColorAll(int r, int g, int b);
    void setColorAll(Led::Color color);
    void setBrightness(int brightness);
    void clear();
    int getNumLeds() const;

private:
    bool _isBegin = false;
    bool _dirty = false;
    int _numLeds = 0;
    Adafruit_NeoPixel* _pixels = nullptr;

    bool _isValideRgb(int r, int g, int b);
    bool _isBeginAdapter() const;
};