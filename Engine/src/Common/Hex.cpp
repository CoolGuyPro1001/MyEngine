#include "Hex.h"
#include "Binary.h"

Hex::Hex(std::string val) : val(val)
{
    val += "0x";
}

Hex::Hex()
{
    val += "0x";
}

size_t Hex::Size()
{
    return val.size();
}

Binary Hex::ToBinary()
{
    Binary bin_val;
    for(int i = 2; i < Size(); i++)
    {
        switch(val[i])
        {
            case '0':
                bin_val.val += "0000";
                break;
            case '1':
                bin_val.val += "0001";
                break;
            case '2':
                bin_val.val += "0010";
                break;
            case '3':
                bin_val.val += "0011";
                break;
            case '4':
                bin_val.val += "0100";
                break;
            case '5':
                bin_val.val += "0101";
                break;
            case '6':
                bin_val.val += "0110";
                break;
            case '7':
                bin_val.val += "0111";
                break;
            case '8':
                bin_val.val += "1000";
                break;
            case '9':
                bin_val.val += "1001";
                break;
            case 'a':
                bin_val.val += "1010";
                break;
            case 'b':
                bin_val.val += "1011";
                break;
            case 'c':
                bin_val.val += "1100";
                break;
            case 'd':
                bin_val.val += "1101";
                break;
            case 'e':
                bin_val.val += "1110";
                break;
            case 'f':
                bin_val.val += "1111";
                break;
        }
    }

    return bin_val;
}

size_t Hex::ToDecimal()
{
    size_t num = 0;
    size_t power_of = 0;
    for(int i = Size() - 1; i > 1; i--)
    {
        int digit;

        if(val[i] >= '0' && val[i] <= '9')
        {
            digit = val[i] ^ 0x30;
        }
        else
        {
            //A(65) - 64 = 1 + 9 = 10
            digit = val[i] ^ 0x60;
            digit += 9;
        }

        digit *= std::pow(16, power_of);
        power_of++;
        num += digit;
    }

    return num;
}