#include "Binary.h"
#include "Hex.h"

namespace Numbers
{
    Binary::Binary(std::string val) : val(val)
    {
        val += "0b";
    }

    Binary::Binary()
    {
        val += "0b";
    }
    
    size_t Binary::Size()
    {
        return val.size();
    }

    Hex Binary::ToHex()
    {
        Hex hex_val;
        //Start at 2 because 0b
        for(int i = 2; i < Size(); i += 4)
        {
            if(val.substr(i, i + 3) == "0000")
                hex_val.val += '0';
            else if(val.substr(i, i + 3) == "0001")
                hex_val.val += '1';
            else if(val.substr(i, i + 3) == "0010")
                hex_val.val += '2';
            else if(val.substr(i, i + 3) == "0011")
                hex_val.val += '3';
            else if(val.substr(i, i + 3) == "0100")
                hex_val.val += '4';
            else if(val.substr(i, i + 3) == "0101")
                hex_val.val += '5';
            else if(val.substr(i, i + 3) == "0110")
                hex_val.val += '6';
            else if(val.substr(i, i + 3) == "0111")
                hex_val.val += '7';
            else if(val.substr(i, i + 3) == "1000")
                hex_val.val += '8';
            else if(val.substr(i, i + 3) == "1001")
                hex_val.val += '9';
            else if(val.substr(i, i + 3) == "1010")
                hex_val.val += 'a';
            else if(val.substr(i, i + 3) == "1011")
                hex_val.val += 'b';
            else if(val.substr(i, i + 3) == "1100")
                hex_val.val += 'c';
            else if(val.substr(i, i + 3) == "1101")
                hex_val.val += 'd';
            else if(val.substr(i, i + 3) == "1110")
                hex_val.val += 'e';
            else if(val.substr(i, i + 3) == "1111")
                hex_val.val += 'f';
        }

        return hex_val;
    }

    size_t Binary::ToDecimal()
    {
        size_t num = 0;
        size_t power_of = 0;
        for(int i = Size() - 1; i > 1; i--)
        {
            int digit = val[i] ^ 0x30;

            digit *= std::pow(2, power_of);
            power_of++;
            num += digit;
        }

        return num;
    }
}