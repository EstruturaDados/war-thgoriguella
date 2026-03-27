#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STRING 100
#define MAX_TERRITORIO 5

// estrutura dos campos
typedef struct {
    char nome[MAX_STRING];
    char cor[MAX_STRING];
    int tropas;
    int ativo;
} Territorio;

// função de ataque por nome de territorio e limpeza de buffer

void atacar(Territorio* atacante, Territorio* defensor);
Territorio* buscarTerritorioPorNome(Territorio* mapa, char* nomeBusca);
int validarTexto(char* str);
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}



int main() {
    srand(time(NULL));

// alocando memoria forma dinamica nos territórios
    Territorio* cadastros = (Territorio*) calloc(MAX_TERRITORIO, sizeof(Territorio));
    int totalterritorios = 0;
    int opcao;

    do {
        printf("\n**************************************\n");
        printf("*** JOGO WAR - NIVEL AVENTUREIRO ***\n");
        printf("**************************************\n");
        printf("1 - CADASTRAR TERRITORIOS\n");
        printf("2 - LISTAR TERRITORIOS CADASTRADOS\n");
        printf("3 - REALIZAR ATAQUE\n");
        printf("4 - SAIR\n");
        printf("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("ESCOLHA UMA OPCAO: ");

        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                if (totalterritorios < MAX_TERRITORIO) {
                    char nomeTEMP[MAX_STRING];
                    char corTEMP[MAX_STRING];
                    int tropasTEMP;
                    int subOpcao;

                    //cadastro do territorio
                    printf("Digite o nome do Territorio: ");
                    fgets(nomeTEMP, MAX_STRING, stdin);
                    nomeTEMP[strcspn(nomeTEMP, "\n")] = '\0';

                    //validando o cadastro de cor
                    do {
                        subOpcao = 0;
                        printf("Digite a cor do Territorio (Apenas letras): ");
                        fgets(corTEMP, MAX_STRING, stdin);
                        corTEMP[strcspn(corTEMP, "\n")] = '\0';

                        if (!validarTexto(corTEMP)) {
                            printf("\n[ERRO] A cor deve conter APENAS letras!\n");
                            printf("1 - Tentar cadastrar novamente\n");
                            printf("2 - Voltar ao menu\n");
                            printf("Escolha: ");
                            scanf("%d", &subOpcao);
                            limparBufferEntrada();

                            if (subOpcao == 2) break; //finaliza o laço de validação da cor
                        } else {
                            subOpcao = 0; // sucesso, sai do loop
                        }
                    }while (subOpcao == 1);

                    if (subOpcao == 2) break; //volta para o menu

                    //cadastro da quantidade de tropas
                    printf("Digite a quantidade da tropas: ");
                    scanf("%d", &tropasTEMP);
                    limparBufferEntrada();

                    //chegando até aqui, salva os dados de forma oficial
                    int i = totalterritorios;
                    strcpy(cadastros[i].nome, nomeTEMP);
                    strcpy(cadastros[i].cor, corTEMP);
                    cadastros[i].tropas = tropasTEMP;
                    cadastros[i].ativo = 1;
                    totalterritorios++;
                    printf("\n Territoria %s cadastrado com Sucesso!\n", cadastros[i].nome);
                } else {
                    printf("\nLimite %d territorios atingido!\n", MAX_TERRITORIO);
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
                        printf("Quantidade: %d\n", cadastros[i].tropas);
                    }
                }
                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 3: {
                char nomeBusca[MAX_STRING];
                int qtd;

                //validando territorio de ataque
                printf("Nome do Territorio Atacante: ");
                fgets(nomeBusca, MAX_STRING, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                Territorio* pAtq = buscarTerritorioPorNome(cadastros, nomeBusca);
                if (!pAtq) {
                    printf("[ERRO] Territorio '%s' nao existe no cadastro. Favor ver lista de territorios cadastrados (Opcao 2).\n", nomeBusca);
                    printf("\nPressione Enter para continuar...");
                    getchar();
                    break;
                }

                if (pAtq->tropas < 2) {
                    printf("[AVISO] '%s' tem apenas %d tropa e precisa de ao menos 2 tropas para atacar!.\n", pAtq->nome, pAtq->tropas);
                    printf("\nPressione Enter para continuar...");
                    getchar();
                    break;
                }

                //validando territorio de defesa
                printf("Nome do Territorio Defensor: ");
                fgets(nomeBusca, MAX_STRING, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                Territorio* pDef = buscarTerritorioPorNome(cadastros, nomeBusca);
                if (!pDef) {
                    printf("[ERRO] Territorio '%s' nao existe no cadastro. Favor ver lista de territorios cadastrados (Opcao 2).\n", nomeBusca);
                    printf("\nPressione Enter para continuar...");
                    getchar();
                    break;
                }

                //validação do combate
                if (strcmp(pAtq->cor, pDef->cor) == 0) {
                    printf("[ERRO] Voce nao pode atacar sua própria cor(%s)!\n", pAtq->cor);
                    } else {
                        atacar(pAtq, pDef);
                }
                break;
            }

            case 4:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                getchar();
                break;
        }
    } while (opcao != 4);

    free(cadastros);
    return 0;
}

// logica e função de ataque x defesa
void atacar(Territorio* atacante, Territorio* defensor) {
    //sorteio dos dados (1 a 6)
    int dadoAtq = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("-*-*- BATALHA DOS DADOS -*-*-");
    printf("\n%s Atacante rolou: %d", atacante->nome, dadoAtq);
    printf("\n%s Defensor rolou: %d\n", defensor->nome, dadoDef);

    if (dadoAtq > dadoDef) {
        printf(">>> VITORIA! %s tomou %s! <<<\n", atacante->nome, defensor->nome);
        printf("\nPressione Enter para continuar...");
        getchar();

        // Em caso de vitoria,o atacante conquista o territorio e move um numero aleatorio de tropas
        int tropasVencedoras = (rand() % (atacante->tropas - 1)) +1;

        printf("%s dominou %s e moveu %d tropas!\n", atacante->nome, defensor->nome, tropasVencedoras);

        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = tropasVencedoras;
        atacante->tropas -= tropasVencedoras;
    } else {
        printf(">>> DEFESA VENCEU! O ataque falhou. <<<\n");
        printf("\nPressione Enter para continuar...");
        getchar();

        // em caso de derrota, o atacante perde quantidade de tropa de forma aleatoria
        int tropasPerdidas = (rand() % (atacante->tropas - 1)) +1;
        atacante->tropas -= tropasPerdidas;
        printf("%s Falhou no ataque e perdeu %d tropas!\n", atacante->nome, tropasPerdidas);
    }
}

// função que retorna 1 se for texto e 0 se conter numeros
int validarTexto(char* str) {
    if (strlen(str) ==0) return 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i])) { //valida se o caractere e um numero
            return 0;
        }
    }
    return 1;
}



// Função que percorre o mapa e retorna o endereço (ponteiro) do território pelo nome
Territorio* buscarTerritorioPorNome(Territorio* mapa, char* nomeBusca) {
    for (int i = 0; i < MAX_TERRITORIO; i++) {
        if (mapa[i].ativo && strcmp(mapa[i].nome, nomeBusca) == 0) return &mapa[i]; // Retorna o ponteiro para o território encontrado
        }
    return NULL;
}