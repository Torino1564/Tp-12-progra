#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BoardDriver.h"

int RequestPinStatus()
{
    char pinNum[5];
    char pin_value[5];
    char pin_direction[5] = "out";
    char pin_active[5] = "0";

    char c;
    int i;

    printf("Ingrese un numero de pin:");
    i = 0;
    while ((c = getchar()) != '\n')
    {
        pinNum[i++] = c;
    }
    pinNum[i] = 0;

    printf("Ingrese el valor del pin (1 o 0):");
    i = 0;
    while ((c = getchar()) != '\n')
    {
        pin_value[i++] = c;
    }
    pin_value[i] = 0;

    PinSetFullStatus(pinNum, pin_direction, pin_active, pin_value);

    return 0;
}

void Unexport( char pinNum[])
{
    FILE* unexport_handler;
    if ((unexport_handler = fopen(path"unexport", "w")) == NULL)
    {
        printf("No se pudo de exportar el pin %s", pinNum);
        return;
    }
    else
    {
        if (fputs(pinNum, unexport_handler) == EOF)
        {
            printf("No se pudo de exportar el pin %s", pinNum);
        }
        else
        {
#ifdef DEBUG
            printf("Se exporto el pin %s correctamente", pinNum);
#endif
        }
    }
    fclose(unexport_handler);
}

int RequestFullPinStatus()
{
    char pinNum[5];
    char pin_direction[5];
    char pin_active[5];
    char pin_value[5];

    char c;
    int i;

    printf("Ingrese un numero de pin:");
    i = 0;
    while ((c = getchar()) != '\n')
    {
        pinNum[i++] = c;
    }
    pinNum[i] = 0;

    printf("Ingrese la direccion del pin (in/out):");
    i = 0;
    while ((c = getchar()) != '\n')
    {
        pin_direction[i++] = c;
    }
    pin_direction[i] = 0;

    printf("Ingrese el estado de activacion del pin (1 active low, 0 active high):");
    i = 0;
    while ((c = getchar()) != '\n')
    {
        pin_active[i++] = c;
    }
    pin_active[i] = 0;

    printf("Ingrese el valor del pin (1 o 0):");
    i = 0;
    while ((c = getchar()) != '\n')
    {
        pin_value[i++] = c;
    }
    pin_value[i] = 0;

    PinSetFullStatus(pinNum, pin_direction, pin_active, pin_value);

    return 0;
}

int PinSetFullStatus(char pinNum[], char pin_direction[], char pin_active[], char pin_value[])
{

    char pin_path[100] = path;
    strcat(pin_path, "gpio");
    strcat(pin_path, pinNum);

    FILE* export_handler;
    FILE* direction_handler;
    FILE* active_handler;
    FILE* value_handler;

    if ((export_handler = fopen(path"export", "w")) == NULL)
    {
        printf("No se pudo abrir el archivo export correctamente\n");
        return 0;
    }
    if (export_handler != NULL)
    {
        if (fputs(pinNum, export_handler) != EOF)
        {
#ifdef DEBUG
            printf("Se exporto el pin correctamente\n");
#endif
        }
        else
        {
            printf("No se pudo exportar el pin correctamente\n");
            return 0;
        }
    }
    fclose(export_handler);


    char direction_path[100] = { 0 };
    strcpy(direction_path, pin_path);
    strcat(direction_path, "/direction"); 

    if ((direction_handler = fopen(direction_path, "w")) == NULL)
    {

        printf("No se pudo establecer la direccion del pin %s correctamente.\n", pinNum);

        return 0;
    }
    else
    {
        if (fputs(pin_direction, direction_handler) != EOF)
        {
#ifdef DEBUG
            printf("Se establecio la direccion del pin %s a %s\n", pinNum, pin_direction);
#endif
        }
        else
        {
#ifdef DEBUG
            printf("No se pudo establecer la direccion del pin %s correctamente.\n", pinNum);
#endif
        }
    }
    fclose(direction_handler);

    char active_path[100] = {0};
    strcpy(active_path, pin_path);
    strcat(active_path, "/active_low");

    if ((active_handler = fopen(active_path, "w")) == NULL)
    {
#ifdef DEBUG
        printf("No se pudo establecer el modo high/low del pin %s correctamente.\n", pin_active);
#endif
        return 0;
    }
    else
    {
        if (fputs(pin_active, active_handler) != EOF)
        {
#ifdef DEBUG
            printf("Se establecio el modo high/low del pin %s\n", pin_active);
#endif
        }
        else
        {
#ifdef DEBUG
            printf("No se pudo establecer el modo high/low del pin %s correctamente.\n", pin_active);
#endif
        }
    }
    fclose(active_handler);

    char value_path[100];
    strcpy(value_path, pin_path);
    strcat(value_path, "/value");

    if ((value_handler = fopen(value_path, "w")) == NULL)
    {
#ifdef DEBUG
        printf("No se pudo establecer el valor del pin %s correctamente.\n", pinNum);
#endif
        return 0;
    }
    else
    {
        if (fputs(pin_value, active_handler) != EOF)
        {
#ifdef DEBUG
            printf("Se establecio el valor del pin %s a %s\n", pinNum, pin_value);
#endif
        }
        else
        {
#ifdef DEBUG
            printf("No se pudo establecer el valor del pin %s correctamente.\n", pinNum);
#endif
        }
    }
    fclose(value_handler);

    return 1;
}

void PinSetStatus(char pinNum[], char pin_value[])
{
    PinSetFullStatus(pinNum, "out", "0", pin_value);
}