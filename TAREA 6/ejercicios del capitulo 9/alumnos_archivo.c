#include <stdio.h>

#define MAX_ALUMNOS 35
#define NUM_CALIFICACIONES 5
#define NOMBRE_ARCHIVO "calificaciones.txt"

int main(void)
{
    FILE *archivo;
    int n, i, j;
    int matricula;
    float calificacion;

    do {
        printf("Numero de alumnos (1 a %d): ", MAX_ALUMNOS);
        if (scanf("%d", &n) != 1) {
            printf("Entrada no valida.\n");
            return 1;
        }
    } while (n < 1 || n > MAX_ALUMNOS);

    archivo = fopen(NOMBRE_ARCHIVO, "w");
    if (archivo == NULL) {
        printf("No se pudo crear el archivo %s.\n", NOMBRE_ARCHIVO);
        return 1;
    }

    /* Se almacena primero el numero de alumnos. */
    fprintf(archivo, "%d\n", n);

    for (i = 0; i < n; i++) {
        printf("\nAlumno %d\n", i + 1);
        printf("Matricula: ");
        scanf("%d", &matricula);

        /* Matricula seguida de sus cinco calificaciones. */
        fprintf(archivo, "%d", matricula);

        for (j = 0; j < NUM_CALIFICACIONES; j++) {
            printf("Calificacion %d: ", j + 1);
            scanf("%f", &calificacion);
            fprintf(archivo, " %.2f", calificacion);
        }
        fprintf(archivo, "\n");
    }
    fclose(archivo);

    /* Se abre de nuevo para demostrar la lectura con fscanf. */
    archivo = fopen(NOMBRE_ARCHIVO, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo %s.\n", NOMBRE_ARCHIVO);
        return 1;
    }

    fscanf(archivo, "%d", &n);
    printf("\nDatos guardados en %s:\n", NOMBRE_ARCHIVO);

    for (i = 0; i < n; i++) {
        fscanf(archivo, "%d", &matricula);
        printf("Matricula: %d | Calificaciones:", matricula);

        for (j = 0; j < NUM_CALIFICACIONES; j++) {
            fscanf(archivo, "%f", &calificacion);
            printf(" %.2f", calificacion);
        }
        printf("\n");
    }

    fclose(archivo);
    return 0;
}
