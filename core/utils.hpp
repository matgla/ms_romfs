#pragma once

#include <cstdint>
#include <string>
#include <vector>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

u8 *makeAlignedPtr(u8 *fp, int alignment);
u32 read32(u8 **fp);
u32 readString(char **str, u8 **fp);
std::vector<std::string> getFilesArray(std::string filePath);