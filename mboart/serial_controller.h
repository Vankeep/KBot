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
#include <Arduino.h>
#include "./lib/serial_transfer/SerialTransfer.h"

class ServoController;

class SerialController{
public:

  void init(ServoController& servoController);
  bool available();

  static void sendState();
private:
  SerialTransfer _serialTransfer;
  ServoController* _servoController;
  static SerialController* _instance;
  bool _stateSendRequested;
  uint32_t _lastPingTime;

  void _parceStatePacket();
};

