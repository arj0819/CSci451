#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned char CLAMP(int input)
{
    if(input < 0) return 0;
    if(input > 255) return 255;
}

int ROUND(float input)
{
    return (int)floor(input + .5);
}

int main(void)
{
    int temp;
    float i = 3.14159;
    temp = ROUND(i);
    printf("%d\n", CLAMP(temp));
    printf("%d\n", CLAMP(ROUND(i)));
    return 0;
}
