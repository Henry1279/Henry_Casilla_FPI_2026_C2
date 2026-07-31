#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINEA 200
#define MAX_DIMENSION 10
#define MIN_NUMERO 0
#define MAX_NUMERO 100
#define CANTIDAD_NUMEROS 101
#define MAX_POSICIONES 1000

void limpiar_salto(char texto[]) {
    texto[strcspn(texto, "\n")] = '\0';
}

int pedir_entero(const char mensaje[], int minimo, int maximo) {
    char linea[MAX_LINEA];
    char extra;
    int numero;

    while (1) {
        printf("%s", mensaje);

        if (fgets(linea, sizeof(linea), stdin) == NULL) {
            printf("Entrada invalida.\n");
            continue;
        }

        limpiar_salto(linea);

        if (sscanf(linea, " %d %c", &numero, &extra) != 1) {
            printf("Entrada invalida. Debe ingresar solo numeros.\n");
            continue;
        }

        if (numero < minimo || numero > maximo) {
            printf("Entrada invalida. El numero debe estar entre %d y %d.\n", minimo, maximo);
            continue;
        }

        return numero;
    }
}

void pedir_matriz(int matriz[MAX_DIMENSION][MAX_DIMENSION], int filas, int columnas, const char nombre[]) {
    int fila;
    int columna;
    char mensaje[MAX_LINEA];

    printf("\nIngrese los datos de la matriz %s\n", nombre);

    for (fila = 0; fila < filas; fila++) {
        for (columna = 0; columna < columnas; columna++) {
            sprintf(mensaje, "%s[%d][%d]: ", nombre, fila + 1, columna + 1);
            matriz[fila][columna] = pedir_entero(mensaje, -100000, 100000);
        }
    }
}

void mostrar_matriz(int matriz[MAX_DIMENSION][MAX_DIMENSION], int filas, int columnas) {
    int fila;
    int columna;

    for (fila = 0; fila < filas; fila++) {
        for (columna = 0; columna < columnas; columna++) {
            printf("%8d", matriz[fila][columna]);
        }
        printf("\n");
    }
}

void multiplicar_matrices() {
    int matriz_a[MAX_DIMENSION][MAX_DIMENSION];
    int matriz_b[MAX_DIMENSION][MAX_DIMENSION];
    int resultado[MAX_DIMENSION][MAX_DIMENSION];
    int filas_a;
    int columnas_a;
    int filas_b;
    int columnas_b;
    int fila;
    int columna;
    int k;

    printf("\nMultiplicacion de matrices\n");
    filas_a = pedir_entero("Filas de la matriz A: ", 1, MAX_DIMENSION);
    columnas_a = pedir_entero("Columnas de la matriz A: ", 1, MAX_DIMENSION);
    filas_b = pedir_entero("Filas de la matriz B: ", 1, MAX_DIMENSION);
    columnas_b = pedir_entero("Columnas de la matriz B: ", 1, MAX_DIMENSION);

    if (columnas_a != filas_b) {
        printf("\nNo se pueden multiplicar las matrices.\n");
        printf("Las columnas de A deben ser iguales a las filas de B.\n");
        return;
    }

    pedir_matriz(matriz_a, filas_a, columnas_a, "A");
    pedir_matriz(matriz_b, filas_b, columnas_b, "B");

    for (fila = 0; fila < filas_a; fila++) {
        for (columna = 0; columna < columnas_b; columna++) {
            resultado[fila][columna] = 0;

            for (k = 0; k < columnas_a; k++) {
                resultado[fila][columna] += matriz_a[fila][k] * matriz_b[k][columna];
            }
        }
    }

    printf("\nMatriz resultado\n");
    mostrar_matriz(resultado, filas_a, columnas_b);
}

int leer_ruta_archivo(char ruta[], int tamano) {
    printf("Ingrese el nombre del archivo: ");

    if (fgets(ruta, tamano, stdin) == NULL) {
        printf("Entrada invalida.\n");
        return 0;
    }

    limpiar_salto(ruta);

    if (strlen(ruta) == 0) {
        printf("Entrada invalida. Debe ingresar un nombre de archivo.\n");
        return 0;
    }

    return 1;
}

void mostrar_posiciones(int posiciones[CANTIDAD_NUMEROS][MAX_POSICIONES], int numero, int cantidad) {
    int i;

    printf("Posiciones: ");
    for (i = 0; i < cantidad; i++) {
        printf("%d", posiciones[numero][i]);

        if (i < cantidad - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

void analizar_archivo() {
    FILE *archivo;
    char ruta[MAX_LINEA];
    char palabra[MAX_LINEA];
    char extra;
    int numero;
    int posicion_actual = 0;
    int frecuencias[CANTIDAD_NUMEROS] = {0};
    int posiciones[CANTIDAD_NUMEROS][MAX_POSICIONES];
    int mostrados[CANTIDAD_NUMEROS] = {0};
    int cantidad_validos = 0;
    int i;
    int vuelta;
    int mejor_numero;

    printf("\nAnalisis de archivo\n");

    if (!leer_ruta_archivo(ruta, sizeof(ruta))) {
        return;
    }

    archivo = fopen(ruta, "r");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    while (fscanf(archivo, "%199s", palabra) == 1) {
        if (sscanf(palabra, " %d %c", &numero, &extra) != 1) {
            printf("Dato invalido en el archivo: %s\n", palabra);
            fclose(archivo);
            return;
        }

        if (numero < MIN_NUMERO || numero > MAX_NUMERO) {
            printf("Dato fuera de rango en el archivo: %d\n", numero);
            fclose(archivo);
            return;
        }

        if (frecuencias[numero] >= MAX_POSICIONES) {
            printf("Hay demasiadas posiciones para el numero %d.\n", numero);
            fclose(archivo);
            return;
        }

        posicion_actual++;
        posiciones[numero][frecuencias[numero]] = posicion_actual;
        frecuencias[numero]++;
        cantidad_validos++;
    }

    fclose(archivo);

    if (cantidad_validos == 0) {
        printf("El archivo no contiene numeros validos.\n");
        return;
    }

    printf("\nTres numeros que mas se repiten\n");

    for (vuelta = 1; vuelta <= 3; vuelta++) {
        mejor_numero = -1;

        for (i = MIN_NUMERO; i <= MAX_NUMERO; i++) {
            if (!mostrados[i] && frecuencias[i] > 0) {
                if (mejor_numero == -1 || frecuencias[i] > frecuencias[mejor_numero]) {
                    mejor_numero = i;
                }
            }
        }

        if (mejor_numero == -1) {
            break;
        }

        mostrados[mejor_numero] = 1;
        printf("\nNumero: %d\n", mejor_numero);
        printf("Cantidad de repeticiones: %d\n", frecuencias[mejor_numero]);
        mostrar_posiciones(posiciones, mejor_numero, frecuencias[mejor_numero]);
    }
}

void mostrar_menu() {
    printf("\nMenu\n");
    printf("1. Multiplicar matrices\n");
    printf("2. Analizar archivo de numeros\n");
    printf("3. Salir\n");
}

int main() {
    int opcion;

    do {
        mostrar_menu();
        opcion = pedir_entero("Elija una opcion: ", 1, 3);

        switch (opcion) {
            case 1:
                multiplicar_matrices();
                break;
            case 2:
                analizar_archivo();
                break;
            case 3:
                printf("Programa finalizado.\n");
                break;
        }
    } while (opcion != 3);

    return 0;
}
