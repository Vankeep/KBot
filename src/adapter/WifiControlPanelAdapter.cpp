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
#include "WifiControlPanelAdapter.h"

void WifiControlPanelAdapter::begin(
    const char* ssid,
    const char* password,
    IPAddress ip,
    IPAddress gateway,
    IPAddress subnet
) {
    _isBegin = true;
    
    _ssid = String(ssid);
    _password = String(password);
    _gateway = gateway;
    _subnet = subnet;
    
    _initWifi(ssid, password, ip, gateway, subnet);
    LOG_INFO_F("%s проинициализирован", _objName);
}

void WifiControlPanelAdapter::tick() {
    if (_isBegin == false) return;
    
    if (_server) _server->handleClient();
    
    if (_webSocket) _webSocket->loop();

    if (millis() - _lastUpdateTime > TIMEOUT_MS) {
        _leftMotor = 0;
        _rightMotor = 0;
    }
}

void WifiControlPanelAdapter::getMotorValues(int& left, int& right) {
    if (_isBegin == false) return;
    left = _leftMotor;
    right = _rightMotor;
}

String WifiControlPanelAdapter::getIPAddress() {
    if (_isBegin == false) return "";
    return WiFi.softAPIP().toString();
}

String WifiControlPanelAdapter::getSSID() {
    if (_isBegin == false) return "";
    return _ssid;
}

String WifiControlPanelAdapter::getPassword() {
    if (_isBegin == false) return "";
    return _password;
}

String WifiControlPanelAdapter::getGateway() {
    if (_isBegin == false) return "";
    return _gateway.toString();
}

String WifiControlPanelAdapter::getSubnet() {
    if (_isBegin == false) return "";
    return _subnet.toString();
}

void WifiControlPanelAdapter::_initWifi(
    const char* ssid,
    const char* password,
    IPAddress ip,
    IPAddress gateway,
    IPAddress subnet
) {
    if (_isBegin == false) return;
    
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(ip, gateway, subnet);
    WiFi.softAP(ssid, password);

    LOG_INFO_F("WiFi точка доступа запущена: %s", ssid);
    LOG_INFO_F("IP адрес: %s", WiFi.softAPIP().toString().c_str());

    _server = new WebServer(80);
    _server->on("/", [this]() { _handleRoot(); });
    _server->begin();
    LOG_INFO("Веб-сервер запущен на порту 80");

    _webSocket = new WebSocketsServer(81);
    _webSocket->begin();
    _webSocket->onEvent([this](uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
        _onWebSocketEvent(num, type, payload, length);
    });
    LOG_INFO("WebSocket сервер запущен на порту 81");
}

void WifiControlPanelAdapter::_onWebSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
    switch (type) {
        case WStype_DISCONNECTED:
            LOG_INFO_F("WebSocket клиент #%u отключен", num);
            break;
            
        case WStype_CONNECTED:
            LOG_INFO_F("WebSocket клиент #%u подключен", num);
            break;
            
        case WStype_TEXT: {
            String data = String((char*)payload);
            int commaIndex = data.indexOf(',');
            
            if (commaIndex > 0) {
                _leftMotor = data.substring(0, commaIndex).toInt();
                _rightMotor = data.substring(commaIndex + 1).toInt();
                _lastUpdateTime = millis();
            }
            break;
        }
        
        default:
            break;
    }
}

void WifiControlPanelAdapter::_handleRoot() {
    if (_isBegin == false) return;
    
    const char* html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
    <title>КБОТ Пульт</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body {
            font-family: Arial, sans-serif;
            background: linear-gradient(145deg, #2a3638 0%, #374548 50%, #2a3638 100%);
            color: #fff;
            overflow: hidden;
            touch-action: none;
            min-height: 100vh;
        }
        #container {
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            height: 100vh;
            padding: 20px;
        }
        h1 {
            font-size: 28px;
            font-weight: 300;
            margin-bottom: 8px;
            color: #ffffff;
            letter-spacing: 3px;
            text-transform: uppercase;
        }
        h1 span {
            color: #7ee0e5;
            font-weight: 700;
        }
        #status {
            font-size: 11px;
            margin-bottom: 15px;
            padding: 6px 16px;
            border-radius: 20px;
            background: rgba(0,0,0,0.3);
            text-transform: uppercase;
            letter-spacing: 1px;
        }
        #status.connected { 
            color: #7ee0e5;
            box-shadow: 0 0 15px rgba(126, 224, 229, 0.3);
        }
        #status.disconnected { 
            color: #ce2937;
            box-shadow: 0 0 15px rgba(206, 41, 55, 0.3);
        }
        #joystick-area {
            width: 260px;
            height: 260px;
            background: radial-gradient(circle at center, rgba(126,224,229,0.05) 0%, rgba(0,0,0,0.3) 70%);
            border-radius: 50%;
            position: relative;
            border: 2px solid rgba(126,224,229,0.3);
            margin-bottom: 0px;
            box-shadow: 
                0 0 40px rgba(0,0,0,0.4),
                inset 0 0 30px rgba(0,0,0,0.3);
        }
        #joystick-area::before {
            content: '';
            position: absolute;
            top: 50%;
            left: 10%;
            right: 10%;
            height: 1px;
            background: linear-gradient(90deg, transparent, rgba(126,224,229,0.2), transparent);
        }
        #joystick-area::after {
            content: '';
            position: absolute;
            left: 50%;
            top: 10%;
            bottom: 10%;
            width: 1px;
            background: linear-gradient(180deg, transparent, rgba(126,224,229,0.2), transparent);
        }
        #joystick {
            width: 80px;
            height: 80px;
            background: linear-gradient(145deg, #7ee0e5, #2a90a6);
            border-radius: 50%;
            position: absolute;
            top: 50%;
            left: 50%;
            transform: translate(-50%, -50%);
            cursor: pointer;
            box-shadow: 
                0 4px 15px rgba(0,0,0,0.4),
                0 0 30px rgba(126, 224, 229, 0.4),
                inset 0 2px 10px rgba(255,255,255,0.2);
            border: 2px solid rgba(255,255,255,0.2);
            transition: box-shadow 0.1s ease;
        }
        #joystick:active {
            box-shadow: 
                0 2px 10px rgba(0,0,0,0.4),
                0 0 40px rgba(126, 224, 229, 0.6),
                inset 0 2px 10px rgba(255,255,255,0.2);
        }
        #info {
            font-family: monospace;
            font-size: 16px;
            text-align: center;
            color: rgba(255,255,255,0.5);
            margin-top: 20px;
        }
        .value { 
            color: #7ee0e5; 
        }
        
        #controls-container {
            width: 260px;
            text-align: center;
            margin-bottom: 20px;
        }
        .slider-group {
            margin-bottom: 12px;
        }
        .slider-label {
            font-size: 12px;
            color: rgba(255,255,255,0.5);
            margin-bottom: 6px;
            display: flex;
            justify-content: space-between;
            padding: 0 5px;
        }
        .slider-value {
            color: #7ee0e5;
            font-weight: bold;
        }
        .slider {
            -webkit-appearance: none;
            appearance: none;
            width: 100%;
            height: 6px;
            border-radius: 3px;
            background: rgba(0,0,0,0.3);
            outline: none;
            border: 1px solid rgba(126,224,229,0.2);
        }
        .slider::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            width: 20px;
            height: 20px;
            border-radius: 50%;
            background: linear-gradient(145deg, #7ee0e5, #2a90a6);
            cursor: pointer;
            box-shadow: 0 2px 6px rgba(0,0,0,0.3);
            border: 2px solid rgba(255,255,255,0.2);
        }
        .slider::-moz-range-thumb {
            width: 20px;
            height: 20px;
            border-radius: 50%;
            background: linear-gradient(145deg, #7ee0e5, #2a90a6);
            cursor: pointer;
            box-shadow: 0 2px 6px rgba(0,0,0,0.3);
            border: 2px solid rgba(255,255,255,0.2);
        }
        #reverse-container {
            display: flex;
            align-items: center;
            justify-content: center;
            gap: 8px;
            margin-top: 8px;
            cursor: pointer;
        }
        #reverse-container input {
            display: none;
        }
        #reverse-container .checkbox-custom {
            width: 20px;
            height: 20px;
            border: 2px solid rgba(126, 224, 229, 0.4);
            border-radius: 4px;
            display: flex;
            align-items: center;
            justify-content: center;
            transition: all 0.2s ease;
        }
        #reverse-container input:checked + .checkbox-custom {
            background: #7ee0e5;
            border-color: #7ee0e5;
            box-shadow: 0 0 10px rgba(126, 224, 229, 0.4);
        }
        #reverse-container .checkbox-custom::after {
            content: '';
            width: 6px;
            height: 10px;
            border: solid #374548;
            border-width: 0 2px 2px 0;
            transform: rotate(45deg) translateY(-1px);
            opacity: 0;
            transition: opacity 0.2s ease;
        }
        #reverse-container input:checked + .checkbox-custom::after {
            opacity: 1;
        }
        #reverse-container span {
            font-size: 12px;
            color: rgba(255,255,255,0.5);
        }
    </style>
</head>
<body>
    <div id="container">
        <h1>КБОТ <span>ПУЛЬТ</span></h1>
        <div id="status" class="disconnected">Подключение...</div>
        <div id="controls-container">
            <div class="slider-group">
                <div class="slider-label">
                    Макс. скорость: <span class="slider-value" id="speed-value">45%</span>
                </div>
                <input type="range" class="slider" id="max-speed" min="10" max="100" value="45">
            </div>
            <div class="slider-group">
                <div class="slider-label">
                    Макс. скороть поворота: <span class="slider-value" id="turn-value">40%</span>
                </div>
                <input type="range" class="slider" id="max-turn" min="10" max="100" value="40">
            </div>
            <label id="reverse-container">
                <input type="checkbox" id="reverse">
                <div class="checkbox-custom"></div>
                <span>Реверс</span>
            </label>
        </div>
        <div id="joystick-area">
            <div id="joystick"></div>
        </div>
        <div id="info">
            L: <span class="value" id="left">0</span> |
            R: <span class="value" id="right">0</span>
        </div>
    </div>
    <script>
        const area = document.getElementById('joystick-area');
        const joystick = document.getElementById('joystick');
        const leftDisplay = document.getElementById('left');
        const rightDisplay = document.getElementById('right');
        const statusEl = document.getElementById('status');
        const maxSpeedSlider = document.getElementById('max-speed');
        const speedValueEl = document.getElementById('speed-value');
        const maxTurnSlider = document.getElementById('max-turn');
        const turnValueEl = document.getElementById('turn-value');
        const reverseCheckbox = document.getElementById('reverse');

        let isDragging = false;
        let centerX = area.offsetWidth / 2;
        let centerY = area.offsetHeight / 2;
        let maxRadius = (area.offsetWidth / 2) - 40;
        let maxSpeed = 1.0;
        let maxTurn = 1.0;
        let currentLeft = 0;
        let currentRight = 0;
        let sendInterval = null;

        let ws = null;
        let reconnectInterval = null;

        function connectWebSocket() {
            const host = window.location.hostname;
            ws = new WebSocket('ws://' + host + ':81');

            ws.onopen = function() {
                statusEl.textContent = 'Подключено';
                statusEl.className = 'connected';
                if (reconnectInterval) {
                    clearInterval(reconnectInterval);
                    reconnectInterval = null;
                }
                sendInterval = setInterval(function() {
                    sendMotorValues(currentLeft, currentRight);
                }, 100);
            };

            ws.onclose = function() {
                statusEl.textContent = 'Отключено';
                statusEl.className = 'disconnected';
                if (sendInterval) {
                    clearInterval(sendInterval);
                    sendInterval = null;
                }

                if (!reconnectInterval) {
                    reconnectInterval = setInterval(connectWebSocket, 2000);
                }
            };

            ws.onerror = function() {
                ws.close();
            };
        }

        connectWebSocket();

        maxSpeedSlider.addEventListener('input', function() {
            maxSpeed = this.value / 100;
            speedValueEl.textContent = this.value + '%';
        });

        maxTurnSlider.addEventListener('input', function() {
            maxTurn = this.value / 100;
            turnValueEl.textContent = this.value + '%';
        });

        function sendMotorValues(left, right) {
            if (ws && ws.readyState === WebSocket.OPEN) {
                ws.send(left + ',' + right);
            }
        }

        function updateJoystick(x, y) {
            let dx = x - centerX;
            let dy = y - centerY;
            let distance = Math.sqrt(dx * dx + dy * dy);

            if (distance > maxRadius) {
                let angle = Math.atan2(dy, dx);
                dx = Math.cos(angle) * maxRadius;
                dy = Math.sin(angle) * maxRadius;
            }

            joystick.style.left = (centerX + dx) + 'px';
            joystick.style.top = (centerY + dy) + 'px';
            joystick.style.transform = 'translate(-50%, -50%)';

            let normalizedDy = (dy / maxRadius) * maxSpeed;
            let normalizedDx = (dx / maxRadius) * maxTurn;

            let forward = -Math.round(normalizedDy * 200);
            let turn = -Math.round(normalizedDx * 200);

            if (reverseCheckbox.checked) {
                forward = -forward;
            }

            let left = forward + turn;
            let right = forward - turn;

            left = Math.max(-200, Math.min(200, left));
            right = Math.max(-200, Math.min(200, right));

            currentLeft = left;
            currentRight = right;

            leftDisplay.textContent = currentLeft;
            rightDisplay.textContent = currentRight;
        }

        function resetJoystick() {
            joystick.style.left = '50%';
            joystick.style.top = '50%';
            currentLeft = 0;
            currentRight = 0;
            leftDisplay.textContent = '0';
            rightDisplay.textContent = '0';
        }

        function handleStart(e) {
            e.preventDefault();
            isDragging = true;
        }

        function handleMove(e) {
            if (!isDragging) return;
            e.preventDefault();

            const rect = area.getBoundingClientRect();
            const touch = e.touches ? e.touches[0] : e;
            const x = touch.clientX - rect.left;
            const y = touch.clientY - rect.top;

            updateJoystick(x, y);
        }

        function handleEnd(e) {
            e.preventDefault();
            isDragging = false;
            resetJoystick();
        }

        joystick.addEventListener('touchstart', handleStart);
        area.addEventListener('touchmove', handleMove);
        area.addEventListener('touchend', handleEnd);

        joystick.addEventListener('mousedown', handleStart);
        document.addEventListener('mousemove', handleMove);
        document.addEventListener('mouseup', handleEnd);

        window.addEventListener('resize', () => {
            centerX = area.offsetWidth / 2;
            centerY = area.offsetHeight / 2;
            maxRadius = (area.offsetWidth / 2) - 45;
        });
    </script>
</body>
</html>
)rawliteral";

    _server->send(200, "text/html", html);
}