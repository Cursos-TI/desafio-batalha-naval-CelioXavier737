#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define AGUA 0
#define NAVIO 3

// Função para imprimir o tabuleiro
void imprimir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Imprime o cabeçalho das colunas (letras A a J)
    printf("   ");
    for (char letra = 'A'; letra <= 'J'; letra++) {
        printf(" %c ", letra);
    }
    printf("\n");

    // Imprime cada linha com numeração e conteúdo
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf(" %d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Verifica se há espaço vazio para navio horizontal ou vertical
int posicao_vazia(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char direcao) {
    if (direcao == 'H' || direcao == 'h') {
        if (coluna + 3 > TAMANHO_TABULEIRO) return 0;
        for (int j = coluna; j < coluna + 3; j++) {
            if (tabuleiro[linha][j] != AGUA) return 0;
        }
    } else if (direcao == 'V' || direcao == 'v') {
        if (linha + 3 > TAMANHO_TABULEIRO) return 0;
        for (int i = linha; i < linha + 3; i++) {
            if (tabuleiro[i][coluna] != AGUA) return 0;
        }
    }
    return 1;
}

// Verifica se há espaço vazio para navio diagonal
int posicao_vazia_diagonal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char direcao) {
    if (direcao == 'D' || direcao == 'd') { // Diagonal principal (↘)
        if (linha + 3 > TAMANHO_TABULEIRO || coluna + 3 > TAMANHO_TABULEIRO) return 0;
        for (int k = 0; k < 3; k++) {
            if (tabuleiro[linha + k][coluna + k] != AGUA) return 0;
        }
    } else if (direcao == 'E' || direcao == 'e') { // Diagonal secundária (↙)
        if (linha + 3 > TAMANHO_TABULEIRO || coluna - 2 < 0) return 0;
        for (int k = 0; k < 3; k++) {
            if (tabuleiro[linha + k][coluna - k] != AGUA) return 0;
        }
    }
    return 1;
}

int main() {
    // Declara e inicializa o tabuleiro com 0 (água)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {AGUA};

    // Vetores representando navios de tamanho 3
    int navio1[3] = {NAVIO, NAVIO, NAVIO};  // Horizontal
    int navio2[3] = {NAVIO, NAVIO, NAVIO};  // Vertical
    int navio3[3] = {NAVIO, NAVIO, NAVIO};  // Diagonal principal
    int navio4[3] = {NAVIO, NAVIO, NAVIO};  // Diagonal secundária

    printf("Tabuleiro inicial:\n\n");
    imprimir_tabuleiro(tabuleiro);
    printf("\n**********\n\n");

    // Posiciona navio horizontal
    if (posicao_vazia(tabuleiro, 2, 1, 'H')) {
        for (int k = 0; k < 3; k++) {
            tabuleiro[2][1 + k] = NAVIO;
        }
    }

    // Posiciona navio vertical
    if (posicao_vazia(tabuleiro, 5, 2, 'V')) {
        for (int k = 0; k < 3; k++) {
            tabuleiro[5 + k][2] = NAVIO;
        }
    }

    // Posiciona navio na diagonal principal (↘)
    if (posicao_vazia_diagonal(tabuleiro, 2, 5, 'D')) {
        for (int k = 0; k < 3; k++) {
            tabuleiro[2 + k][5 + k] = NAVIO;
        }
    }

    // Posiciona navio na diagonal secundária (↙)
    if (posicao_vazia_diagonal(tabuleiro, 0, 9, 'E')) {
        for (int k = 0; k < 3; k++) {
            tabuleiro[0 + k][9 - k] = NAVIO;
        }
    }

    // Exibe o tabuleiro com os 4 navios posicionados
    printf("Tabuleiro após posicionar os quatro navios (horizontal, vertical e dois diagonais):\n\n");
    imprimir_tabuleiro(tabuleiro);
    printf("\n**********\n\n");

    return 0;
}