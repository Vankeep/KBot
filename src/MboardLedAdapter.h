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
#include "BaseAdapter.h"

class MboardLedAdapter : public BaseAdapter{
public:
    MboardLedAdapter(const char* objName) : BaseAdapter(objName) {}
    void color(Led::Name name, int red, int green, int blue);
    void color(Led::Name name, Led::Color color);
    void colorAll(Led::Color color);
    void off(Led::Name name);
    void offAll();
private:
    uint32_t _getColorUint(uint8_t r, uint8_t g, uint8_t b) { return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b; }
    bool _isValide(int red, int green, int blue);
};
