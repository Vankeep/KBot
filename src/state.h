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
#include "SerialController.h"
#include "config.h"

class State{
public:
  static void init() {  
    for(uint8_t i = 0; i < Wheel::Name::COUNT; i++){
      Wheel::Name name = Wheel::getName(i);
      setWheelSpeed(name, Wheel::initSpeed(name));
    }

    for(uint8_t i = 0; i < Servos::Name::COUNT; i++){
      Servos::Name name = Servos::getName(i);
      _statePacket.servoAngle[name] = Servos::initAngle(name);
      _nextAngle[name] = Servos::initAngle(name);
    }

    for(uint8_t i = 0; i < Led::Name::COUNT; i++){
      Led::Name name = Led::getName(i);
      setLedColor(name, Led::Color::BLACK);
    }

    _markStateChangedFlag = false;
  }

  static void setWheelSpeed(Wheel::Name n, int val) { _set(&_statePacket.wheelSpeed[n], val); }
  static int getWheelSpeed(Wheel::Name n) { return _statePacket.wheelSpeed[n]; }

  static void setServoAngle(Servos::Name n, uint8_t val) { 
    if(val != _nextAngle[n]){
      _nextAngle[n] = val;
      _markStateChangedFlag = true;
    }
  }
  static uint8_t getServoAngle(Servos::Name n) { return _statePacket.servoAngle[n]; }

  static void setLedColor(Led::Name n, uint32_t color){ _set(&_statePacket.ledColor[n], color);}
  static uint32_t getLedColor(Led::Name n){ return _statePacket.ledColor[n]; }

  static void flush() {
    if (_markStateChangedFlag) {
      // save current angle
      uint8_t tmp[sizeof(_statePacket.servoAngle)];
      memcpy(tmp, _statePacket.servoAngle, sizeof(tmp));
      // set target
      memcpy(_statePacket.servoAngle, _nextAngle, sizeof(_nextAngle));
      SerialController::sendState();
      // set current
      memcpy(_statePacket.servoAngle, tmp, sizeof(tmp));

      _markStateChangedFlag = false;
    }
  }


  static StatePacket& getStatePacket() { return _statePacket; }

    static void setStatePacketDirect(const StatePacket& packet) {
        _statePacket = packet;
    }


  static void printState(){
#ifdef SERIAL_STATE_DEBUG
    Serial.println("Моторы:");
    Serial.print("14A=");
    Serial.print(State::getWheelSpeed(Wheel::Name::XP14A));
    Serial.print(" | 15A=");
    Serial.print(State::getWheelSpeed(Wheel::Name::XP15A));
    Serial.print(" | 14B=");
    Serial.print(State::getWheelSpeed(Wheel::Name::XP14B));
    Serial.print(" | 15B=");
    Serial.println(State::getWheelSpeed(Wheel::Name::XP15B));
    Serial.println("Сервоприводы:");
    Serial.print("SRV1=");
    Serial.print(State::getServoAngle(Servos::Name::SRV1));
    Serial.print(" | SRV2=");
    Serial.print(State::getServoAngle(Servos::Name::SRV2));
    Serial.print(" | SRV3=");
    Serial.print(State::getServoAngle(Servos::Name::SRV3));
    Serial.print(" | SRV4=");
    Serial.print(State::getServoAngle(Servos::Name::SRV4));
    Serial.print(" | SRV5=");
    Serial.print(State::getServoAngle(Servos::Name::SRV5));  
    Serial.print(" | SRV6=");
    Serial.println(State::getServoAngle(Servos::Name::SRV6)); 
    Serial.println("Светодиоды:");
    for(uint8_t i = 0; i < 4; i++){
      Serial.print("  ledColor ");
      Serial.print(i);
      Serial.print(": 0x");
      Serial.println(State::getLedColor(Led::getName(i)), HEX);
    }
#endif
}
  
private:
  static StatePacket _statePacket;
  static bool _markStateChangedFlag;
  static uint8_t _nextAngle[Servos::Name::COUNT];

  template<typename T>
  static void _set(T* field, T newValue) {
    if(*field != newValue) {
      *field = newValue;
      _markStateChangedFlag = true;
    }
  }

};

inline StatePacket State::_statePacket;
inline bool State::_markStateChangedFlag = false;
inline uint8_t State::_nextAngle[Servos::Name::COUNT];