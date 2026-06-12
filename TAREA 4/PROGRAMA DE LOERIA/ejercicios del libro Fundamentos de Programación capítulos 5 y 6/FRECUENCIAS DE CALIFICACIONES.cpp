#include <stdio.h>

int main() {
    int CAL[50];
    int FREC[6] = {0};
    int i;
    int mayor, calMayor;

    printf("Ingrese las 50 calificaciones, entre 0 y 5:\n");

    for (i = 0; i < 50; i++) {
        printf("Calificacion %d: ", i + 1);
        scanf("%d", &CAL[i]);

        while (CAL[i] < 0 || CAL[i] > 5) {
            printf("Calificacion invalida. Ingrese un valor entre 0 y 5: ");
            scanf("%d", &CAL[i]);
        }

        FREC[CAL[i]]++;
    }

    mayor = FREC[0];
    calMayor = 0;

    for (i = 1; i < 6; i++) {
        if (FREC[i] > mayor) {
            mayor = FREC[i];
            calMayor = i;
        }
    }

    printf("\nFrecuencia de calificaciones:\n");

    for (i = 0; i < 6; i++) {
        printf("Calificacion %d: %d veces\n", i, FREC[i]);
    }

    printf("\nLa frecuencia mas alta es %d", mayor);
    printf("\nCorresponde a la calificacion %d\n", calMayor);

    return 0;
}
