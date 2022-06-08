#include "hardware.h"
#include "BoardDriver.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

static port_t puertoA = {0};

static const char* GPIONum[8] = {
    "17","4","18", "23","24","25","22","27"
};

void BitSet( int bitNum )
{
    char stringBitNum[3] = {0};
    strcpy(stringBitNum, GPIONum[bitNum]);
    PinSetStatus( stringBitNum, "1");
    puertoA.bits |= Create8bitMask(bitNum);
}

void BitClr( int bitNum)
{
    char stringBitNum[3] = { 0 };
    strcpy(stringBitNum, GPIONum[bitNum]);
    PinSetStatus(stringBitNum, "0");
    puertoA.bits &= ~Create8bitMask(bitNum);
}

int BitGet(const int bitNum)
{
    int result = 1;
    if (!(puertoA.bits & Create8bitMask(bitNum)))
    {
        result = 0;
    }

    return result;

}

void BitToggle(const int bitNum)
{
    if (BitGet(bitNum))
    {
        BitClr(bitNum);
    }
    else
    {
        BitSet(bitNum);
    }
}

void MaskOn( const uint8_t mask)
{
    puertoA.bits |= mask;
    Syncronize();
}

void MaskOff(const uint8_t mask)
{
    puertoA.bits ^= mask & puertoA.bits;
    Syncronize();
  
}

void MaskToggle( const uint16_t mask)
{
    puertoA.bits ^= mask;
    Syncronize();
}

uint8_t Create8bitMask(const int bitNum)
{
    uint8_t mask = 0b00000001;
    
    mask = mask << bitNum;
    
    return mask;
}

char * IntToString(const int num, char * string)
{
    int temp = num;
    temp /= 10;
    if (temp != 0)
    {
        string[0] = temp + '0';
        temp = num - temp;
        string[1] = temp + '0';
    }
    else
    {
        string[0] = (num - temp + '0');
    }

    return string;
}

int StringToInt(char* string)
{
    int i;
    int result = 0;
    for( i=0 ; string[i] != 0 ; i++)
    {
        result *= 10;
        result += (string[i] - '0');
    }

    return result;
}

void Syncronize( void )
{
    unsigned int mascaraMascara = 0b00000001;
    for (int i = 0; i < 8; i++)
    {
        if (puertoA.bits & mascaraMascara)
        {
            BitSet(i);
        }
        else
        {
            BitClr(i);
        }
        mascaraMascara <<= 1;
    }
}

void PrintPort( void )
{
    printf("LED 0: %d\t", BitGet( 0));
    printf("LED 1: %d\t", BitGet( 1));
    printf("LED 2: %d\t", BitGet( 2));
    printf("LED 3: %d\t", BitGet( 3));
    printf("LED 4: %d\t", BitGet( 4));
    printf("LED 5: %d\t", BitGet( 5));
    printf("LED 6: %d\t", BitGet( 6));
    printf("LED 7: %d\t\n", BitGet( 7));
}

void Shutdown()
{
    int i = 0;
    for (i = 0; i <= 7; i++)
    {
        Unexport( GPIONum[i]);
    }
}