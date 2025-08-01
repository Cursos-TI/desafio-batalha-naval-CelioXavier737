#include <stdio.h>

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.

// Função para imprimir o tabuleiro
void imprimir_tabuleiro(int tabuleiro[10][10]) {
    // Imprime o cabeçalho das colunas (A a J)
    printf("   ");  // Espaço para o canto superior esquerdo
    for (char letra = 'A'; letra <= 'J'; letra++) {
        printf(" %c ", letra);
    }
    printf("\n");

    // Imprime as linhas com números e os dados do tabuleiro
    for (int i = 0; i < 10; i++) {
        printf("%2d ", i);  // Número da linha com espaçamento
        for (int j = 0; j < 10; j++) {
            printf(" %d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}


// Função para verificar se há espaço vazio
int posicao_vazia(int tabuleiro[10][10], int linha, int coluna, char direcao) {
    if (direcao == 'H' || direcao == 'h') {
        if (coluna + 3 > 10) return 0;
        for (int j = coluna; j < coluna + 3; j++) {
            if (tabuleiro[linha][j] != 0) return 0;
        }
    } else if (direcao == 'V' || direcao == 'v') {
        if (linha + 3 > 10) return 0;
        for (int i = linha; i < linha + 3; i++) {
            if (tabuleiro[i][coluna] != 0) return 0;
        }
    }
    return 1;
}


int main() {
    // Nível Novato - Posicionamento dos Navios
    // Sugestão: Declare uma matriz bidimensional para representar o tabuleiro (Ex: int tabuleiro[5][5];).
    // Sugestão: Posicione dois navios no tabuleiro, um verticalmente e outro horizontalmente.
    // Sugestão: Utilize `printf` para exibir as coordenadas de cada parte dos navios.

    // Nível Aventureiro - Expansão do Tabuleiro e Posicionamento Diagonal
    // Sugestão: Expanda o tabuleiro para uma matriz 10x10.
    // Sugestão: Posicione quatro navios no tabuleiro, incluindo dois na diagonal.
    // Sugestão: Exiba o tabuleiro completo no console, mostrando 0 para posições vazias e 3 para posições ocupadas.

    // Nível Mestre - Habilidades Especiais com Matrizes
    // Sugestão: Crie matrizes para representar habilidades especiais como cone, cruz, e octaedro.
    // Sugestão: Utilize estruturas de repetição aninhadas para preencher as áreas afetadas por essas habilidades no tabuleiro.
    // Sugestão: Exiba o tabuleiro com as áreas afetadas, utilizando 0 para áreas não afetadas e 1 para áreas atingidas.

    // Exemplos de exibição das habilidades:
    // Exemplo para habilidade em cone:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 1 1 1 1 1
    
    // Exemplo para habilidade em octaedro:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 0 0 1 0 0

    // Exemplo para habilidade em cruz:
    // 0 0 1 0 0
    // 1 1 1 1 1
    // 0 0 1 0 0

    #define TAMANHO_TABULEIRO 10
    #define AGUA 0
    #define NAVIO 3

    // Declara o tabuleiro
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {AGUA};


    // Navios representados por vetores com valores distintos
    int navio1[3] = {NAVIO, NAVIO, NAVIO};  // Navio1  horizontal
    int navio2[3] = {NAVIO, NAVIO, NAVIO};  // Navio2 vertical

    printf("Tabuleiro inicial:\n\n");
    imprimir_tabuleiro(tabuleiro);
    printf("\n**********\n\n");

    // Posiciona navio1 horizontalmente
    if (posicao_vazia(tabuleiro, 2, 1, 'H')) {
        for (int k = 0; k < 3; k++) {
            tabuleiro[2][1 + k] = navio1[k];  // Copia do vetor navio1 para o tabuleiro
        }
    }

    // Posiciona navio2 verticalmente
    if (posicao_vazia(tabuleiro, 5, 2, 'V')) {
        for (int k = 0; k < 3; k++) {
            tabuleiro[5 + k][2] = navio2[k];  // Copia do vetor navio2 para o tabuleiro
        }
    }

    printf("Tabuleiro após posicionar os navios:\n\n");
    imprimir_tabuleiro(tabuleiro);
    printf("\n**********\n\n");



    return 0;
}
