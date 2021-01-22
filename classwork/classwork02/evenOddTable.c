#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;
    char *parity;
    int even;
    for (i = -10; i < 11; i++)
    {
        if (i % 2 == 0)
        {
            parity = "Even";
            even++;
        }
        else
        {
            parity = "Odd";
        }
        printf("%d \t %d \t %s\n", i, i * i, parity);
    }
}