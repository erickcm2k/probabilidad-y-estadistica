// Maestro: Ceballos Sebastián Ricardo
// Castañeda Martínez Erick - 2CM14
// Probabilidad y estadística

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

// Determinar que sistema operativo usa quien compile la aplicación.
#ifdef _WIN32
#define SO "windows" // Windows
#else
#define SO "unix" // Sistemas basados en UNIX como Linux o MacOS
#endif

void esperar(char *mensaje)
{
    bool hayMensaje = strlen(mensaje) != 0;

    if (strcmp(SO, "windows") == 0)
    {
        if (hayMensaje)
        {
            printf("%s\n", mensaje);
        }
        system("pause");
        printf("\n");
    }
    else
    {
        if (hayMensaje)
        {
            printf("%s\n", mensaje);
            system("read -n 1 -s -p \"\"");
            printf("\n");
        }
        else
        {
            system("read -n 1 -s -p \"Presione cualquier tecla para salir...\"");
            printf("\n");
        }
    }
}

void limpiarPantalla()
{
    if (strcmp(SO, "windows") == 0)
    {
        system("cls");
    }
    else
    {
        system("clear");
    }
}

/*
*
* Función auxiliar para la función "imprimirTabla".
*
*/
int lanzarDado()
{
    const int limInf = 1;
    const int limSup = 6;

    return rand() % (limSup - limInf + 1) + limInf;
}

/* 
*   Retorna 0 -> usuario pierde (casa gana)
*   Retorna 1 -> usuario gana
*   Retorna suma -> se retorna el punto y el juego continua
*/
int ganaPrimerLanzamiento()
{
    int dado1 = lanzarDado();
    int dado2 = lanzarDado();
    int suma = dado1 + dado2;
    printf("La suma de los dados en su primer tiro es: %d.\n", suma);
    switch (suma)
    {
    case 2:
        return 0;
        break;
    case 3:
        return 0;
        break;
    case 12:
        return 0;
        break;
    case 7:
        return 1;
        break;
    case 11:
        return 1;
        break;
    default:
        return suma;
    }
}

void juegoCraps()
{
    printf("-----------------------------------------");
    printf("\nCRAPS\n");
    printf("-----------------------------------------\n");

    esperar("Presione cualquier tecla para tirar por primera vez");

    int sumaPrimerLanzamiento = ganaPrimerLanzamiento();

    if (sumaPrimerLanzamiento == 0)
    {
        printf("La casa gana.\n\n");
    }
    else if (sumaPrimerLanzamiento == 1)
    {
        printf("¡Usted gana! ¡Felicidades!\n\n");
    }
    else
    {
        int punto = sumaPrimerLanzamiento;
        printf("El juego continua, tienes el punto %d.\n\n", punto);

        int contadorLanzamientos = 1;

        int resultado = 0;
        do
        {
            contadorLanzamientos++;
            esperar("Presione cualquier tecla para volver a tirar los dados.");
            resultado = lanzarDado() + lanzarDado();
            printf("La suma de los dados es: %d.\n", resultado);
            printf("Haz tirado %d veces.\n\n", contadorLanzamientos);
            if (resultado == punto)
            {
                printf("Su punto es %d y sus dados suman %d.\n", punto, resultado);
                printf("¡Usted gana! ¡Felicidades!\n\n");
            }
            if (resultado == 7)
            {
                printf("La casa gana.\n\n");
            }

        } while (resultado != 7 && resultado != punto);
    }
    esperar("");
    limpiarPantalla();
}

int main()
{
    srand(time(NULL)); // Semilla generadora.
    juegoCraps();
    return 0;
}
