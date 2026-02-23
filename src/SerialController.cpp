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
#include "SerialController.h"
#include "state.h"

void SerialController::init(){
    _instance = this;
    Serial2.begin(SERIAL_PROTOCOL_BAUD, SERIAL_8N1, 13, 14);
    Serial2.flush();
    delay(50);
    _serialTransfer.begin(Serial2);

    _lastPingTime = millis();
    _stateSentThisCycle = false;
}

void SerialController::sendState(){
    uint16_t sendSize = 0;
    sendSize = _instance->_serialTransfer.txObj(State::getStatePacket(), sendSize);
    _instance->_serialTransfer.sendData(sendSize, static_cast<uint8_t>(PacketType::STATE));
    _instance->_stateSentThisCycle = true;
}

void SerialController::update() {
    if (_serialTransfer.available()) {
        PacketType type = (PacketType)_serialTransfer.currentPacketID();

        switch(type) {
            case STATE:
                _parceStatePacket();
                break;
            case GET_STATE:
                sendState();
                break;
            default:
                break;
        }
    }
    if (!_stateSentThisCycle && millis() - _lastPingTime >= PING_INTERVAL_MS) {
        PingPacket ping{true};
        uint16_t sendSize = 0;
        sendSize = _serialTransfer.txObj(ping, sendSize);
        _serialTransfer.sendData(sendSize, static_cast<uint8_t>(PacketType::PING));
        _lastPingTime = millis();
    }
    _stateSentThisCycle = false;
}

void SerialController::_parceStatePacket(){
    uint16_t recSize = 0;
    StatePacket packet;
    recSize = _serialTransfer.rxObj(packet, recSize);
    State::setStatePacketDirect(packet); 
}



SerialController* SerialController::_instance = nullptr;