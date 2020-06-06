#include <stdio.h>
#include <stdlib.h>

short kierunek;

void IntToBinary(unsigned char input)
{
    short i = 7;
    while(i>=0)
    {
        printf("%d",(input >> i) & 1);
        i--;
    }
    printf("   ");
}

void Opoznienie()
{
    int c,d = 0;
    for (c = 1; c <= 327; c++) // 32767
            for (d = 1; d <= 8192; d++)
            {}
}

unsigned char NastWezyk(unsigned char input)
{
    unsigned char result = input;

    if(result == 7)
        kierunek = 0;
    else if(result == 224)
        kierunek = 1;

    if(kierunek == 0)
        result <<= 1;
    else
        result >>= 1;

    return result;
}

int main(void)
{
   unsigned char display = 0;
   unsigned char wezyk = 7;
   kierunek = 0;
   //przyjmując
   // 0 - w lewo
   // 1 - w prawo

   while (1)
   {
       display = wezyk;
       wezyk = NastWezyk(wezyk);
       printf("\r");
       IntToBinary(display);

       Opoznienie();
   }
}