#pragma once
#pragma warning(disable:4996)

#define path "/sys/class/gpio/"

int PinSetFullStatus(char pinNum[], char pin_direction[], char pin_active[], char pin_value[]);
void PinSetStatus(char pinNum[], char pin_value[]);
int RequestFullPinStatus();
int RequestPinStatus();
void Unexport();