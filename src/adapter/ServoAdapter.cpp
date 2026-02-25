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

void ServoAdapter::begin(ServoPin::Name name){
    if(_isBegin == true) {
        LOG_ERR_F("%s уже проинициализирован. Повторная инициализация игнорируется", _objName);
        return;
    }
    _name = name;
    // TODO реализовать проверку State на предмет инициализации
    _isBegin = true;
    LOG_INFO_F("%s проинициализирован", _objName);
}

void ServoAdapter::setAngle(int angle){
    if(angle < ServoPin::minAngle(_name) ) {
        LOG_ERR_F("%s.setAngle() параметр angle не может быть менее чем %d", _objName, (int)ServoPin::minAngle(_name));
        return;
    }
    if(angle > ServoPin::maxAngle(_name)) {
        LOG_ERR_F("%s.setAngle() параметр angle не может быть более чем %d", _objName, (int)ServoPin::maxAngle(_name));
        return;
    }
    State::setServoAngle(_name, angle);
}

int ServoAdapter::getAngle(){
    return (int)State::getServoAngle(_name);
}

void ServoAdapter::goHome(){
    State::setServoAngle(_name, ServoPin::initAngle(_name));
}
