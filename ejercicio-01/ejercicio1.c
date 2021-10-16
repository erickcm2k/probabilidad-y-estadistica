#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
*
* Función auxiliar para la función "imprimirTabla".
*
*/
int lanzamientoDato()
{
    const int limInf = 1;
    const int limSup = 6;

    int semilla = rand();
    int aleatorio = semilla % (limSup - limInf + 1) + limInf;
    return aleatorio;
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
        int dado1 = lanzamientoDato();
        int dado2 = lanzamientoDato();
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
    printf("Total: %11d %7.2f", numLanzamientos, sumaFrecuenciasRelativas);
}

int main()
{
    srand(time(NULL)); // Semilla generadora.

    int numLanzamientos;
    printf("Ingrese la cantidad de lanzamientos: ");
    scanf("%d", &numLanzamientos);
    printf("Calculando para %d lanzamientos...\n\n", numLanzamientos);

    imprimirTabla(numLanzamientos);

    return 0;
}
