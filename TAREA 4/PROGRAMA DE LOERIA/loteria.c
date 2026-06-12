#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MIN_NUMERO 1
#define MAX_NUMERO 40
#define MAX_JUGADAS 1000
#define MAX_LINEA 100

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

float pedir_dinero(const char mensaje[]) {
    char linea[MAX_LINEA];
    char extra;
    float dinero;

    while (1) {
        printf("%s", mensaje);

        if (fgets(linea, sizeof(linea), stdin) == NULL) {
            printf("Entrada invalida.\n");
            continue;
        }

        limpiar_salto(linea);

        if (sscanf(linea, " %f %c", &dinero, &extra) != 1) {
            printf("Entrada invalida. Debe ingresar una cantidad numerica.\n");
            continue;
        }

        if (dinero <= 0) {
            printf("Entrada invalida. La cantidad apostada debe ser mayor que cero.\n");
            continue;
        }

        return dinero;
    }
}

void mostrar_menu() {
    printf("\nMenu\n");
    printf("1. Jugar\n");
    printf("2. Elegir cantidad de jugadas\n");
    printf("3. Salir\n");
}

int elegir_cantidad_jugadas() {
    return pedir_entero("Ingrese la cantidad de jugadas: ", 1, MAX_JUGADAS);
}

void jugar(int cantidad_jugadas) {
    int numero_jugada;
    int numeros_apostados[MAX_JUGADAS];
    int numero_sorteado;
    float cantidades_apostadas[MAX_JUGADAS];
    float cantidades_ganadas[MAX_JUGADAS];

    for (numero_jugada = 1; numero_jugada <= cantidad_jugadas; numero_jugada++) {
        printf("\nJugada %d\n", numero_jugada);

        numeros_apostados[numero_jugada - 1] = pedir_entero("Ingrese un numero del 1 al 40: ", MIN_NUMERO, MAX_NUMERO);
        cantidades_apostadas[numero_jugada - 1] = pedir_dinero("Ingrese la cantidad de dinero apostada: ");

        numero_sorteado = (rand() % MAX_NUMERO) + MIN_NUMERO;

        if (numeros_apostados[numero_jugada - 1] == numero_sorteado) {
            cantidades_ganadas[numero_jugada - 1] = cantidades_apostadas[numero_jugada - 1] * 1000;
        } else {
            cantidades_ganadas[numero_jugada - 1] = 0;
        }
    }

    printf("\nResultados\n");
    printf("-----------------------------------------------------------------\n");
    printf("%-15s%-18s%-18s%-18s\n", "Nro. jugada", "Nro. apostado", "Apostado", "Ganado");
    printf("-----------------------------------------------------------------\n");

    for (numero_jugada = 1; numero_jugada <= cantidad_jugadas; numero_jugada++) {
        printf("%-15d%-18d$%-17.2f$%-17.2f\n",
               numero_jugada,
               numeros_apostados[numero_jugada - 1],
               cantidades_apostadas[numero_jugada - 1],
               cantidades_ganadas[numero_jugada - 1]);
    }
}

int main() {
    int opcion;
    int cantidad_jugadas = 1;

    srand((unsigned int) time(NULL));

    do {
        mostrar_menu();
        opcion = pedir_entero("Elija una opcion: ", 1, 3);

        switch (opcion) {
            case 1:
                jugar(cantidad_jugadas);
                break;
            case 2:
                cantidad_jugadas = elegir_cantidad_jugadas();
                printf("Cantidad de jugadas seleccionada: %d\n", cantidad_jugadas);
                break;
            case 3:
                printf("Programa finalizado.\n");
                break;
        }
    } while (opcion != 3);

    return 0;
}
