#include <stdio.h>
#include <string.h>

#define TAM_NOME 50
#define ARQUIVO "estoque.dat"
#define LIMITE_ESTOQUE 5

typedef struct {
    int codigo;
    char nome[TAM_NOME];
    float preco;
    int quantidade;
} Produto;

void cadastrarProduto() {
    Produto p;
    FILE *arquivo;

    printf("\n--- Cadastro de Produto ---\n");

    printf("Codigo: ");
    scanf("%d", &p.codigo);

    printf("Nome: ");
    scanf(" %[^\n]", p.nome);

    printf("Preco: ");
    scanf("%f", &p.preco);

    printf("Quantidade: ");
    scanf("%d", &p.quantidade);

    arquivo = fopen(ARQUIVO, "ab");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    fwrite(&p, sizeof(Produto), 1, arquivo);

    fclose(arquivo);

    printf("\nProduto salvo com sucesso!\n");
}

void listarProdutos() {
    Produto p;
    FILE *arquivo;

    arquivo = fopen(ARQUIVO, "rb");

    if (arquivo == NULL) {
        printf("\nNenhum produto cadastrado ainda.\n");
        return;
    }

    printf("\n--- Lista de Produtos ---\n");

    while (fread(&p, sizeof(Produto), 1, arquivo) == 1) {
        printf("Codigo: %d | Nome: %s | Preco: %.2f | Quantidade: %d\n",
               p.codigo, p.nome, p.preco, p.quantidade);
    }

    fclose(arquivo);
}

void buscarProduto() {
    Produto p;
    FILE *arquivo;
    int codigoBusca;
    int encontrado = 0;

    printf("\nDigite o codigo do produto que deseja buscar: ");
    scanf("%d", &codigoBusca);

    arquivo = fopen(ARQUIVO, "rb");

    if (arquivo == NULL) {
        printf("\nNenhum produto cadastrado ainda.\n");
        return;
    }

    while (fread(&p, sizeof(Produto), 1, arquivo) == 1) {
        if (p.codigo == codigoBusca) {
            printf("\n--- Produto encontrado ---\n");
            printf("Codigo: %d | Nome: %s | Preco: %.2f | Quantidade: %d\n",
                   p.codigo, p.nome, p.preco, p.quantidade);
            encontrado = 1;
            break;
        }
    }

    if (encontrado == 0) {
        printf("\nProduto com codigo %d nao encontrado.\n", codigoBusca);
    }

    fclose(arquivo);
}

void removerProduto() {
    Produto p;
    FILE *arquivo, *temp;
    int codigoRemover;
    int encontrado = 0;

    printf("\nDigite o codigo do produto que deseja remover: ");
    scanf("%d", &codigoRemover);

    arquivo = fopen(ARQUIVO, "rb");
    if (arquivo == NULL) {
        printf("\nNenhum produto cadastrado ainda.\n");
        return;
    }

    temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporario!\n");
        fclose(arquivo);
        return;
    }

    while (fread(&p, sizeof(Produto), 1, arquivo) == 1) {
        if (p.codigo == codigoRemover) {
            encontrado = 1;
        } else {
            fwrite(&p, sizeof(Produto), 1, temp);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove(ARQUIVO);
    rename("temp.dat", ARQUIVO);

    if (encontrado == 1) {
        printf("\nProduto removido com sucesso!\n");
    } else {
        printf("\nProduto com codigo %d nao encontrado.\n", codigoRemover);
    }
}

void alertaEstoqueBaixo() {
    Produto p;
    FILE *arquivo;
    int algumAlerta = 0;

    arquivo = fopen(ARQUIVO, "rb");

    if (arquivo == NULL) {
        printf("\nNenhum produto cadastrado ainda.\n");
        return;
    }

    printf("\n--- Produtos com Estoque Baixo (menor que %d) ---\n", LIMITE_ESTOQUE);

    while (fread(&p, sizeof(Produto), 1, arquivo) == 1) {
        if (p.quantidade < LIMITE_ESTOQUE) {
            printf("Codigo: %d | Nome: %s | Quantidade: %d\n",
                   p.codigo, p.nome, p.quantidade);
            algumAlerta = 1;
        }
    }

    if (algumAlerta == 0) {
        printf("Nenhum produto com estoque baixo no momento.\n");
    }

    fclose(arquivo);
}

void editarProduto() {
    Produto p;
    FILE *arquivo, *temp;
    int codigoEditar;
    int encontrado = 0;

    printf("\nDigite o codigo do produto que deseja editar: ");
    scanf("%d", &codigoEditar);

    arquivo = fopen(ARQUIVO, "rb");
    if (arquivo == NULL) {
        printf("\nNenhum produto cadastrado ainda.\n");
        return;
    }

    temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporario!\n");
        fclose(arquivo);
        return;
    }

    while (fread(&p, sizeof(Produto), 1, arquivo) == 1) {
        if (p.codigo == codigoEditar) {
            encontrado = 1;

            printf("\nProduto encontrado. Digite os novos dados:\n");

            printf("Nome: ");
            scanf(" %[^\n]", p.nome);

            printf("Preco: ");
            scanf("%f", &p.preco);

            printf("Quantidade: ");
            scanf("%d", &p.quantidade);
        }

        fwrite(&p, sizeof(Produto), 1, temp);
    }

    fclose(arquivo);
    fclose(temp);

    remove(ARQUIVO);
    rename("temp.dat", ARQUIVO);

    if (encontrado == 1) {
        printf("\nProduto atualizado com sucesso!\n");
    } else {
        printf("\nProduto com codigo %d nao encontrado.\n", codigoEditar);
    }
}

int main() {
    int opcao;

    do {
        printf("\n===== SISTEMA DE CONTROLE DE ESTOQUE =====\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Buscar produto\n");
        printf("4 - Remover produto\n");
        printf("5 - Alerta de estoque baixo\n");
        printf("6 - Editar produto\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            cadastrarProduto();
        } else if (opcao == 2) {
            listarProdutos();
        } else if (opcao == 3) {
            buscarProduto();
        } else if (opcao == 4) {
            removerProduto();
        } else if (opcao == 5) {
            alertaEstoqueBaixo();
        } else if (opcao == 6) {
            editarProduto();
        } else if (opcao == 0) {
            printf("Encerrando o sistema...\n");
        } else {
            printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}