#include <stdio.h>
#include <stdlib.h> // Para malloc, free, exit
#include <string.h> // Para strcpy

/**
 * @brief Define a estrutura de um cômodo (nó) da mansão.
 * * Cada cômodo possui um nome e ponteiros para os caminhos da
 * esquerda e da direita, que podem levar a outros cômodos.
 */
typedef struct Sala {
    char nome[100];            // Nome do cômodo
    struct Sala *esquerda;     // Ponteiro para o cômodo à esquerda
    struct Sala *direita;      // Ponteiro para o cômodo à direita
} Sala;

/**
 * @brief Cria (aloca dinamicamente) um novo cômodo (Sala).
 * * Aloca memória para uma nova Sala, define seu nome
 * e inicializa seus caminhos (filhos) como nulos.
 * * @param nome O nome a ser atribuído ao novo cômodo.
 * @return Um ponteiro para a Sala recém-criada.
 */
Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    
    // Verifica se a alocação de memória foi bem-sucedida
    if (novaSala == NULL) {
        printf("Erro critico: Falha ao alocar memoria para a sala.\n");
        exit(1); 
    }
    
    strcpy(novaSala->nome, nome);
    
    // Inicializa os caminhos como nulos (sem saída)
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

/**
 * @brief Permite a navegação interativa do jogador pela mansão (árvore).
 * * Começando pela sala inicial (raiz), o jogador pode escolher
 * 'e' (esquerda), 'd' (direita) ou 's' (sair). A exploração
 * continua até que o jogador saia ou chegue a um cômodo sem saídas
 * (um nó-folha).
 * * @param salaInicial O ponto de partida da exploração (geralmente o "Hall de Entrada").
 */
void explorarSalas(Sala* salaInicial) {
    Sala* salaAtual = salaInicial; // O jogador começa na sala inicial
    char escolha;

    printf("--- Detective Quest: O Mistério da Mansão ---\n");
    printf("Bem-vindo(a) a mansao! Encontre o culpado.\n");
    printf("Explore os comodos escolhendo 'e' (esquerda) ou 'd' (direita).\n");
    printf("Digite 's' a qualquer momento para desistir e sair do jogo.\n");

    while (1) {
        // Exibe a localização atual do jogador
        printf("\n========================================\n");
        printf("VoCE ESTA EM: %s\n", salaAtual->nome);
        printf("========================================\n");

        // Condição de parada: verifica se é um nó-folha (sem saídas)
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("Voce chegou a um comodo sem saidas.\n");
            printf("Parece que nao ha mais para onde ir a partir daqui.\n");
            printf("Fim da exploracao.\n");
            break;
        }

        // Apresenta as opções de caminho
        printf("Escolha seu caminho:\n");
        if (salaAtual->esquerda != NULL) {
            printf(" (e) Esquerda: [ %s ]\n", salaAtual->esquerda->nome);
        }
        if (salaAtual->direita != NULL) {
            printf(" (d) Direita:  [ %s ]\n", salaAtual->direita->nome);
        }
        printf(" (s) Sair do jogo\n");
        printf("Sua escolha: ");

        scanf(" %c", &escolha);

        switch (escolha) {
            case 'e':
            case 'E':
                if (salaAtual->esquerda != NULL) {
                    salaAtual = salaAtual->esquerda;
                } else {
                    printf("-> Nao ha caminho para a esquerda.\n");
                }
                break;

            case 'd':
            case 'D':
                if (salaAtual->direita != NULL) {
                    salaAtual = salaAtual->direita;
                } else {
                    printf("-> Nao ha caminho para a direita.\n");
                }
                break;

            case 's':
            case 'S':
                printf("\nVoce decidiu sair da mansao. Ate a proxima, detetive!\n");
                return; 

            default:
                printf("-> Opcao invalida! Tente 'e', 'd' ou 's'.\n");
                break;
        }
    }
}

/**
 * @brief Libera toda a memória alocada dinamicamente para o mapa.
 * * Usa um percurso em pós-ordem para garantir que os filhos
 * sejam liberados antes do pai.
 * * @param sala A sala raiz do mapa a ser liberado.
 */
void liberarMapa(Sala* sala) {
    // Caso base da recursão
    if (sala == NULL) {
        return;
    }
    
    liberarMapa(sala->esquerda);

    liberarMapa(sala->direita);
    
    free(sala);
}

/**
 * @brief Função principal (main) - Ponto de entrada do programa.
 * * Monta o mapa inicial da mansão (a árvore binária)
 * de forma manual no código, usando a função criarSala().
 * Em seguida, dá início à exploração e, ao final,
 * libera a memória alocada.
 * * @return 0 se o programa for executado com sucesso.
 */
int main() {
    // --- Montagem do Mapa da Mansão ---
    
    // Nível 0: Raiz
    Sala* hall = criarSala("Hall de Entrada");

    // Nível 1: Filhos do Hall
    hall->esquerda = criarSala("Sala de Estar");
    hall->direita = criarSala("Sala de Jantar");

    // Nível 2: Filhos da Sala de Estar
    hall->esquerda->esquerda = criarSala("Biblioteca");
    hall->esquerda->direita = criarSala("Varanda");

    // Nível 2: Filhos da Sala de Jantar
    hall->direita->esquerda = criarSala("Cozinha");

    // Nível 3: Filhos da Varanda
    hall->esquerda->direita->esquerda = criarSala("Jardim de Inverno");
    
    explorarSalas(hall);

    liberarMapa(hall);
    hall = NULL; 

    return 0;
}