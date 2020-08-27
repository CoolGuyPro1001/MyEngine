#ifndef HEX_H
#define HEX_H

#include <string>
#include <math.h>
#include "Binary.h"

namespace Numbers
{
    class Binary;
    struct Hex
    {
        std::string val;
        Hex(std::string val);
        Hex();

        size_t Size();
        size_t ToDecimal();
        Binary ToBinary();
    };
}
#endif