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
#include "SonicAdapter.h"

void SonicAdapter::begin() { 
    _sensor.begin(); 
    // TODO передалать класс по принципу остальных. Внедрить библиотеку https://github.com/m5stack/M5Unit-Sonic/blob/master/src/Unit_Sonic.h
}

long SonicAdapter::getDistanceMm(){
    // TODO добавить проверку на инициализиацию
   long distance = (long)_sensor.getDistance();
   if (distance >= 4500) {
       return _lastDistance;
   } else {
       _lastDistance = distance;
       return distance;
   }
}
