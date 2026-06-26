#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAD 10
#define MAX_N 100

int main(void)
{
    char cad[MAX_N][MAX_CAD + 1];
    int n;
    int i;
    double suma = 0.0;
    double promedio;

    printf("Ingrese el numero de cadenas: ");
    scanf("%d", &n);

    getchar();

    if (n < 1 || n > MAX_N) {
        printf("El numero de cadenas debe estar entre 1 y %d.\n", MAX_N);
        return 1;
    }

    printf("\nIngrese cadenas con numeros reales:\n");
    for (i = 0; i < n; i++) {
        printf("cad%d: ", i + 1);
        fgets(cad[i], MAX_CAD + 1, stdin);
        cad[i][strcspn(cad[i], "\n")] = '\0';

        if (strlen(cad[i]) == MAX_CAD) {
            int c;

            while ((c = getchar()) != '\n' && c != EOF) {
            }
        }

        suma += atof(cad[i]);
    }

    promedio = suma / n;

    printf("\nSuma: %.2lf\n", suma);
    printf("Promedio: %.2lf\n", promedio);

    return 0;
}
