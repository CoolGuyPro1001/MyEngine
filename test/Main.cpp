#include <stdio.h>
#include <math.h>

int main()
{
    char feels = 0b00001111;
    char mask = 0b10101010;
    printf("%x", feels & mask);

    00001111
    10101010
    00001010
    
}