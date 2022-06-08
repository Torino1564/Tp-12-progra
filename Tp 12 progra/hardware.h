#pragma warning(disable:4996)
#include "Ports.h"

#define TURNOFF MaskOff(0b11111111)
#define TOGGLEALL MaskToggle(0b11111111)
#define TURNON MaskOn(0b11111111)

void BitSet(int bitNum);
void BitClr(int bitNum);
int BitGet(const int bitNum);
void BitToggle(const int bitNum);
void MaskOn(const uint8_t mask);
void MaskOff(const uint8_t mask);
void MaskToggle(const uint16_t mask);
void Syncronize( void );
void Shutdown();
void PrintPort( void );

char* IntToString(const int num, char* string);
int StringToInt(char* string);
uint8_t Create8bitMask(const int bitNum);