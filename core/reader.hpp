#pragma once

#include <cstdint>
#include <string_view>

template <typename T>
constexpr auto align(const T value, const uint32_t alignment)
{
    return value % alignment ? value + (alignment - value % alignment) : value;
}

class Reader
{
public:
    Reader(const uint8_t* address)
        : address_(address)
        , readed_bytes_(0)
    {
    }

    std::string_view read_string(const std::size_t size)
    {
        std::string_view str(reinterpret_cast<const char*>(address_ + readed_bytes_), size);
        readed_bytes_ += size;
        return str;
    }

    std::string_view read_string_with_padding(const std::size_t padding)
    {
        std::string_view str(reinterpret_cast<const char*>(address_ + readed_bytes_));
        readed_bytes_ += align(str.size(), padding);
        return str;
    }

    template <typename T>
    T read()
    {
        T data;
        uint8_t* ptr = reinterpret_cast<uint8_t*>(&data);
        for (int i = 0; i < sizeof(T); ++i)
        {
            ptr[sizeof(T) - i - 1] = address_[readed_bytes_ + i];
        }
        readed_bytes_ += sizeof(T);
        return data;
    }

    void skip(uint32_t bytes)
    {
        readed_bytes_ += bytes;
    }

    template <typename T>
    void skip()
    {
        readed_bytes_ += sizeof(T);
    }

    const uint8_t* address() const
    {
        return address_ + readed_bytes_;
    }

    const std::size_t get_readed_bytes() const
    {
        return readed_bytes_;
    }

private:

    const uint8_t* address_;
    std::size_t readed_bytes_;
};
