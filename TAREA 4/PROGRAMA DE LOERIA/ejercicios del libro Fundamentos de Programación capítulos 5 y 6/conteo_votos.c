#include <stdio.h>

int main(void)
{
    int voto;
    int candidato1 = 0;
    int candidato2 = 0;
    int candidato3 = 0;
    int candidato4 = 0;
    int candidato5 = 0;
    int votos_invalidos = 0;

    printf("Ingrese los votos de los candidatos (1 a 5).\n");
    printf("Ingrese 0 para terminar:\n");

    do {
        printf("Voto: ");
        scanf("%d", &voto);

        switch (voto) {
        case 1:
            candidato1++;
            break;
        case 2:
            candidato2++;
            break;
        case 3:
            candidato3++;
            break;
        case 4:
            candidato4++;
            break;
        case 5:
            candidato5++;
            break;
        case 0:
            break;
        default:
            votos_invalidos++;
            printf("Voto invalido. Debe ser un numero entre 1 y 5.\n");
            break;
        }
    } while (voto != 0);

    printf("\nResultados de la eleccion:\n");
    printf("Candidato 1: %d votos\n", candidato1);
    printf("Candidato 2: %d votos\n", candidato2);
    printf("Candidato 3: %d votos\n", candidato3);
    printf("Candidato 4: %d votos\n", candidato4);
    printf("Candidato 5: %d votos\n", candidato5);
    printf("Votos invalidos: %d\n", votos_invalidos);

    return 0;
}
