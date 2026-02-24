  #include "BaseAdapter.h"

  BaseAdapter::BaseAdapter(const char* objName) {
      strncpy(_objName, objName, sizeof(_objName) - 1);
      _objName[sizeof(_objName) - 1] = '\0';
  }

  bool BaseAdapter::_isBeginAdapter() const {
      if(_isBegin == false) {
          LOG_ERR_F("%s не было вызова begin() Класс не проинициализирован", _objName);
      }
      return _isBegin;
  }
