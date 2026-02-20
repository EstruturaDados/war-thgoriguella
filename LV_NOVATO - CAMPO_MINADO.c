#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TERRITORIO 5
#define MAX_STRING 100

struct territorio {
    char nome[MAX_STRING];
    char cor[MAX_STRING];
    int tropa;
};

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    struct territorio cadastros[MAX_TERRITORIO];
    int totalterritorios = 0;
    int opcao;

    do {
        printf("\n**************************************\n");
        printf("*** TERRITORIOS - NIVEL NOVATO ***\n");
        printf("**************************************\n");
        printf("1 - CADASTRAR NOVOS TERRITORIOS\n");
        printf("2 - LISTAR TERRITORIOS CADASTRADOS\n");
        printf("3 - SAIR\n");
        printf("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n\n");
        printf("ESCOLHA UMA OPCAO: ");

        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                if (totalterritorios < MAX_TERRITORIO) {
                    printf("Digite o nome do Territorio: ");
                    fgets(cadastros[totalterritorios].nome, MAX_STRING, stdin);
                    
                    cadastros[totalterritorios].nome[strcspn(cadastros[totalterritorios].nome, "\n")] = '\0';

                    printf("Digite a cor do Territorio: ");
                    fgets(cadastros[totalterritorios].cor, MAX_STRING, stdin);
                   
                    cadastros[totalterritorios].cor[strcspn(cadastros[totalterritorios].cor, "\n")] = '\0';

                    printf("Digite a quantidade da tropa: ");
                    scanf("%d", &cadastros[totalterritorios].tropa);
                    limparBufferEntrada();

                    totalterritorios++;
                    printf("\nTerritorio cadastrado com Sucesso!\n");
                } else {
                    printf("Limite atingido!\n");
                }
                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 2:
                printf("### LISTA DE TERRITORIOS CADASTRADOS ###\n\n");
                if (totalterritorios == 0) {
                    printf("Nenhum territorio foi cadastrado.\n");
                } else {
                    for (int i = 0; i < totalterritorios; i++) {
                        printf("**************************************\n");
                        printf("ID: %d\n", i + 1);
                        printf("Nome: %s\n", cadastros[i].nome);
                        printf("Cor: %s\n", cadastros[i].cor);
                        printf("Quantidade: %d\n", cadastros[i].tropa);
                    }
                }
                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 3:
                printf("Saindo...\n\n");
                break;

            default:
                printf("Opcao invalida!\n");
                getchar();
                break;
        }
    } while (opcao != 3);

    return 0;
}
