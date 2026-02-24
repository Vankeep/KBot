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
#include "config.h"

// Предотвращает назначение двух устройств на один разъём.
// Использование в адаптерах — одна строка в begin():
// if (!ConnectorManager::claim(name, _objName)) return;

class ConnectorManager {
public:
    static bool claim(Connector::Name name, const char* owner);
    static void release(Connector::Name name);
    static const char* getOwner(Connector::Name name);

private:
    static const char* _owners[Connector::Name::COUNT];
};