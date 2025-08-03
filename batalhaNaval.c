#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
#define AGUA 0
#define NAVIO 3
#define CONE 1
#define CRUZ 2
#define OCTAEDRO 4

void imprimir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("   ");
    for (char letra = 'A'; letra <= 'J'; letra++) {
        printf(" %c ", letra);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            int val = tabuleiro[i][j];
            if(val == AGUA)
                printf(" 0 ");
            else if(val == NAVIO)
                printf(" 3 ");
            else if(val == CONE)
                printf(" 1 ");
            else if(val == CRUZ)
                printf(" 2 ");
            else if(val == OCTAEDRO)
                printf(" 4 ");
            else
                printf(" ? ");
        }
        printf("\n");
    }
}

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

// Preenche matrizes de habilidades (cone 3x5, cruz 3x3, octaedro 5x5)
void preencher_matriz_cone(int matriz[3][5]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            matriz[i][j] = (j >= 2 - i && j <= 2 + i) ? 1 : 0;
        }
    }
}

void preencher_matriz_cruz(int matriz[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matriz[i][j] = (i == 1 || j == 1) ? 1 : 0;
        }
    }
}

void preencher_matriz_octaedro(int matriz[5][5]) {
    int centro = 2;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matriz[i][j] = (abs(i - centro) + abs(j - centro) <= centro) ? 1 : 0;
        }
    }
}

void aplicar_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                        int origem_l, int origem_c,
                        int altura, int largura,
                        int matriz_habilidade[altura][largura],
                        int valor_habilidade) {
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            if (matriz_habilidade[i][j] == 1) {
                int lin_tab = origem_l + i;
                int col_tab = origem_c + j;
                if (lin_tab >= 0 && lin_tab < TAMANHO_TABULEIRO && col_tab >= 0 && col_tab < TAMANHO_TABULEIRO) {
                    if (tabuleiro[lin_tab][col_tab] == AGUA) {
                        tabuleiro[lin_tab][col_tab] = valor_habilidade;
                    }
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = { {0} };

    // Preencher matrizes de habilidades
    int matriz_cone[3][5];
    int matriz_cruz[3][3];
    int matriz_octaedro[5][5];

    preencher_matriz_cone(matriz_cone);
    preencher_matriz_cruz(matriz_cruz);
    preencher_matriz_octaedro(matriz_octaedro);

    // Aplicar habilidades no tabuleiro (áreas vazias)
    aplicar_habilidade(tabuleiro, 2, 4, 3, 5, matriz_cone, CONE);
    aplicar_habilidade(tabuleiro, 5, 6, 3, 3, matriz_cruz, CRUZ);
    aplicar_habilidade(tabuleiro, 5, 2, 5, 5, matriz_octaedro, OCTAEDRO);

    // Posicionar navios SEM sobrepor nenhuma outra peça
    posicionar_navio_no_tabuleiro(tabuleiro, 0, 0, 'H', 3);
    posicionar_navio_no_tabuleiro(tabuleiro, 4, 0, 'V', 3);

    // Navio diagonal na posição (9,0) até (7,2)
    posicionar_navio_no_tabuleiro(tabuleiro, 7, 0, 'D', 3); 
    posicionar_navio_no_tabuleiro(tabuleiro, 0, 9, 'E', 3); 

    imprimir_tabuleiro(tabuleiro);

    return 0;
}