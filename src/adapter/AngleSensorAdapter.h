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

class AngleSensorAdapter : public BaseAdapter{
public:
    AngleSensorAdapter(const char* objName) : BaseAdapter(objName) {}
    void begin(Pins::Name name);
    int getAngle();

private:
    uint8_t _pin;
    int _lastAngle = 0;
    int _candidateAngle = -1;
    unsigned long _candidateTime = 0;
    static const unsigned long DEBOUNCE_MS = 150;
    static const int TOLERANCE = 2;
};