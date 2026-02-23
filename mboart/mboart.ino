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
#include "./lib/serial_transfer/Packet.cpp"
#include "./lib/serial_transfer/SerialTransfer.cpp"
#include <Arduino.h>
#include "wheels_controller.h"
#include "serial_controller.h"
#include "servo_controller.h"
#include "led_controller.h"
#include "state.h"

LedController ledController{};
WheelsController wheelsController;
ServoController servoController;
SerialController serialController;

void setup() {
  wheelsController.init();
  serialController.init(servoController);
  Serial.begin(SERIAL_PROTOCOL_BAUD);

  pinMode(8, OUTPUT);
  pinMode(38, OUTPUT);
  State::init();
  ledController.init();
  servoController.init();
}

void loop() {
  serialController.available();
  ledController.loop();
  wheelsController.loop();
  servoController.loop();
  State::flush();
}
