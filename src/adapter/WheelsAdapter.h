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
#pragma once
#include "BaseAdapter.h"
#include "config.h"

class WheelsAdapter : public BaseAdapter{
public:
    WheelsAdapter(const char* objName) : BaseAdapter(objName) {}
    void drive(int left, int right);
    void drive(Wheel::Name name, int speed);
    void stop(Wheel::Name name);
    void stopAll();

private:
    bool _isValidateSpeed(int speed, const char* paramName);
};
