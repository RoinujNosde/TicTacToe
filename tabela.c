#include "tabela.h"
#include <stdlib.h>
#include <stdio.h>

char *criar_tabela()
{
    char *tabela = malloc(10 * sizeof(char));
    for (int i = 0; i < 9; i++)
    {
        tabela[i] = '_';
    }

    return tabela;
}

void imprimir_tabela(char tabela[10])
{
    printf("\n");
    printf("   A   B   C \n");
    printf("0 _%c_|_%c_|_%c_\n", tabela[0], tabela[1], tabela[2]);
    printf("1 _%c_|_%c_|_%c_\n", tabela[3], tabela[4], tabela[5]);
    printf("2 _%c_|_%c_|_%c_\n", tabela[6], tabela[7], tabela[8]);
    printf("\n");
}

int posicao_disponivel(int posicao, char tabela[10])
{
    if (posicao >= 0 && posicao < 9)
    {
        if (tabela[posicao] != 'X' && tabela[posicao] != 'O')
        {
            return 1;
        }
    }
    return 0;
}

int houve_vitoria(char tabela[10])
{
    //comparando por linhas iguais
    for (int i = 0; i < 7; i = i + 3)
    {
        if (tabela[i] == '_')
        {
            continue;
        }
        if (tabela[i] == tabela[i + 1] && tabela[i] == tabela[i + 2])
        {
            return 1;
        }
    }
    //comparando por colunas iguais
    for (int i = 0; i < 3; i++)
    {
        if (tabela[i] == '_')
        {
            continue;
        }
        if (tabela[i] == tabela[i + 3] && tabela[i] == tabela[i + 6])
        {
            return 1;
        }
    }
    //comparando diagonais, o meio sempre deve estar preenchido
    if (tabela[4] != '_')
    {
        //comparando da esquerda para a direita
        if (tabela[0] == tabela[4] && tabela[0] == tabela[8])
        {
            return 1;
        }
        //comparando da direita para a esquerda
        if (tabela[2] == tabela[4] && tabela[4] == tabela[6])
        {
            return 1;
        }
    }
    return 0;
}

void marcar_posicao(int posicao_escolhida, char tabela[10], int jogador)
{
    char marcacao;
    if (jogador)
    {
        marcacao = 'X';
    }
    else
    {
        marcacao = 'O';
    }
    tabela[posicao_escolhida] = marcacao;
}

int houve_empate(char tabela[10])
{
    for (int i = 0; i < 9; i++)
    {
        if (tabela[i] == '_')
        {
            return 0;
        }
    }

    return 1;
}
