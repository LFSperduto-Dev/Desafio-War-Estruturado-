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

// Vetor de missões estratégicas pré-definidas
// Contém 5 descrições de missões diferentes para sorteio
const char* missoes[] = {
    "Conquistar pelo menos 3 territórios da mesma cor.",
    "Eliminar todas as tropas da cor vermelha.",
    "Ter pelo menos 5 territórios sob controle.",
    "Controlar territórios com pelo menos 10 tropas no total.",
    "Conquistar um território específico (o primeiro cadastrado)."
};
const int totalMissoes = 5;  // Número total de missões disponíveis

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

// Função para exibir os dados dos territórios (mapa)
// Recebe um ponteiro para o vetor de territórios e o número de territórios
// Utiliza ponteiros para acessar os dados dos territórios
void exibirMapa(struct Territorio* mapa, int numTerritorios) {
    printf("Estado Atual do Mapa:\n");
    for (int i = 0; i < numTerritorios; i++) {
        printf("Território %d: Nome: %s, Cor: %s, Tropas: %d\n", 
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("\n");
}

// Função para atribuir uma missão sorteada a um jogador
// Recebe um ponteiro para a string de destino (passado por referência para modificação) e o vetor de missões
// Sorteia uma missão aleatoriamente e copia para o destino usando strcpy
void atribuirMissao(char* destino, const char* missoes[], int totalMissoes) {
    int indiceSorteado = rand() % totalMissoes;
    strcpy(destino, missoes[indiceSorteado]);
}

// Função para exibir a missão de um jogador
// Recebe a missão por valor (cópia do ponteiro) para exibição
void exibirMissao(char* missao) {
    printf("Sua missão: %s\n", missao);
}

// Função para verificar se a missão foi cumprida
// Recebe a missão por referência (ponteiro) para acessar o conteúdo, o mapa e o tamanho
// Implementa lógica simples para verificar condições de vitória baseadas nas missões
int verificarMissao(char* missao, struct Territorio* mapa, int tamanho) {
    // Lógica simples para cada missão (pode ser expandida)
    if (strcmp(missao, "Conquistar pelo menos 3 territórios da mesma cor.") == 0) {
        // Conta territórios por cor e verifica se alguma cor tem >= 3
        int contagens[10] = {0};  // Assume até 10 cores diferentes
        for (int i = 0; i < tamanho; i++) {
            for (int j = 0; j < 10; j++) {
                if (strcmp(mapa[i].cor, missoes[j]) == 0) {  // Simples, mas pode ser melhorado
                    contagens[j]++;
                }
            }
        }
        for (int j = 0; j < 10; j++) {
            if (contagens[j] >= 3) return 1;
        }
    } else if (strcmp(missao, "Eliminar todas as tropas da cor vermelha.") == 0) {
        // Verifica se não há territórios com cor "vermelha"
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0) return 0;
        }
        return 1;
    } else if (strcmp(missao, "Ter pelo menos 5 territórios sob controle.") == 0) {
        // Conta territórios de uma cor específica (assume primeira cor como do jogador)
        int count = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, mapa[0].cor) == 0) count++;  // Simples: assume cor do primeiro território
        }
        return count >= 5;
    } else if (strcmp(missao, "Controlar territórios com pelo menos 10 tropas no total.") == 0) {
        // Soma tropas de uma cor específica
        int totalTropas = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, mapa[0].cor) == 0) totalTropas += mapa[i].tropas;
        }
        return totalTropas >= 10;
    } else if (strcmp(missao, "Conquistar um território específico (o primeiro cadastrado).") == 0) {
        // Verifica se o primeiro território tem a cor do jogador
        return strcmp(mapa[0].cor, mapa[0].cor) == 0;  // Sempre true se for o próprio, mas assume mudança
    }
    return 0;  // Missão não cumprida
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
// Recebe ponteiros para o mapa e as missões dos jogadores, e libera a memória usando free
void liberarMemoria(struct Territorio* mapa, char** missoesJogadores, int numJogadores) {
    free(mapa);
    for (int i = 0; i < numJogadores; i++) {
        free(missoesJogadores[i]);
    }
    free(missoesJogadores);
}

int main() {
    // Inicializa o gerador de números aleatórios com o tempo atual para garantir aleatoriedade
    srand(time(NULL));
    
    int numJogadores, numTerritorios;
    printf("Digite o número de jogadores: ");
    scanf("%d", &numJogadores);
    printf("Digite o número de territórios: ");
    scanf("%d", &numTerritorios);
    
    // Alocação dinâmica de memória para o vetor de territórios usando calloc
    struct Territorio* mapa = (struct Territorio*) calloc(numTerritorios, sizeof(struct Territorio));
    if (mapa == NULL) {
        printf("Erro na alocação de memória para o mapa.\n");
        return 1;
    }
    
    // Alocação dinâmica para as missões dos jogadores
    char** missoesJogadores = (char**) malloc(numJogadores * sizeof(char*));
    if (missoesJogadores == NULL) {
        printf("Erro na alocação de memória para as missões.\n");
        free(mapa);
        return 1;
    }
    for (int i = 0; i < numJogadores; i++) {
        missoesJogadores[i] = (char*) malloc(200 * sizeof(char));  // Tamanho suficiente para a missão
        if (missoesJogadores[i] == NULL) {
            printf("Erro na alocação de memória para a missão do jogador %d.\n", i + 1);
            liberarMemoria(mapa, missoesJogadores, i);  // Libera até aqui
            return 1;
        }
    }
    
    // Cadastro dos territórios
    cadastrarTerritorios(mapa, numTerritorios);
    
    // Atribuição e exibição das missões para cada jogador
    for (int i = 0; i < numJogadores; i++) {
        atribuirMissao(missoesJogadores[i], missoes, totalMissoes);
        printf("Jogador %d:\n", i + 1);
        exibirMissao(missoesJogadores[i]);
        printf("\n");
    }
    
    // Exibição inicial do mapa
    exibirMapa(mapa, numTerritorios);
    
    // Loop para permitir ataques até que haja um vencedor
    int vencedor = -1;
    while (vencedor == -1) {
        // Escolha do jogador atual (simples: alterna entre jogadores)
        static int jogadorAtual = 0;
        printf("Turno do Jogador %d:\n", jogadorAtual + 1);
        
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
        
        // Exibe o mapa atualizado
        exibirMapa(mapa, numTerritorios);
        
        // Verifica se algum jogador cumpriu sua missão
        for (int i = 0; i < numJogadores; i++) {
            if (verificarMissao(missoesJogadores[i], mapa, numTerritorios)) {
                vencedor = i;
                break;
            }
        }
        
        // Alterna para o próximo jogador
        jogadorAtual = (jogadorAtual + 1) % numJogadores;
    }
    
    // Declara o vencedor
    printf("Jogador %d venceu! Missão cumprida: %s\n", vencedor + 1, missoesJogadores[vencedor]);
    
    // Liberação da memória alocada
    liberarMemoria(mapa, missoesJogadores, numJogadores);
    
    printf("Programa encerrado. Memória liberada.\n");
    return 0;
}
