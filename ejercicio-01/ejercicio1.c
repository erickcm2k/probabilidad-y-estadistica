// Maestro: Ceballos Sebastián Ricardo
// Castañeda Martínez Erick - 2CM14
// Probabilidad y estadística


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Determinar que sistema operativo usa quien compile la aplicación.
#ifdef _WIN32
#define SO "windows" // Windows
#else 
#define SO "unix" // Sistemas basados en UNIX como Linux o MacOS
#endif

void esperar()
{
    if (strcmp(SO, "windows") == 0)
    {
        system("pause");
    }
    else
    {
        system("read -n 1 -s -p \"Presione cualquier tecla para salir...\"");
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
*
* Función principal.
*
*/
void imprimirTabla(int numLanzamientos)
{
    int frecuencia[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //2,3,4,5,6,7,8,9,10,11,12
    // Construimos un arreglo con los valores de cada uno de los lanzamientos.
    // Se genera la tabla.
    for (int i = 0; i < numLanzamientos; i++)
    {
        int dado1 = lanzarDado();
        int dado2 = lanzarDado();
        int sumaDados = dado1 + dado2;
        frecuencia[sumaDados - 2]++;
    }

    // Imprimimos la tabla
    printf("Valor    Frecuencia   Frecuencia relativa\n");
    printf("-----------------------------------------\n");
    float sumaFrecuenciasRelativas = 0;
    for (int i = 0; i < 11; i++)
    {
        int numeroDelDado = i + 2;
        int frec = frecuencia[i];
        float frecRelativa = (float)frecuencia[i] / (float)numLanzamientos;
        sumaFrecuenciasRelativas += frecRelativa;
        printf("%2d %7d %18.5f\n", numeroDelDado, frec, frecRelativa);
    }
    printf("-----------------------------------------\n");
    printf("Total: %11d %7.2f\n\n", numLanzamientos, sumaFrecuenciasRelativas);
}

int main()
{
    srand(time(NULL)); // Semilla generadora.

    int numLanzamientos;
    printf("Ingrese la cantidad de lanzamientos: ");
    scanf("%d", &numLanzamientos);
    printf("Calculando para %d lanzamientos...\n\n", numLanzamientos);
    if (numLanzamientos <= 0)
    {
        printf("Digite un numero mayor a cero.\n");
    }
    else
    {

        imprimirTabla(numLanzamientos);
    }
    esperar();
    limpiarPantalla();

    return 0;
}
