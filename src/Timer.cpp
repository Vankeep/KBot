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
#include "Timer.h"

void Timer::begin() {
    _interval = 0;
    _lastTick = 0;
    _active = false;
    _done = false;
    _ready = false;
    _repeat = false;
    _initialized = true;
}

void Timer::startOnce(uint32_t ms) {
    if (!_initialized) return;
    _interval = ms;
    _repeat = false;
    _lastTick = millis();
    _active = true;
    _done = false;
    _ready = false;
}

void Timer::startEvery(uint32_t ms) {
    if (!_initialized) return;
    _interval = ms;
    _repeat = true;
    _lastTick = millis();
    _active = true;
    _done = false;
    _ready = false;
}

void Timer::stop() {
    _active = false;
    _done = false;
    _ready = false;
}

void Timer::reset() {
    if (!_initialized) return;
    _lastTick = millis();
    _done = false;
    _ready = false;
    _active = true;
}

bool Timer::isReady() const {
    return _ready;
}

bool Timer::isActive() const {
    return _active;
}

bool Timer::isDone() const {
    return _done;
}

void Timer::update() {
    _ready = false;
    if (!_active) return;

    if (millis() - _lastTick >= _interval) {
        _ready = true;
        if (_repeat) {
            _lastTick = millis();
        } else {
            _active = false;
            _done = true;
        }
    }
}
