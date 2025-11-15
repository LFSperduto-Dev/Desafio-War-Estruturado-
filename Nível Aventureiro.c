#include <stdio.h>   // Biblioteca para entrada e saída padrão (printf, scanf)
#include <stdlib.h>  // Biblioteca para alocação dinâmica (malloc, calloc, free) e rand()
#include <string.h>  // Biblioteca para manipulação de strings (strcpy, strcmp)
#include <time.h>    // Biblioteca para srand() e time()

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

// Função para cadastrar os territórios
// Recebe um ponteiro para o vetor de territórios e o número de territórios
// Utiliza ponteiros para acessar e modificar os dados dos territórios
void cadastrarTerritorios(struct Territorio* mapa, int numTerritorios) {
    for (int i = 0; i < numTerritorios; i++) {
        printf("Cadastro do Território %d:\n", i + 1);
        
        // Entrada do nome: usa scanf para ler uma string sem espaços
        printf("Digite o nome do território: ");
        scanf("%s", mapa[i].nome);
        
        // Entrada da cor: usa scanf para ler uma string sem espaços
        printf("Digite a cor do exército: ");
        scanf("%s", mapa[i].cor);
        
        // Entrada da quantidade de tropas: usa scanf para ler um inteiro
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        
        printf("\n");  // Linha em branco para separar os cadastros
    }
}

// Função para exibir os dados dos territórios
// Recebe um ponteiro para o vetor de territórios e o número de territórios
// Utiliza ponteiros para acessar os dados dos territórios
void exibirTerritorios(struct Territorio* mapa, int numTerritorios) {
    printf("Dados dos Territórios:\n");
    for (int i = 0; i < numTerritorios; i++) {
        printf("Território %d: Nome: %s, Cor: %s, Tropas: %d\n", 
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("\n");
}

// Função para simular um ataque entre dois territórios
// Recebe ponteiros para o território atacante e defensor
// Simula rolagem de dados (1 a 6) usando rand()
// Se o dado do atacante for maior, ele vence: muda a cor do defensor e define suas tropas como metade das do atacante
// Caso contrário, o atacante perde uma tropa
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    // Rolagem de dados: números aleatórios de 1 a 6
    int dado_atacante = rand() % 6 + 1;
    int dado_defensor = rand() % 6 + 1;
    
    printf("Resultado do ataque:\n");
    printf("Dado do atacante (%s): %d\n", atacante->nome, dado_atacante);
    printf("Dado do defensor (%s): %d\n", defensor->nome, dado_defensor);
    
    if (dado_atacante > dado_defensor) {
        // Atacante vence: transfere a cor e metade das tropas para o defensor
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        printf("Atacante venceu! O território %s agora pertence à cor %s e tem %d tropas.\n", 
               defensor->nome, defensor->cor, defensor->tropas);
    } else {
        // Atacante perde: perde uma tropa
        atacante->tropas -= 1;
        printf("Atacante perdeu! O território atacante %s perdeu uma tropa e agora tem %d tropas.\n", 
               atacante->nome, atacante->tropas);
    }
    printf("\n");
}

// Função para liberar a memória alocada dinamicamente
// Recebe um ponteiro para o vetor de territórios e libera a memória usando free
void liberarMemoria(struct Territorio* mapa) {
    free(mapa);
}

int main() {
    // Inicializa o gerador de números aleatórios com o tempo atual para garantir aleatoriedade
    srand(time(NULL));
    
    int numTerritorios;
    printf("Digite o número de territórios a serem cadastrados: ");
    scanf("%d", &numTerritorios);
    
    // Alocação dinâmica de memória para o vetor de territórios usando calloc
    // calloc inicializa a memória com zeros, evitando dados lixo
    struct Territorio* mapa = (struct Territorio*) calloc(numTerritorios, sizeof(struct Territorio));
    if (mapa == NULL) {
        printf("Erro na alocação de memória.\n");
        return 1;  // Encerra o programa em caso de erro
    }
    
    // Cadastro dos territórios
    cadastrarTerritorios(mapa, numTerritorios);
    
    // Exibição inicial dos territórios
    exibirTerritorios(mapa, numTerritorios);
    
    // Loop para permitir múltiplos ataques até o usuário decidir parar
    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        // Exibe os territórios disponíveis para orientar o jogador
        exibirTerritorios(mapa, numTerritorios);
        
        int idx_atacante, idx_defensor;
        printf("Escolha o índice do território atacante (1 a %d): ", numTerritorios);
        scanf("%d", &idx_atacante);
        idx_atacante--;  // Ajusta para índice baseado em 0
        
        printf("Escolha o índice do território defensor (1 a %d): ", numTerritorios);
        scanf("%d", &idx_defensor);
        idx_defensor--;  // Ajusta para índice baseado em 0
        
        // Validação das escolhas
        if (idx_atacante < 0 || idx_atacante >= numTerritorios || 
            idx_defensor < 0 || idx_defensor >= numTerritorios) {
            printf("Índices inválidos. Tente novamente.\n\n");
            continue;
        }
        if (strcmp(mapa[idx_atacante].cor, mapa[idx_defensor].cor) == 0) {
            printf("Não é possível atacar um território da mesma cor. Escolha novamente.\n\n");
            continue;
        }
        if (mapa[idx_atacante].tropas <= 0) {
            printf("O território atacante não tem tropas suficientes para atacar.\n\n");
            continue;
        }
        
        // Realiza o ataque usando ponteiros
        atacar(&mapa[idx_atacante], &mapa[idx_defensor]);
        
        // Exibe os dados atualizados após o ataque
        exibirTerritorios(mapa, numTerritorios);
        
        // Pergunta se o usuário deseja continuar atacando
        printf("Deseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);  // O espaço antes de %c ignora espaços em branco
    }
    
    // Liberação da memória alocada
    liberarMemoria(mapa);
    
    printf("Programa encerrado. Memória liberada.\n");
    return 0;
}
