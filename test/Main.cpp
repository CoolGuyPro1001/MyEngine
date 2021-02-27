#include <stdio.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
    unsigned short num = 0xABCD;
    unsigned short* ptr = &num;
    printf("%d", *ptr);

    return 0;
}