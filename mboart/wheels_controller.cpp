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
#include "config.h"
#include "wheels_controller.h"
#include "state.h"

void WheelsController::init(){
  for(uint8_t i = 0; i < Wheel::Name::COUNT; i++){
    Wheel::Name name = Wheel::getName(i);
    pinMode(Wheel::dirPin(name), OUTPUT);
    pinMode(Wheel::speedPin(name), OUTPUT);
  }
}

void WheelsController::loop(){
  for(uint8_t i = 0; i < Wheel::Name::COUNT; i++){
    Wheel::Name name = Wheel::getName(i);
    int speed = State::getWheelSpeed(name);
    
    digitalWrite(Wheel::dirPin(name), speed >= 0 ? 0:1);
    analogWrite(Wheel::speedPin(name), abs(speed));
  }
  delay(10); // TODO под вопросом. 
}