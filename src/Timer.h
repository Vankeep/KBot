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
#include <Arduino.h>

class Timer {
public:
    void begin();
    void startOnce(uint32_t ms);
    void startEvery(uint32_t ms);
    void stop();
    void reset();

    bool isReady() const;
    bool isActive() const;
    bool isDone() const;

    void update();

private:
    uint32_t _interval = 0;
    uint32_t _lastTick = 0;
    bool _active = false;
    bool _done = false;
    bool _ready = false;
    bool _repeat = false;
    bool _initialized = false;
};
