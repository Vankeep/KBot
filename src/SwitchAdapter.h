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

class SwitchAdapter {
public:
    void begin(Pins::Name name, bool pullUp = true);
    void tick();

    bool isPressed();   // true один раз при замыкании
    bool isReleased();  // true один раз при размыкании
    bool isHeld();      // true пока удерживается

private:
    bool _isBegin = false;
    uint8_t _pin;
    bool _pullUp = true;

    bool _state = false;
    bool _stableState = false;
    bool _debouncing = false;
    uint32_t _debTimer = 0;

    bool _pressFlag = false;
    bool _releaseFlag = false;

    static const uint16_t DEBOUNCE_MS = 80;
};
