  #pragma once
  #include "../config.h"

  class BaseAdapter {
  protected:
      char _objName[32];
      bool _isBegin = false;

      BaseAdapter(const char* objName);
      bool _isBeginAdapter() const;
  };
