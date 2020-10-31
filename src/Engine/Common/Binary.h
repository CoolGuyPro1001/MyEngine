#ifndef BINARY_H
#define BINARY_H

#include <string>
#include <math.h>
#include "Hex.h"


namespace Numbers
{
    class Hex;
    struct Binary
    {
        std::string val;
        Binary(std::string val);
        Binary();

        size_t Size();
        size_t ToDecimal();
        Hex ToHex();
    };
}
#endif