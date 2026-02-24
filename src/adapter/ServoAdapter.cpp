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

void ServoAdapter::setAngle(ServoPins::Name name, int angle){
    if(angle < ServoPins::minAngle(name) ) {
        LOG_ERR_F("%s.setAngle() параметр angle не может быть менее чем %d", _objName, (int)ServoPins::minAngle(name));
        return;
    }
    if(angle > ServoPins::maxAngle(name)) {
        LOG_ERR_F("%s.setAngle() параметр angle не может быть более чем %d", _objName, (int)ServoPins::maxAngle(name));
        return;
    }
    State::setServoAngle(name, angle);
}

int ServoAdapter::getAngle(ServoPins::Name name){
    return (int)State::getServoAngle(name);
}

void ServoAdapter::goHome(){
    for(uint8_t i = 0; i < ServoPins::Name::COUNT; i++){
        ServoPins::Name name = ServoPins::getName(i);
        State::setServoAngle(name, ServoPins::initAngle(name));
    }
}
