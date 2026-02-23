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
#include "MboardLedAdapter.h"
#include "state.h"

void MboardLedAdapter::color(Led::Name name, int red, int green, int blue){
    if(!_isValide(red, green, blue)) return;
    State::setLedColor(name, _getColorUint(red, green, blue));
}

void MboardLedAdapter::color(Led::Name name, Led::Color color){
    State::setLedColor(name, color);
}

void MboardLedAdapter::colorAll(Led::Color color){
    for(uint8_t i = 0; i < Led::Name::COUNT; i++){
        State::setLedColor(Led::getName(i), color);
    }
}

void MboardLedAdapter::off(Led::Name name){
    State::setLedColor(name, Led::Color::BLACK);
}

void MboardLedAdapter::offAll(){
    for(uint8_t i = 0; i < Led::Name::COUNT; i++){
        State::setLedColor(Led::getName(i), Led::Color::BLACK);
    }
}

bool MboardLedAdapter::_isValide(int red, int green, int blue){
    return (red >= 0  && red <= 255) && (green >=0 && green <=255) && (blue >=0 && blue <=255);
}
