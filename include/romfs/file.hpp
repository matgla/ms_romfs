#pragma once

#include "romfs/fileHeader.hpp"

namespace romfs
{

class File
{
public:
    File(const FileHeader& file_header);

    const uint8_t* data() const; // gsl_span
    uint32_t size() const;
private:
    const FileHeader file_header_;
};

} // namespace romfs

