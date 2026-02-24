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

// #define SERIAL_STATE_DEBUG

// WHEEL CONTROLLER SETTINGS
namespace Wheel {
  enum Name : uint8_t { XP14A, XP15A, XP14B, XP15B, COUNT };

  struct Config {
    uint8_t speedPin;
    uint8_t dirPin;
    int     initSpeed;
  };
  constexpr Config config[] = {
    [XP14A] = { 16,  8, 0 },
    [XP15A] = { 15, 38, 0 },
    [XP14B] = { 14, 37, 0 },
    [XP15B] = { 35, 11, 0 },
  };

  constexpr int MAX_SPEED = 255;
  constexpr uint8_t speedPin(Name w) { return config[w].speedPin; }
  constexpr uint8_t dirPin(Name w)   { return config[w].dirPin; }
  constexpr int     initSpeed(Name w){ return config[w].initSpeed; }
  constexpr Name getName(uint8_t i) { return static_cast<Name>(i); }
}

// SERVO CONTROLLER SETTINGS
namespace ServoPin {
  enum Name : uint8_t { SRV1, SRV2, SRV3, SRV4, COUNT };

  struct Config {
    uint8_t pwmPin;
    uint8_t initAngle;
    uint8_t minAngle;
    uint8_t maxAngle;
  };
  constexpr Config config[] = {
    [SRV1] = {2,  90, 0,  180},
    [SRV2] = {4,  90, 0,  180},
    [SRV3] = {19, 90, 0,  180}, 
    [SRV4] = {12, 90, 0,  180}
  };

  constexpr uint8_t POWER_PIN = 48;
  constexpr uint8_t STEP_INTERVAL_MS = 10;
  constexpr uint8_t pwmPin(Name n)    { return config[n].pwmPin; }
  constexpr uint8_t initAngle(Name n) { return config[n].initAngle; }
  constexpr uint8_t minAngle(Name n)  { return config[n].minAngle; }
  constexpr uint8_t maxAngle(Name n)  { return config[n].maxAngle; }
  constexpr Name getName(uint8_t i)   { return static_cast<Name>(i); }
}

namespace Led{
  enum Name : uint8_t { DA9, DA14, DA20, DA26, COUNT};

  constexpr uint8_t DEFAULT_BRIGHTHESS =  150;
  constexpr Name getName(uint8_t i)   { return static_cast<Name>(i); }

  namespace Color {
    constexpr uint32_t RED     = 0xFF0000;
    constexpr uint32_t GREEN   = 0x00FF00;
    constexpr uint32_t BLUE    = 0x0000FF;
    constexpr uint32_t YELLOW  = 0xFFFF00;
    constexpr uint32_t CYAN    = 0x00FFFF;
    constexpr uint32_t MAGENTA = 0xFF00FF;
    constexpr uint32_t BLACK   = 0x000000;
  }
}
#define LED_COUNT                           4
#define LED_PIN                             1

// ПРОТОКОЛ ОБМЕНА
#define SERIAL_PROTOCOL_BAUD    115200
#define PING_TIMEOUT_MS 1500

enum PacketType: uint8_t{
  STATE,
  GET_STATE,
  PING
};

struct __attribute__((packed)) PingPacket{
  bool isTrue;
};

struct __attribute__((packed)) StatePacket {
  // [DA9, DA14, DA20, DA26] cостояние светодиодов 
  uint32_t ledColor[4];
  // [SRV1 SRV2 SRV3 SRV4] текущее состояние сервоприводов (углы) 
  uint8_t servoAngle[4];
  // [XP14A, XP15A, XP14B, XP15B] текущая скорость моторов 
  int wheelSpeed[4];
};
