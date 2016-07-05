#pragma once

#include <cstdint>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

u8 *makeAlignedPtr(u8 *fp, int alignment);
u32 read32(u8 *fp);
u32 readString(char **str, u8 *fp);

constexpr int U32_OFFSET() {
    return sizeof(u32);
}
constexpr int U16_OFFSET() {
    return sizeof(u16);
}
constexpr int U8_OFFSET() {
    return sizeof(u8);
}