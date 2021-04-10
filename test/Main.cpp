#include <stdio.h>
#include <math.h>

int main()
{
    int num = 0;
    int i = 0;
    while(i < 100)
    {
        num += i;
        i++;
    }
    printf("%d", num);
    return 0;
}