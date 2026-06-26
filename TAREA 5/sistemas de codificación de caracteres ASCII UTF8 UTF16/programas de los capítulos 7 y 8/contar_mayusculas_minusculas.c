#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_N 20
#define MAX_M 50

int main(void)
{
    char fra[MAX_N][MAX_M];
    int n;
    int i, j;

    do {
        printf("Ingrese el numero de cadenas (1 a %d): ", MAX_N);
        scanf("%d", &n);
    } while (n < 1 || n > MAX_N);

    getchar();

    printf("\nIngrese las cadenas:\n");
    for (i = 0; i < n; i++) {
        printf("FRA[%d]: ", i);
        fgets(fra[i], MAX_M, stdin);

        fra[i][strcspn(fra[i], "\n")] = '\0';
    }

    printf("\nResultados:\n");
    for (i = 0; i < n; i++) {
        int minusculas = 0;
        int mayusculas = 0;

        for (j = 0; fra[i][j] != '\0'; j++) {
            if (islower((unsigned char)fra[i][j])) {
                minusculas++;
            } else if (isupper((unsigned char)fra[i][j])) {
                mayusculas++;
            }
        }

        printf("FRA[%d] = \"%s\"\n", i, fra[i]);
        printf("  Minusculas: %d\n", minusculas);
        printf("  Mayusculas: %d\n", mayusculas);
    }

    return 0;
}
