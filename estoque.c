#include <stdio.h>
#include <string.h>

#define TAM_NOME 50
#define ARQUIVO "estoque.dat"

typedef struct {
    int codigo;
    char nome[TAM_NOME];
    float preco;
    int quantidade;
} Produto;

int main() {
    int opcao;

    do {
        printf("\n===== SISTEMA DE CONTROLE DE ESTOQUE =====\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Buscar produto\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            printf("Voce escolheu Cadastrar produto.\n");
        } else if (opcao == 2) {
            printf("Voce escolheu Listar produtos.\n");
        } else if (opcao == 3) {
            printf("Voce escolheu Buscar produto.\n");
        } else if (opcao == 0) {
            printf("Encerrando o sistema...\n");
        } else {
            printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}