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
#include "config.h"
#include "serial_controller.h"
#include "servo_controller.h"
#include "state.h"

void SerialController::init(ServoController& servoController){
  _instance = this;
  _servoController = &servoController;
  Serial2.begin(SERIAL_PROTOCOL_BAUD, SERIAL_8N1, 18, 17);
  Serial2.flush();
  _serialTransfer.begin(Serial2);
  _stateSendRequested = false;
  _lastPingTime = millis();
}

bool SerialController::available() {
  uint32_t currentTime = millis();
  if (currentTime - _lastPingTime > PING_TIMEOUT_MS) {
    State::init();
    _lastPingTime = currentTime;
  }
  if (_serialTransfer.available()) {
    PacketType type = (PacketType)_serialTransfer.currentPacketID();

    switch(type) {
      case PING:
        _lastPingTime = currentTime;
        break;
      case STATE:
        _parceStatePacket();
        _lastPingTime = currentTime;
        break;
      case GET_STATE:
        sendState();
        _lastPingTime = currentTime;
        break;
      default:
        return false;
    }
    return true;
  }
  return false;
}

void SerialController::_parceStatePacket(){
  uint16_t recSize = 0;
  StatePacket packet;
  recSize = _serialTransfer.rxObj(packet, recSize);
  
  // скорость моторов
  for(uint8_t i = 0; i < Wheel::Name::COUNT; i++){
    Wheel::Name name = Wheel::getName(i);
    State::setWheelSpeed(name, packet.wheelSpeed[i]);
  }
  
  // углы сервы
  _servoController->setTargetAngles(packet.servoAngle);
 
  // диоды
  for(uint8_t i = 0; i < Led::Name::COUNT; i++){
    Led::Name name = Led::getName(i);
    State::setLedColor(name, packet.ledColor[i]);
  }
}

void SerialController::sendState(){
  uint16_t sendSize = 0;
  sendSize = _instance->_serialTransfer.txObj(State::getStatePacket(), sendSize);
  _instance->_serialTransfer.sendData(sendSize, static_cast<uint8_t>(PacketType::STATE));
  
#ifdef SERIAL_STATE_DEBUG
    Serial.println("----------------------------------------------------------");
    Serial.println("Моторы:");
    Serial.print("");
    Serial.print(State::getWheelSpeed(Wheel::Name::XP14A));
    Serial.print(" | 15A=");
    Serial.print(State::getWheelSpeed(Wheel::Name::XP15A));
    Serial.print(" | 14B=");
    Serial.print(State::getWheelSpeed(Wheel::Name::XP14B));
    Serial.print(" | 15B=");
    Serial.println(State::getWheelSpeed(Wheel::Name::XP15B));
    Serial.println("Сервоприводы:");
    Serial.print("SRV1=");
    Serial.print(State::getServoAngle(Servos::Name::SRV1));
    Serial.print(" | SRV2=");
    Serial.print(State::getServoAngle(Servos::Name::SRV2));
    Serial.print(" | SRV3=");
    Serial.print(State::getServoAngle(Servos::Name::SRV3));
    Serial.print(" | SRV4=");
    Serial.println(State::getServoAngle(Servos::Name::SRV4));
    Serial.println("Светодиоды:");
    for(uint8_t i = 0; i < Servos::Name::COUNT; i++){
      Serial.print("  ledColor ");
      Serial.print(i);
      Serial.print(": 0x");
      Serial.println(State::getLedColor(Led::getName(i)), HEX);
    }
#endif
}

SerialController* SerialController::_instance = nullptr;