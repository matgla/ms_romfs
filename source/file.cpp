#include "romfs/file.hpp"

#include "romfs/utils.hpp"

namespace romfs
{

File::File(const FileHeader& file_header)
    : file_header_(file_header)
{
}

const uint8_t* File::data() const
{
    return file_header_.data();
}

const uint32_t File::size() const
{
    return file_header_.get_size();
}

} // namespace romfs
