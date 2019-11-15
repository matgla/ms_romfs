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
    Reader(uint8_t const* address)
        : address_(address)
    {
    }

    std::string_view read_string(const std::size_t size)
    {
        std::string_view str(reinterpret_cast<const char*>(address_), size);
        address_ += size;
        return str;
    }

    std::string_view read_string_with_padding(const std::size_t padding)
    {
        std::string_view str(reinterpret_cast<const char*>(address_));
        address_ += align(str.size(), padding);
        return str;
    }

    template <typename T>
    T read()
    {
        T data;
        uint8_t* ptr = reinterpret_cast<uint8_t*>(&data);
        for (int i = 0; i < sizeof(T); ++i)
        {
            ptr[sizeof(T) - i - 1] = address_[i];
        }
        address_ += sizeof(T);
        return data;
    }

    void skip(uint32_t bytes)
    {
        address_ += bytes;
    }

    template <typename T>
    void skip()
    {
        address_ += sizeof(T);
    }

    uint8_t const* address() const
    {
        return address_;
    }

private:

    uint8_t const* address_;
};
