#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "ai.h"
#include "tabela.h"

static void posicoes_disponiveis(char tabela[10], int posicoes_disponiveis[9]) {
    for (int i = 0; i < 9; i++) {
        if (tabela[i] == '_') {
            posicoes_disponiveis[i] = 1;
        } else {
            posicoes_disponiveis[i] = 0;
        }
    }
}

static int utilidade(char tabela[10], int maximizing_player) {
    if (houve_vitoria(tabela)) {
        if (maximizing_player) {
            return 1;
        } else {
            return -1;
        }
    }
    return 0;
}

static char * resultado(char tabela[10], int posicao, int maximizing_player) {
    char * tabela_simulada = malloc(10 * sizeof (char));
    strncpy(tabela_simulada, tabela, 10);
    marcar_posicao(posicao, tabela_simulada, !maximizing_player);

    return tabela_simulada;
}

static int fim_de_jogo(char tabela[10]) {
    if (houve_vitoria(tabela)) {
        return 1;
    }
    if (houve_empate(tabela)) {
        return 1;
    }

    return 0;
}

static double minimax(char tabela[10], int maximizing_player) {
    if (fim_de_jogo(tabela)) {
        return utilidade(tabela, !maximizing_player);
    }

    int disponiveis[9];
    posicoes_disponiveis(tabela, disponiveis);
    if (maximizing_player) {
        double valor = -INFINITY;
        for (int i = 0; i < 9; i++) {
            if (disponiveis[i]) {
                char * tabela_filha = resultado(tabela, i, maximizing_player);
                valor = fmaxf(valor, minimax(tabela_filha, !maximizing_player));
                
                free(tabela_filha);
            }
        }
        return valor;
    } else {
        double valor = INFINITY;
        for (int i = 0; i < 9; i++) {
            if (disponiveis[i]) {
                char * tabela_filha = resultado(tabela, i, maximizing_player);
                valor = fminf(valor, minimax(tabela_filha, !maximizing_player));

                free(tabela_filha);
            }
        }
        return valor;
    }
}

void computador_solicitar_posicao(int *posicao_escolhida, char tabela[10]) {
    double mm = -INFINITY;
    int posicao = -1;

    int disponiveis[9];
    posicoes_disponiveis(tabela, disponiveis);
    for (int i = 0; i < 9; i++) {
        if (disponiveis[i]) {
            if (posicao == -1) {
                posicao = i;
            }

            char * tabela_i = resultado(tabela, i, 1);
            double temp_mm = minimax(tabela_i, 0);
            if (temp_mm > mm) {
                mm = temp_mm;
                posicao = i;
            }

            free(tabela_i);
        }
    }

    *posicao_escolhida = posicao;
}