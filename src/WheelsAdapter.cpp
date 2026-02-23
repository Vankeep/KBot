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
#include "WheelsAdapter.h"
#include "state.h"

void WheelsAdapter::drive(int left, int right){
    if( left > WHEEL_SPEED_MAX || left < WHEEL_SPEED_MIN ||
        right > WHEEL_SPEED_MAX || right < WHEEL_SPEED_MIN){ return; }

        State::setWheelSpeed(Wheel::Name::XP14A, left);
        State::setWheelSpeed(Wheel::Name::XP14B, left);
        State::setWheelSpeed(Wheel::Name::XP15A, right);
        State::setWheelSpeed(Wheel::Name::XP15B, right);
}

void WheelsAdapter::drive(Wheel::Name name, int speed){
    if(speed > WHEEL_SPEED_MAX || speed < WHEEL_SPEED_MIN ) return;
    State::setWheelSpeed(name, speed);
}

void WheelsAdapter::stop(Wheel::Name name){
    State::setWheelSpeed(name, 0);
}

void WheelsAdapter::stopAll(){
    State::setWheelSpeed(Wheel::Name::XP14A, 0);
    State::setWheelSpeed(Wheel::Name::XP14B, 0);
    State::setWheelSpeed(Wheel::Name::XP15A, 0);
    State::setWheelSpeed(Wheel::Name::XP15B, 0);
}
