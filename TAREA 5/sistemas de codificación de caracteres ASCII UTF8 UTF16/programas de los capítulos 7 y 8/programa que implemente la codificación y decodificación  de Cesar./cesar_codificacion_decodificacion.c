#include <stdio.h>
#include <string.h>

#define MAX_FRASE 200

char codificar_caracter(char c, int codigo)
{
    if (c >= 'A' && c <= 'Z') {
        return (char)('A' + (c - 'A' + codigo) % 26);
    }

    if (c >= 'a' && c <= 'z') {
        return (char)('a' + (c - 'a' + codigo) % 26);
    }

    return c;
}

int main(void)
{
    char frase[MAX_FRASE];
    char codificada[MAX_FRASE];
    char decodificada[MAX_FRASE];
    int codigo;
    int i;

    printf("Ingrese la frase: ");
    fgets(frase, MAX_FRASE, stdin);
    frase[strcspn(frase, "\n")] = '\0';

    printf("Ingrese el numero de codigo: ");
    scanf("%d", &codigo);

    codigo = codigo % 26;
    if (codigo < 0) {
        codigo += 26;
    }

    for (i = 0; frase[i] != '\0'; i++) {
        codificada[i] = codificar_caracter(frase[i], codigo);
    }
    codificada[i] = '\0';

    for (i = 0; codificada[i] != '\0'; i++) {
        decodificada[i] = codificar_caracter(codificada[i], 26 - codigo);
    }
    decodificada[i] = '\0';

    printf("\nFrase original: %s\n", frase);
    printf("Frase codificada: %s\n", codificada);
    printf("Frase decodificada: %s\n", decodificada);

    return 0;
}
