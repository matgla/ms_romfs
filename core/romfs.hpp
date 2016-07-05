#include "utils.hpp"

class RomFsDisk {
    const u8 *fileStart;

  public:
    RomFsDisk(u8 *file) : fileStart(file){};
};
