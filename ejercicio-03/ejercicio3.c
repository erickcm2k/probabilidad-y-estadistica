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

bool validarApuesta(saldoBanco, monto)
{
    return saldoBanco - monto >= 0 && monto > 0 ? true : false;
}

int rondaCraps(saldoBanco)
{
    int apuesta;
    bool apuestaEsValida = false;
    int nuevoSaldo = saldoBanco;
    printf("-----------------------------------------");
    printf("\nCRAPS\n");
    printf("-----------------------------------------\n");

    printf("\nDispone de $%d de saldo en el banco.\n", nuevoSaldo);
    printf("\nIngrese el monto inicial que desea apostar.\n");
    do
    {
        scanf("%d", &apuesta);
        apuestaEsValida = validarApuesta(nuevoSaldo, apuesta);
        if (apuestaEsValida)
        {
            printf("Ha decidido apostar $%d.\n\n", apuesta);
        }
        else
        {
            printf("El monto ingresado no es valido.\n");
            printf("Es necesario ingresar una cifra valida.\n");
        }
    } while (!apuestaEsValida);
    esperar("Presione cualquier tecla para tirar los dados.");

    int sumaPrimerLanzamiento = ganaPrimerLanzamiento();

    if (sumaPrimerLanzamiento == 0)
    {
        printf("La casa gana.\n\n");
        nuevoSaldo -= apuesta;
        printf("\nEl nuevo saldo del banco es $%d.\n", nuevoSaldo);
    }
    else if (sumaPrimerLanzamiento == 1)
    {
        printf("¡Usted gana! ¡Felicidades!\n\n");
        nuevoSaldo += apuesta;
        printf("\nEl nuevo saldo del banco es $%d.\n", nuevoSaldo);
    }
    else
    {
        int punto = sumaPrimerLanzamiento;
        printf("El juego continua, el valor del punto es: %d.\n", punto);
        printf("El saldo se matiene intacto.\n\n");

        int resultado = 0;
        do
        {
            esperar("Presione cualquier tecla para volver a tirar los dados.");
            resultado = lanzarDado() + lanzarDado();
            printf("La suma de los dados es: %d.\n", resultado);
            printf("Su punto es %d.\n", punto);

            if (resultado == punto)
            {

                printf("¡Usted gana! ¡Felicidades!\n\n");
                nuevoSaldo += apuesta;
                printf("\nEl nuevo saldo del banco es $%d.\n", nuevoSaldo);
            }
            else if (resultado == 7)
            {
                printf("La casa gana.\n\n");
                nuevoSaldo -= apuesta;
                printf("\nEl nuevo saldo del banco es $%d.\n", nuevoSaldo);
            }
            else
            {
                printf("No hay cambios en su saldo.\n");
            }

        } while (resultado != 7 && resultado != punto);
    }

    return nuevoSaldo;
}

int main()
{
    srand(time(NULL)); // Semilla generadora.
    int saldoBanco = 1000;
    char resp;

    do
    {
        saldoBanco = rondaCraps(saldoBanco);

        if (saldoBanco == 0)
        {
            printf("-----------------------------------------\n");
            printf("El saldo del banco se ha agotado.\n");
            printf("Gracias por jugar.\n\n");
        }
        else
        {
            printf("\nIngrese la tecla s si desea continuar jugando.\n");
            printf("Digite cualquier otra tecla para terminar el juego.\n\n");
            scanf(" %c", &resp);
        }

    } while (saldoBanco > 0 && (resp == 'S' || resp == 's'));
    esperar("");
    limpiarPantalla();

    return 0;
}
