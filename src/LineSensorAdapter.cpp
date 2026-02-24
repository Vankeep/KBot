#include "LineSensorAdapter.h"

void LineSensorAdapter::begin(Pins::Name name) {
    if (name == Pins::Name::XP8  || name == Pins::Name::XP10 || 
        name == Pins::Name::XP11 || name == Pins::Name::XP13) {
        if(_isBegin == true) {
            LOG_INFO_F("%s уже проинициализирован. Повторная инициализация игнорируется", _objName);
            return;
        }
        _pin = Pins::leftPin(name);
        pinMode(_pin, INPUT);

        _emaScaled   = analogRead(_pin) * EMA_DEN;

        _isOnLine = false;
        _wasOnLine = false;
        _detected = false;
        _lost = false;
        _candidate = false;
        _stableCount = 0;
        _isBegin = true;
        LOG_INFO_F("%s проинициализирован", _objName);
    } else {
        LOG_ERR_F("%s Неподдерживаемый пин: %d Используйте XP8, XP10, XP11 или XP13", _objName, (int)name);
    }
}

void LineSensorAdapter::tick() {
    if (!_isBegin) return;

    _detected = false;
    _lost     = false;

    int raw = _readMedian();

    _emaScaled += (static_cast<int32_t>(raw) * EMA_DEN - _emaScaled) * EMA_NUM / EMA_DEN;
    int filtered = _emaScaled / EMA_DEN;

    bool rawState;
    if (filtered < THRESHOLD_LOW) {
        rawState = true; 
    } else if (filtered > THRESHOLD_HIGH) {
        rawState = false;
    } else {
        rawState = _isOnLine;
    }

    if (rawState != _isOnLine) {
        if (rawState == _candidate) {
            _stableCount++;
        } else {
            _candidate   = rawState;
            _stableCount = 1;
        }

        if (_stableCount >= DEBOUNCE_COUNT) {
            _wasOnLine = _isOnLine;
            _isOnLine  = rawState;

            if (_isOnLine && !_wasOnLine) {
                _detected = true;
            }
            if (!_isOnLine && _wasOnLine) {
                _lost = true;
            }

            _stableCount = 0;
        }
    } else {
        _candidate   = _isOnLine;
        _stableCount = 0;
    }
}

bool LineSensorAdapter::isOnLine() {
    if(!_isBeginAdapter()) return false;
    return _isOnLine;
}

bool LineSensorAdapter::isDetected() {
    if(!_isBeginAdapter()) return false;
    return _detected;
}

bool LineSensorAdapter::isLost() {
    if(!_isBeginAdapter()) return false;
    return _lost;
}

int LineSensorAdapter::_readMedian() {
    int buf[ADC_SAMPLES];

    for (uint8_t i = 0; i < ADC_SAMPLES; i++) {
        buf[i] = analogRead(_pin);
    }

    for (uint8_t i = 1; i < ADC_SAMPLES; i++) {
        int key = buf[i];
        int8_t j = i - 1;
        while (j >= 0 && buf[j] > key) {
            buf[j + 1] = buf[j];
            j--;
        }
        buf[j + 1] = key;
    }

    return buf[ADC_SAMPLES / 2];
}