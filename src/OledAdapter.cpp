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
#include "OledAdapter.h"
#include "config.h"

#define SERIAL_Y      140
#define SERIAL_H      100
#define LINE_H        22
#define LINE_PAD      3

void OledAdapter::begin() {
    // тень под контейнером
    M5.Lcd.fillRoundRect(2, SERIAL_Y + 2, 318, SERIAL_H, 6, 0x1082);
    // основной контейнер
    M5.Lcd.fillRoundRect(0, SERIAL_Y, 318, SERIAL_H, 6, 0x18E3);
    // тонкая рамка
    M5.Lcd.drawRoundRect(0, SERIAL_Y, 318, SERIAL_H, 6, 0x3186);

    LOG_INFO("Oled проинициализирован");
}

void OledAdapter::printStr1(const String& text) { _drawLine(1, text.c_str()); }
void OledAdapter::printStr1(const char* text) { _drawLine(1, text); }
void OledAdapter::printStr1(int value) { _drawLine(1, String(value).c_str()); }
void OledAdapter::printStr1(long value) { _drawLine(1, String(value).c_str()); }
void OledAdapter::printStr1(float value, uint8_t decimals) { _drawLine(1, String(value, (unsigned int)decimals).c_str()); }
void OledAdapter::printStr1(double value, uint8_t decimals) { _drawLine(1, String(value, (unsigned int)decimals).c_str()); }

void OledAdapter::printStr2(const String& text) { _drawLine(2, text.c_str()); }
void OledAdapter::printStr2(const char* text) { _drawLine(2, text); }
void OledAdapter::printStr2(int value) { _drawLine(2, String(value).c_str()); }
void OledAdapter::printStr2(long value) { _drawLine(2, String(value).c_str()); }
void OledAdapter::printStr2(float value, uint8_t decimals) { _drawLine(2, String(value, (unsigned int)decimals).c_str()); }
void OledAdapter::printStr2(double value, uint8_t decimals) { _drawLine(2, String(value, (unsigned int)decimals).c_str()); }

void OledAdapter::printStr3(const String& text) { _drawLine(3, text.c_str()); }
void OledAdapter::printStr3(const char* text) { _drawLine(3, text); }
void OledAdapter::printStr3(int value) { _drawLine(3, String(value).c_str()); }
void OledAdapter::printStr3(long value) { _drawLine(3, String(value).c_str()); }
void OledAdapter::printStr3(float value, uint8_t decimals) { _drawLine(3, String(value, (unsigned int)decimals).c_str()); }
void OledAdapter::printStr3(double value, uint8_t decimals) { _drawLine(3, String(value, (unsigned int)decimals).c_str()); }

void OledAdapter::printStr4(const String& text) { _drawLine(4, text.c_str()); }
void OledAdapter::printStr4(const char* text) { _drawLine(4, text); }
void OledAdapter::printStr4(int value) { _drawLine(4, String(value).c_str()); }
void OledAdapter::printStr4(long value) { _drawLine(4, String(value).c_str()); }
void OledAdapter::printStr4(float value, uint8_t decimals) { _drawLine(4, String(value, (unsigned int)decimals).c_str()); }
void OledAdapter::printStr4(double value, uint8_t decimals) { _drawLine(4, String(value, (unsigned int)decimals).c_str()); }

void OledAdapter::clear() { init(); }

void OledAdapter::_drawLine(uint8_t line, const char* text) {
    int16_t y = SERIAL_Y + 4 + (line - 1) * (LINE_H + LINE_PAD);
    // очистка строки
    M5.Lcd.fillRect(6, y, 306, LINE_H, 0x18E3);
    // маркер строки маленький кружок
    M5.Lcd.fillCircle(12, y + LINE_H / 2, 3, 0x4A69);
    // текст
    M5.Lcd.setTextColor(0xDEFB, 0x18E3);   // светло-серый на тёмном
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextDatum(ML_DATUM);
    M5.Lcd.drawString(text, 22, y + LINE_H / 2);
}