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
#include "state.h"

ServoAdapter::ServoAdapter(const char* objName) {
    strncpy(_objName, objName, sizeof(_objName) - 1);
    _objName[sizeof(_objName) - 1] = '\0';
}

void ServoAdapter::setAngle(Servos::Name name, int angle){
    if(angle < Servos::minAngle(name) ) {
        LOG_ERR_F("%s.setAngle() параметр angle не может быть менее чем %d", _objName, (int)Servos::minAngle(name));
        return;
    }
    if(angle > Servos::maxAngle(name)) {
        LOG_ERR_F("%s.setAngle() параметр angle не может быть более чем %d", _objName, (int)Servos::maxAngle(name));
        return;
    }
    State::setServoAngle(name, angle);
}

int ServoAdapter::getAngle(Servos::Name name){
    return (int)State::getServoAngle(name);
}

void ServoAdapter::goHome(){
    for(uint8_t i = 0; i < Servos::Name::COUNT; i++){
        Servos::Name name = Servos::getName(i);
        State::setServoAngle(name, Servos::initAngle(name));
    }
}
