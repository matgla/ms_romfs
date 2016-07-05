#include "utils.hpp"
#include <cstring>

u8 *makeAlignedPtr(u8 *fp, int alignment) {
    uintptr_t addr = (uintptr_t)fp;
    if (addr % alignment != 0)
        addr += alignment - addr % alignment;
    return (u8 *)addr;
}

u32 read32(u8 *fp) {
    return (u32)*fp++ << 24 | (u32)*fp++ << 16 | (u32)*fp++ << 8 | (u32)*fp++;
}

u32 readString(char **str, u8 *fp) {
    delete[](*str);
    u32 size = 0;
    size = strlen((char *)(fp += 4));
    *str = new char[size];

    if (size % 4) {
        size = size + 4 - (size % 4); // align to 4 bytes
    }
    size += 4;
    strcpy(*str, (char *)fp);
    return size;
}