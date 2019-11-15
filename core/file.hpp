#pragma once

#include "fileHeader.hpp"
#include "utils.hpp"
#include <istream>
#include <streambuf>

class File final
{
public:
    File() : fileHdr(nullptr), open(false) {
    }
    bool isOpen();
    FileHeader fileHdr;
    bool open;

private:
};

class FileBuf final : public std::streambuf {
  protected:
    /* central output function
     * - print characters in uppercase mode
     */
    virtual int_type overflow(int_type c) {
        if (c != EOF) {
            // convert lowercase to uppercase
            c = std::toupper(static_cast<char>(c), getloc());

            // and write the character to the standard output
            if (putchar(c) == EOF) {
                return EOF;
            }
        }
        return c;
    }

    virtual int_type underflow() {
        return 10;
    }

  public:
    std::istream &operator>>(int &val) {
        val = 10;
    }
};