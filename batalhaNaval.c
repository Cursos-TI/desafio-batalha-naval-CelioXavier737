#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define AGUA 0
#define NAVIO 3
#define CONE 1
#define CRUZ 2
#define OCTAEDRO 4

// Função para imprimir o tabuleiro
void imprimir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("   ");
    for (char letra = 'A'; letra <= 'J'; letra++) {
        printf(" %c ", letra);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf(" %d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para posicionar navio com base na direção
void posicionar_navio_no_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                                   int linha, int coluna, char direcao, int tamanho_navio) {
    int pode_posicionar = 1;

    if (direcao == 'H' || direcao == 'h') {
        if (coluna + tamanho_navio > TAMANHO_TABULEIRO) return;
        for (int j = coluna; j < coluna + tamanho_navio; j++) {
            if (tabuleiro[linha][j] != AGUA) pode_posicionar = 0;
        }
        if (pode_posicionar) {
            for (int j = coluna; j < coluna + tamanho_navio; j++) {
                tabuleiro[linha][j] = NAVIO;
            }
        }
    }
    else if (direcao == 'V' || direcao == 'v') {
        if (linha + tamanho_navio > TAMANHO_TABULEIRO) return;
        for (int i = linha; i < linha + tamanho_navio; i++) {
            if (tabuleiro[i][coluna] != AGUA) pode_posicionar = 0;
        }
        if (pode_posicionar) {
            for (int i = linha; i < linha + tamanho_navio; i++) {
                tabuleiro[i][coluna] = NAVIO;
            }
        }
    }
    else if (direcao == 'D' || direcao == 'd') {
        if (linha + tamanho_navio > TAMANHO_TABULEIRO || coluna + tamanho_navio > TAMANHO_TABULEIRO) return;
        for (int k = 0; k < tamanho_navio; k++) {
            if (tabuleiro[linha + k][coluna + k] != AGUA) pode_posicionar = 0;
        }
        if (pode_posicionar) {
            for (int k = 0; k < tamanho_navio; k++) {
                tabuleiro[linha + k][coluna + k] = NAVIO;
            }
        }
    }
    else if (direcao == 'E' || direcao == 'e') {
        if (linha + tamanho_navio > TAMANHO_TABULEIRO || coluna - (tamanho_navio - 1) < 0) return;
        for (int k = 0; k < tamanho_navio; k++) {
            if (tabuleiro[linha + k][coluna - k] != AGUA) pode_posicionar = 0;
        }
        if (pode_posicionar) {
            for (int k = 0; k < tamanho_navio; k++) {
                tabuleiro[linha + k][coluna - k] = NAVIO;
            }
        }
    }
}

// Funções para posicionar habilidades especiais
void posicionar_cruz(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int l, int c) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if ((i == 0 || j == 0) && l + i >= 0 && l + i < TAMANHO_TABULEIRO && c + j >= 0 && c + j < TAMANHO_TABULEIRO) {
                if (tabuleiro[l + i][c + j] == AGUA) tabuleiro[l + i][c + j] = CRUZ;
            }
        }
    }
}

void posicionar_octaedro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int l, int c) {
    int delta[5][2] = {{0,0}, {-1,0}, {1,0}, {0,-1}, {0,1}};
    for (int i = 0; i < 5; i++) {
        int nl = l + delta[i][0];
        int nc = c + delta[i][1];
        if (nl >= 0 && nl < TAMANHO_TABULEIRO && nc >= 0 && nc < TAMANHO_TABULEIRO) {
            if (tabuleiro[nl][nc] == AGUA) tabuleiro[nl][nc] = OCTAEDRO;
        }
    }
}

void posicionar_cone(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int l, int c) {
    for (int i = 0; i < 3; i++) {
        for (int j = -i; j <= i; j++) {
            int nl = l + i;
            int nc = c + j;
            if (nl >= 0 && nl < TAMANHO_TABULEIRO && nc >= 0 && nc < TAMANHO_TABULEIRO) {
                if (tabuleiro[nl][nc] == AGUA) tabuleiro[nl][nc] = CONE;
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {AGUA};

    // Posiciona navios em locais livres (sem sobrescrever)
    posicionar_navio_no_tabuleiro(tabuleiro, 0, 0, 'H', 3);
    posicionar_navio_no_tabuleiro(tabuleiro, 4, 0, 'V', 3);
    posicionar_navio_no_tabuleiro(tabuleiro, 6, 1, 'D', 3);
    posicionar_navio_no_tabuleiro(tabuleiro, 1, 9, 'E', 3);

    // Posiciona figuras sem sobreposição
    posicionar_cone(tabuleiro, 2, 4);       // cone 3x5
    posicionar_cruz(tabuleiro, 5, 6);       // cruz 3x3
    posicionar_octaedro(tabuleiro, 8, 8);   // octaedro 5x5

    imprimir_tabuleiro(tabuleiro);
    printf("\n3 - Navio, 1 - Cone, 2 - Cruz, 4 - Octaedro\n");

    return 0;
}