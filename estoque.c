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

void cadastrarProduto() {
    Produto p;

    printf("\n--- Cadastro de Produto ---\n");
    printf("Codigo: ");
    scanf("%d", &p.codigo);

    printf("Nome: ");
    scanf(" %[^\n]", p.nome);

    printf("Preco: ");
    scanf("%f", &p.preco);

    printf("Quantidade: ");
    scanf("%d", &p.quantidade);

    printf("\nProduto cadastrado (ainda nao salvo em arquivo):\n");
    printf("Codigo: %d | Nome: %s | Preco: %.2f | Quantidade: %d\n",
           p.codigo, p.nome, p.preco, p.quantidade);
}
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
        cadastrarProduto();
}         else if (opcao == 2) {
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