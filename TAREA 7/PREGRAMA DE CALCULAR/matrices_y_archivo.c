#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
    Programa:
    1. Multiplica dos matrices.
    2. Lee un archivo JSON con resultados de loteria.

    El archivo JSON debe contener objetos con tres campos:
    Primera, Segunda y Tercera.

    Ejemplo:
    [
        {"Primera": 5, "Segunda": 8, "Tercera": 10},
        {"Primera": 5, "Segunda": 3, "Tercera": 8}
    ]

    El programa cuenta cuales son los tres numeros que mas se repiten
    entre todos los campos Primera, Segunda y Tercera, indicando tambien
    en que sorteo y posicion aparecio cada numero.
*/

#define MAX_LINEA 200
#define MAX_DIMENSION 10
#define MIN_NUMERO 0
#define MAX_NUMERO 100
#define CANTIDAD_NUMEROS 101
#define MAX_POSICIONES 1000
#define MAX_TEXTO_POSICION 50

/* Elimina el salto de linea que deja fgets al leer texto por teclado. */
void limpiar_salto(char texto[]) {
    texto[strcspn(texto, "\n")] = '\0';
}

/*
    Pide un numero entero y valida:
    - Que realmente sea un numero.
    - Que no tenga letras u otros caracteres.
    - Que este dentro del rango permitido.
*/
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

/* Solicita todos los valores de una matriz por teclado. */
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

/* Muestra una matriz en forma de tabla. */
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

/*
    Multiplica dos matrices.
    Para poder multiplicarlas, las columnas de A deben ser iguales
    a las filas de B.
*/
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

/* Lee el nombre del archivo JSON que se desea analizar. */
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

/*
    Carga todo el archivo JSON en memoria para poder buscar dentro del texto.
    Retorna NULL si el archivo no se puede abrir o leer.
*/
char *leer_archivo_completo(const char ruta[]) {
    FILE *archivo;
    long tamano;
    char *contenido;

    archivo = fopen(ruta, "rb");

    if (archivo == NULL) {
        return NULL;
    }

    fseek(archivo, 0, SEEK_END);
    tamano = ftell(archivo);
    rewind(archivo);

    contenido = (char *) malloc((tamano + 1) * sizeof(char));

    if (contenido == NULL) {
        fclose(archivo);
        return NULL;
    }

    fread(contenido, sizeof(char), tamano, archivo);
    contenido[tamano] = '\0';

    fclose(archivo);
    return contenido;
}

/*
    Extrae un numero de un objeto JSON buscando un campo especifico.
    Por ejemplo, si campo es "Primera", busca:
    "Primera": numero
*/
int extraer_numero_del_objeto(const char objeto[], const char campo[], int *numero) {
    char patron[MAX_LINEA];
    char *posicion_campo;
    char *posicion_dos_puntos;
    char *fin_numero;
    long valor;

    sprintf(patron, "\"%s\"", campo);
    posicion_campo = strstr(objeto, patron);

    if (posicion_campo == NULL) {
        return 0;
    }

    posicion_dos_puntos = strchr(posicion_campo, ':');

    if (posicion_dos_puntos == NULL) {
        return 0;
    }

    valor = strtol(posicion_dos_puntos + 1, &fin_numero, 10);

    if (posicion_dos_puntos + 1 == fin_numero) {
        return 0;
    }

    while (*fin_numero != '\0' && isspace((unsigned char) *fin_numero)) {
        fin_numero++;
    }

    if (*fin_numero != ',' && *fin_numero != '}') {
        return 0;
    }

    if (valor < MIN_NUMERO || valor > MAX_NUMERO) {
        return 0;
    }

    *numero = (int) valor;
    return 1;
}

/*
    Registra una aparicion de un numero:
    - Aumenta su frecuencia.
    - Guarda la posicion donde aparecio, por ejemplo:
      Sorteo 2 - Segunda
*/
int registrar_numero(
    int numero,
    const char nombre_posicion[],
    int numero_sorteo,
    int frecuencias[CANTIDAD_NUMEROS],
    char posiciones[CANTIDAD_NUMEROS][MAX_POSICIONES][MAX_TEXTO_POSICION]
) {
    if (frecuencias[numero] >= MAX_POSICIONES) {
        printf("Hay demasiadas posiciones para el numero %d.\n", numero);
        return 0;
    }

    sprintf(
        posiciones[numero][frecuencias[numero]],
        "Sorteo %d - %s",
        numero_sorteo,
        nombre_posicion
    );

    frecuencias[numero]++;
    return 1;
}

/* Muestra todas las posiciones donde aparecio un numero. */
void mostrar_posiciones(char posiciones[CANTIDAD_NUMEROS][MAX_POSICIONES][MAX_TEXTO_POSICION], int numero, int cantidad) {
    int i;

    printf("Posiciones: ");
    for (i = 0; i < cantidad; i++) {
        printf("%s", posiciones[numero][i]);

        if (i < cantidad - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

/*
    Analiza el archivo JSON.
    Cada objeto del JSON representa un sorteo y debe tener:
    - Primera
    - Segunda
    - Tercera

    Se cuentan todos esos numeros y se imprimen los tres que mas se repiten.
*/
void analizar_archivo() {
    char ruta[MAX_LINEA];
    char *contenido;
    char *inicio_objeto;
    char *fin_objeto;
    char objeto[MAX_LINEA * 5];
    static int frecuencias[CANTIDAD_NUMEROS];
    static char posiciones[CANTIDAD_NUMEROS][MAX_POSICIONES][MAX_TEXTO_POSICION];
    static int mostrados[CANTIDAD_NUMEROS];
    int cantidad_validos = 0;
    int numero_sorteo = 0;
    int primera;
    int segunda;
    int tercera;
    int i;
    int vuelta;
    int mejor_numero;
    int largo_objeto;

    printf("\nAnalisis de archivo JSON\n");

    /*
        Como los arreglos son static, se limpian antes de cada analisis.
        Esto permite usar la opcion varias veces sin mezclar resultados.
    */
    memset(frecuencias, 0, sizeof(frecuencias));
    memset(posiciones, 0, sizeof(posiciones));
    memset(mostrados, 0, sizeof(mostrados));

    if (!leer_ruta_archivo(ruta, sizeof(ruta))) {
        return;
    }

    contenido = leer_archivo_completo(ruta);

    if (contenido == NULL) {
        printf("No se pudo abrir o leer el archivo.\n");
        return;
    }

    inicio_objeto = strchr(contenido, '{');

    while (inicio_objeto != NULL) {
        fin_objeto = strchr(inicio_objeto, '}');

        if (fin_objeto == NULL) {
            printf("JSON invalido. Falta cerrar un objeto con }.\n");
            free(contenido);
            return;
        }

        largo_objeto = (int) (fin_objeto - inicio_objeto + 1);

        if (largo_objeto >= (int) sizeof(objeto)) {
            printf("Objeto JSON demasiado largo.\n");
            free(contenido);
            return;
        }

        strncpy(objeto, inicio_objeto, largo_objeto);
        objeto[largo_objeto] = '\0';

        if (
            !extraer_numero_del_objeto(objeto, "Primera", &primera) ||
            !extraer_numero_del_objeto(objeto, "Segunda", &segunda) ||
            !extraer_numero_del_objeto(objeto, "Tercera", &tercera)
        ) {
            printf("Objeto JSON invalido o con numeros fuera del rango 0 a 100.\n");
            printf("Objeto leido: %s\n", objeto);
            free(contenido);
            return;
        }

        numero_sorteo++;

        if (
            !registrar_numero(primera, "Primera", numero_sorteo, frecuencias, posiciones) ||
            !registrar_numero(segunda, "Segunda", numero_sorteo, frecuencias, posiciones) ||
            !registrar_numero(tercera, "Tercera", numero_sorteo, frecuencias, posiciones)
        ) {
            free(contenido);
            return;
        }

        cantidad_validos += 3;
        inicio_objeto = strchr(fin_objeto + 1, '{');
    }

    free(contenido);

    if (cantidad_validos == 0) {
        printf("El archivo no contiene objetos JSON validos.\n");
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

/* Muestra las opciones principales del programa. */
void mostrar_menu() {
    printf("\nMenu\n");
    printf("1. Multiplicar matrices\n");
    printf("2. Analizar archivo de numeros\n");
    printf("3. Salir\n");
}

/* Funcion principal: mantiene el menu activo hasta que el usuario elige salir. */
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
