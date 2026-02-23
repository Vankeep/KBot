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
#include "ESP32Servo.h"
#include "config.h"
#include <Arduino.h>
#include "servo_controller.h"
#include "state.h"

void ServoController::init() {
    pinMode(Servos::POWER_PIN, OUTPUT);
    digitalWrite(Servos::POWER_PIN, HIGH);
    delay(100);

    for(uint8_t i = 0; i < Servos::Name::COUNT; i++){
      Servos::Name name = Servos::getName(i);

      uint8_t angle = Servos::initAngle(name);
      _currentAngles[i] = angle;
      _targetAngles[i] = angle;

      _servos[i].attach(Servos::pwmPin(name));
      _servos[i].write(angle);
      delay(10);
    }
  }


void ServoController::loop() {
  if (!_markChangedFlag) { return; }
  const unsigned long now = millis();
  if (now - _lastStepMs < Servos::STEP_INTERVAL_MS) { return; }
  _lastStepMs = now;

  bool allArrived = true;

  for (uint8_t i = 0; i < Servos::Name::COUNT; i++) {
    if (_currentAngles[i] == _targetAngles[i]) { continue; }
    Servos::Name name = Servos::getName(i);

    _currentAngles[i] += (_currentAngles[i] < _targetAngles[i]) ? 1 : -1;
    _servos[i].write(_currentAngles[i]);

    if (_currentAngles[i] != _targetAngles[i]) {
      allArrived = false;
    }
  }

  if (allArrived) {
    _markChangedFlag = false;
    for (uint8_t i = 0; i < Servos::Name::COUNT; i++) {
      Servos::Name name = Servos::getName(i);
      State::setServoAngle(name, _currentAngles[i]);
    }
  }
}

void ServoController::setTargetAngles(uint8_t* targetServoAngle){
  for(uint8_t i = 0; i < Servos::Name::COUNT; i++){
    Servos::Name name = Servos::getName(i);

    uint8_t currentAngle = State::getServoAngle(name);

    if(currentAngle != targetServoAngle[i]){
      _targetAngles[i] = targetServoAngle[i];
      _markChangedFlag = true;
    } else {
      _targetAngles[i] = currentAngle;
    }
  }
}