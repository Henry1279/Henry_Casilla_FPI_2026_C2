#include <stdio.h>

#define TAM 100

int main(void)
{
    int arre[TAM];
    int num;
    int contador = 0;
    int i;

    printf("Ingrese los %d elementos del arreglo:\n", TAM);
    for (i = 0; i < TAM; i++) {
        printf("ARRE[%d]: ", i);
        scanf("%d", &arre[i]);
    }

    printf("\nIngrese el numero que desea buscar: ");
    scanf("%d", &num);

    for (i = 0; i < TAM; i++) {
        if (arre[i] == num) {
            contador++;
        }
    }

    printf("\nEl numero %d se encuentra %d veces en el arreglo.\n", num, contador);

    return 0;
}
