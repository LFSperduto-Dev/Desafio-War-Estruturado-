#include <stdio.h>  // Biblioteca para entrada e saída padrão (printf, scanf)
#include <string.h> // Biblioteca para manipulação de strings (embora não seja usada diretamente aqui, incluída conforme solicitado)

// Definição da struct Territorio
// Esta struct representa um território com nome, cor do exército e quantidade de tropas.
// Campos:
// - nome: string de até 29 caracteres (mais o terminador nulo)
// - cor: string de até 9 caracteres (mais o terminador nulo)
// - tropas: inteiro representando a quantidade de tropas
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    // Declaração de um vetor de structs para armazenar 5 territórios
    // Este vetor permite armazenar múltiplas instâncias da struct Territorio
    struct Territorio territorios[5];
    
    // Laço para entrada dos dados dos 5 territórios
    // O laço percorre de 0 a 4 (índices do vetor), solicitando ao usuário os dados de cada território
    for (int i = 0; i < 5; i++) {
        printf("Cadastro do Território %d:\n", i + 1);
        
        // Entrada do nome: usa scanf para ler uma string sem espaços
        // Assume-se que o nome do território não contém espaços
        printf("Digite o nome do território: ");
        scanf("%s", territorios[i].nome);
        
        // Entrada da cor: usa scanf para ler uma string sem espaços
        // Assume-se que a cor é uma palavra simples
        printf("Digite a cor do exército: ");
        scanf("%s", territorios[i].cor);
        
        // Entrada da quantidade de tropas: usa scanf para ler um inteiro
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        
        printf("\n");  // Linha em branco para separar os cadastros
    }
    
    // Exibição dos dados após o cadastro
    // Após preencher todos os territórios, o programa exibe as informações de cada um
    // O laço percorre novamente o vetor para imprimir os dados formatados
    printf("Dados dos Territórios Cadastrados:\n\n");
    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].cor);
        printf("Quantidade de Tropas: %d\n\n", territorios[i].tropas);
    }
    
    return 0;  // Indica que o programa terminou com sucesso
}
