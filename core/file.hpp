#pragma once

#include "utils.hpp"

class File final {
  public:
    bool isOpen();

  private:
    bool open;
};