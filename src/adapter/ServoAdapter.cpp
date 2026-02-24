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
#include "ServoAdapter.h"
#include "../state.h"

void ServoAdapter::setAngle(ServoPin::Name name, int angle){
    if(angle < ServoPin::minAngle(name) ) {
        LOG_ERR_F("%s.setAngle() параметр angle не может быть менее чем %d", _objName, (int)ServoPin::minAngle(name));
        return;
    }
    if(angle > ServoPin::maxAngle(name)) {
        LOG_ERR_F("%s.setAngle() параметр angle не может быть более чем %d", _objName, (int)ServoPin::maxAngle(name));
        return;
    }
    State::setServoAngle(name, angle);
}

int ServoAdapter::getAngle(ServoPin::Name name){
    return (int)State::getServoAngle(name);
}

void ServoAdapter::goHome(){
    for(uint8_t i = 0; i < ServoPin::Name::COUNT; i++){
        ServoPin::Name name = ServoPin::getName(i);
        State::setServoAngle(name, ServoPin::initAngle(name));
    }
}
