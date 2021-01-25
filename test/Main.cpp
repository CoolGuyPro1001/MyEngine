#include <stdio.h>

int main(int argc, char* argv[])
{
    FILE* file = fopen("test.txt", "w");

    fputs("test", file);
    fclose(file);
    return 0;
}