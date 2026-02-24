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

//#define SERIAL_STATE_DEBUG

// WHEEL CONTROLLER SETTINGS
#define WHEEL_SPEED_MAX     200
#define WHEEL_SPEED_MIN     -200
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
  // Аксессоры
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

  enum Color : uint32_t {
    RED     = 0xFF0000,
    GREEN   = 0x00FF00,
    BLUE    = 0x0000FF,
    YELLOW  = 0xFFFF00,
    CYAN    = 0x00FFFF,
    MAGENTA = 0xFF00FF,
    BLACK   = 0x000000
  };
}
#define LED_COUNT                           4
#define LED_PIN                             1

namespace Connector {
  enum Name : uint8_t { XP8, XP9, XP10, XP13, XP12, XP11, COUNT }; 
  struct Config {
    uint8_t leftPin;
    uint8_t rigthPin;
    const char* text;
  };
  constexpr Config config[] = {
    [XP8] =  {35, 23, "XP8"},        //   16 15 14 35 8 38 37 11
    [XP9] =  {0,  27, "XP9"},
    [XP10] = {34, 2 , "XP10"}, 
    [XP13] = {38, 26, "XP13"},
    [XP12] = {18, 19, "XP12"},
    [XP11] = {36, 25, "XP11"}
  };
  constexpr uint8_t leftPin(Name n)  { return config[n].leftPin; }
  constexpr uint8_t rigthPin(Name n) { return config[n].rigthPin; }
  constexpr const char* text(Name n)   { return config[n].text; }
  constexpr Name getName(uint8_t i)  { return static_cast<Name>(i); }
}

// ПРОТОКОЛ ОБМЕНА
#define SERIAL_PROTOCOL_BAUD    115200
#define PING_INTERVAL_MS        1000

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

// LOGGING SYSTEM
// Для отключения логирования добавьте #define NO_LOGGING в ваш .ino файл перед #include <KBot.h>
// Макросы можно использовать в своем коде

// - d = decimal (десятичное целое число)
// - s = string (строка)
// - f = float (дробное число)
// - x = hexadecimal (шестнадцатеричное)
// - u = unsigned (беззнаковое целое)
// - c = char (один символ)
// LOG_INFO_F("%s проинициализирован", nameObj);
// LOG_ERR_F("Ошибка на пине %d", pinNumber);
// LOG_INFO_F("Значение %s: %d", name, value);
#ifndef NO_LOGGING
  #define LOG_INFO(msg) do { Serial.print("[INFO] - "); Serial.println(msg); } while(0)
  #define LOG_ERR(msg) do { Serial.print("[ERR] - "); Serial.println(msg); } while(0)
  #define LOG_INFO_VAL(msg, val) do { Serial.print("[INFO] - "); Serial.print(msg); Serial.println(val); } while(0)
  #define LOG_ERR_VAL(msg, val) do { Serial.print("[ERR] - "); Serial.print(msg); Serial.println(val); } while(0)
  #define LOG_INFO_F(fmt, ...) do { \
    char logBuffer[100]; \
    snprintf(logBuffer, sizeof(logBuffer), fmt, __VA_ARGS__); \
    LOG_INFO(logBuffer); \
  } while(0)
  #define LOG_ERR_F(fmt, ...) do { \
    char logBuffer[100]; \
    snprintf(logBuffer, sizeof(logBuffer), fmt, __VA_ARGS__); \
    LOG_ERR(logBuffer); \
  } while(0)
#else
  #define LOG_INFO(msg)
  #define LOG_ERR(msg)
  #define LOG_INFO_VAL(msg, val)
  #define LOG_ERR_VAL(msg, val)
  #define LOG_INFO_F(fmt, ...)
  #define LOG_ERR_F(fmt, ...)
#endif

