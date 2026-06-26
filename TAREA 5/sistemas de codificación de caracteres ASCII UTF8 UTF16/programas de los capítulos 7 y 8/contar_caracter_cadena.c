#include <stdio.h>
#include <string.h>

#define MAX_CAD 50

int main(void)
{
    char cad[MAX_CAD + 1];
    char car;
    int contador = 0;
    int i;

    printf("Ingrese la cadena: ");
    fgets(cad, MAX_CAD + 1, stdin);
    cad[strcspn(cad, "\n")] = '\0';

    printf("Ingrese el caracter a buscar: ");
    scanf("%c", &car);

    for (i = 0; cad[i] != '\0'; i++) {
        if (cad[i] == car) {
            contador++;
        }
    }

    printf("\nEl caracter '%c' aparece %d veces en la cadena.\n", car, contador);

    return 0;
}
