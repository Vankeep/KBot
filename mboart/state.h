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
#include "serial_controller.h"
#include "config.h"

class State{
public:
  static void init() {  
    for(uint8_t i = 0; i < Wheel::Name::COUNT; i++){
      Wheel::Name name = Wheel::getName(i);
      setWheelSpeed(name, Wheel::initSpeed(name));
    }

    for(uint8_t i = 0; i < ServoPin::Name::COUNT; i++){
      ServoPin::Name name = ServoPin::getName(i);
      setServoAngle(name, ServoPin::initAngle(name));
    }

    for(uint8_t i = 0; i < Led::Name::COUNT; i++){
      Led::Name name = Led::getName(i);
      setLedColor(name, Led::Color::BLACK);
    }

    _markStateChangedFlag = false;
  }

  static void setWheelSpeed(Wheel::Name n, int val) { _set(&_statePacket.wheelSpeed[n], val); }
  static int getWheelSpeed(Wheel::Name n) { return _statePacket.wheelSpeed[n]; }

  static void setServoAngle(ServoPin::Name n, uint8_t val) { _set(&_statePacket.servoAngle[n], val); }
  static uint8_t getServoAngle(ServoPin::Name n) { return _statePacket.servoAngle[n]; }

  static void setLedColor(Led::Name n, uint32_t color){ _set(&_statePacket.ledColor[n], color);}
  static uint32_t getLedColor(Led::Name n){ return _statePacket.ledColor[n]; }

  static void flush() {
    if (_markStateChangedFlag) {
      SerialController::sendState();
      _markStateChangedFlag = false;
    } 
  }

  static StatePacket& getStatePacket() { return _statePacket; }
  
private:
  static StatePacket _statePacket;
  static bool _markStateChangedFlag;
  
  template<typename T>
  static void _set(T* field, T newValue) {
    if(*field != newValue) {
      *field = newValue;
      _markStateChangedFlag = true;
    }
  }

};

// Определения статических членов
inline StatePacket State::_statePacket;
inline bool State::_markStateChangedFlag = false;