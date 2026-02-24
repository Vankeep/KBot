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
#include "RgbLedAdapter.h"
#include <M5Unified.h>

RgbLedAdapter::RgbLedAdapter(const char* objName) {
    strncpy(_objName, objName, sizeof(_objName) - 1);
    _objName[sizeof(_objName) - 1] = '\0';
}

void RgbLedAdapter::begin(Pins::Name name, int numLeds) {
    if(numLeds < 1) {
        LOG_ERR_F("%s.begin() Аргумент numLeds не может быть менее 1", _objName);
        return;
    };
    if(_isBegin == true) {
        LOG_ERR_F("%s уже проинициализирован. Повторная инициализация игнорируется", _objName);
        return;
    }

    uint8_t pin = Pins::rigthPin(name);
    _numLeds = numLeds;

    _pixels = new Adafruit_NeoPixel(_numLeds, pin, NEO_GRB + NEO_KHZ800);
    _pixels->begin();
    _pixels->setBrightness(50);
    _pixels->clear();
    _pixels->show();

    _isBegin = true;

    LOG_INFO_F("%s проинициализирован", _objName);
}

void RgbLedAdapter::tick() {
    if(_isBegin == false) return;
    if(_dirty == false) return;
    _pixels->show();
    _dirty = false;
}

void RgbLedAdapter::setColor(int pixel, int r, int g, int b) {
    if(_isBeginAdapter() == false) return;
    if(_isValideRgb(r, g, b) == false) return;
    if(pixel < 1){
        LOG_ERR_F("%s.setColor() Аргумент pixel не может быть менее 1", _objName);
        return;
    }

    if(pixel < 1 || pixel > _numLeds) return;
    _pixels->setPixelColor(pixel - 1, _pixels->Color(r, g, b));
    _dirty = true;
}

void RgbLedAdapter::setColor(int pixel, Led::Color color) {
    if(_isBeginAdapter() == false) return;
    if(pixel < 1){
        LOG_ERR_F("%s.setColor() Аргумент pixel не может быть менее 1", _objName);
        return;
    }

    if(pixel < 1 || pixel > _numLeds) return;
    _pixels->setPixelColor(pixel - 1, color);
    _dirty = true;
}

void RgbLedAdapter::setColorAll(int r, int g, int b) {
    if(_isBeginAdapter() == false) return;
    if(_isValideRgb(r, g, b) == false) return;

    uint32_t color = _pixels->Color(r, g, b);
    for(uint16_t i = 0; i < _numLeds; i++) {
        _pixels->setPixelColor(i, color);
    }
    _dirty = true;
}

void RgbLedAdapter::setColorAll(Led::Color color) {
    if(_isBeginAdapter() == false) return;

    for(uint16_t i = 0; i < _numLeds; i++) {
        _pixels->setPixelColor(i, color);
    }
    _dirty = true;
}

void RgbLedAdapter::setBrightness(int brightness) {
    if(_isBeginAdapter() == false) return;
    if(brightness < 0 || brightness > 255){
        LOG_ERR_F("%s.setBrightness() Аргумент brightness не может быть менее 0 или более 255", _objName);
        return;
    }
    
    _pixels->setBrightness(brightness);
    _dirty = true;
}

void RgbLedAdapter::clear() {
    if(_isBeginAdapter() == false) return;
    _pixels->clear();
    _dirty = true;
}

int RgbLedAdapter::getNumLeds() const {
    if(_isBeginAdapter() == false) return -1;
    return _numLeds;
}

bool RgbLedAdapter::_isValideRgb(int r, int g, int b) const {
    if(r >= 0 || g >= 0 || b >= 0 || r <= 255 || g <= 255 || b <= 255){
        return true;
    } else {
        LOG_ERR_F("%s Цвет не может быть менее 0 или более 255", _objName);
        return false;
    }
}

bool RgbLedAdapter::_isBeginAdapter() const {
    if(_isBegin == false) {
        LOG_ERR_F("%s не было вызова begin(). Класс не проинициализирован", _objName);
    }
    return _isBegin;
}