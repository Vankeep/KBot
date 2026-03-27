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
#include <M5Unified.h>
#include <WiFi.h>
#include <WebServer.h>
#include "lib/WebSockets/WebSocketsServer.h"

class WifiControlPanelAdapter : public BaseAdapter {
public:
    WifiControlPanelAdapter(const char* objName) : BaseAdapter(objName) {}
    
    void begin(
        const char* ssid = "kbot",
        const char* password = "12345678",
        IPAddress ip = IPAddress(10, 0, 0, 1),
        IPAddress gateway = IPAddress(10, 0, 0, 1),
        IPAddress subnet = IPAddress(255, 255, 255, 0)
    );
    
    void tick();
    void getMotorValues(int& left, int& right);
    
    String getIPAddress();
    String getSSID();
    String getPassword();
    String getGateway();
    String getSubnet();

private:
    void _initWifi(const char* ssid, const char* password, IPAddress ip, IPAddress gateway, IPAddress subnet);
    void _handleRoot();
    void _onWebSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length);

    WebServer* _server = nullptr;
    WebSocketsServer* _webSocket = nullptr;
    
    int _leftMotor = 0;
    int _rightMotor = 0;
    unsigned long _lastUpdateTime = 0;
    static const unsigned long TIMEOUT_MS = 500;
    
    String _ssid;
    String _password;
    IPAddress _gateway;
    IPAddress _subnet;
};