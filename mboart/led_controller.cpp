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
#include "pgmspace.h"
#include "config.h"
#include "led_controller.h"
#include "state.h"

LedController::LedController()
    : _ledStrip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800) {
  }


void LedController::init(){
  _ledStrip.begin();
  _ledStrip.setBrightness(Led::DEFAULT_BRIGHTHESS);
}

void LedController::loop(){
  for(uint8_t i = 0; i < Led::Name::COUNT; i++){
    Led::Name name = Led::getName(i);
    _ledStrip.setPixelColor((uint8_t)name, State::getLedColor(name));
  }
  _ledStrip.show();
}
