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
#include "ConnectorManager.h"

const char* ConnectorManager::_owners[Connector::Name::COUNT] = {};

bool ConnectorManager::claim(Connector::Name port, const char* owner) {
    if (_owners[port] != nullptr) {
        LOG_ERR_F("Разъём %s занят \"%s\", запрашивает \"%s\"",
                  Connector::text(port), _owners[port], owner);
        return false;
    }
    _owners[port] = owner;
    return true;
}

void ConnectorManager::release(Connector::Name port) {
    _owners[port] = nullptr;
}

const char* ConnectorManager::getOwner(Connector::Name port) {
    return _owners[port];
}