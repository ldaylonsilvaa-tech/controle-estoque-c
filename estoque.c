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
    printf("Sistema de Controle de Estoque\n");
    return 0;
}
