#pragma once

#include <cstdint>

#include "romfs/fileHeader.hpp"

namespace romfs
{

class DirectoryIterator
{
public:
    DirectoryIterator(const uint8_t* address, std::size_t offset);

    const DirectoryIterator& operator++();
    bool operator!=(const DirectoryIterator& it) const;

    const FileHeader operator*() const;

private:
    const uint8_t* address_;
    std::size_t offset_;
};

} // namespace romfs
