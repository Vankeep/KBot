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

class LineSensorAdapter {
public:
    void begin(Pins::Name name);
    void tick();
    bool isOnLine();
    bool isDetected();
    bool isLost();

private:
    // Гистерезис
    static constexpr int THRESHOLD_LOW  = 1800;
    static constexpr int THRESHOLD_HIGH = 2300;
    // фильтр EMA
    static constexpr int EMA_NUM = 3;  
    static constexpr int EMA_DEN = 16;
    // debounce
    static constexpr uint8_t DEBOUNCE_COUNT = 3;
    //Мультисэмплинг
    static constexpr uint8_t ADC_SAMPLES = 5;

    uint8_t  _pin          = 0;
    bool     _isBegin      = false;
    int32_t  _emaScaled    = 0;

    bool     _isOnLine     = false;
    bool     _wasOnLine    = false;
    bool     _detected     = false;
    bool     _lost         = false;

    bool     _candidate    = false;   // кандидат на новое состояние
    uint8_t  _stableCount  = 0;       // счётчик стабильных тиков

    int      readMedian();
};