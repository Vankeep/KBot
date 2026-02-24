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
#include <ESP32Servo.h>
#include "config.h"


class ServoController {
public:
  void init();
  void loop();
  void setTargetAngles(uint8_t* targetServoAngle);

private:
  Servo _servos[ServoPin::Name::COUNT];
  uint8_t _targetAngles[ServoPin::Name::COUNT];
  uint8_t _currentAngles[ServoPin::Name::COUNT];
  unsigned long _lastStepMs = 0;
  bool _markChangedFlag = false;
};