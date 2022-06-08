#include "hardware.h"
#include <stdio.h>
#include <string.h>

#define ISASCIINUM(x) ( ((x) >= '0' && (x) <= '9' ) ? 1 : 0)
#define ISCOMMAND(x) ( (x) == 't' || (x) == 'q' || (x) == 's' || (x) == 'c') 

void Polling(void);

int main()
{
	printf("Bienvenido al Simulador de puerto de 8 bits. Las instrucciones de uso son las siguientes:\nLa tecla 's' enciende todos los bits del puerto\nLa tecla 'c' apaga todos los leds.\nLa tecla 't' realiza un toggle de todos los leds.\nLa tecla 'q' termina el programa\n\n" );
    Syncronize();
    Polling();
	Shutdown();
    return 0;
}

void Polling(void)
{
	
	while (1)
	{
		char input[20] = { 0 };
		scanf("%19s", input);

		if (StringToInt(input) >= 8 && !ISCOMMAND(input[0]))
		{
			printf("No es un input valido\n");
		}
		else
		{

			if (!strcmp(input, "q"))
			{
				printf("Terminando el programa...\n");
				TURNOFF;
				break;
			}
			else if (!strcmp(input, "t"))
			{
				printf("Realizando un Toggle a todos los bits\n");
				TOGGLEALL;
			}
			else if (!strcmp(input, "s"))
			{
				printf("Encendiendo todos los bits\n");
				TURNON;
			}
			else if (!strcmp(input, "c"))
			{
				printf("Apagando todos los leds\n");
				TURNOFF;
			}
			else if (ISASCIINUM(input[0]))
			{
				printf("Realizando un Toggle al bit ingresado\n");
				BitToggle(input[0] - '0');
			}
			else
			{
				printf(" \"%s\" no es un input valido\n", input);
			}
			PrintPort();
		}
	}
}
