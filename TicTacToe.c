#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tabela.h"
#include "interacao.h"
#include "ai.h"

void iniciar_um_jogador();
void iniciar_dois_jogadores();

int main()
{
    printf("  _______ _   _______      _______           __   ___  \n");
    printf(" |__   __(_) |__   __|    |__   __|         /_ | / _ \\ \n");
    printf("    | |   _  ___| | __ _  ___| | ___   ___   | || | | |\n");
    printf("    | |  | |/ __| |/ _` |/ __| |/ _ \\ / _ \\  | || | | |\n");
    printf("    | |  | | (__| | (_| | (__| | (_) |  __/  | || |_| |\n");
    printf("    |_|  |_|\\___|_|\\__,_|\\___|_|\\___/ \\___|  |_(_)___/ \n");

    while (1)
    {

        int modo = solicitar_modo_de_jogo();

        if (modo == 2)
        {
            iniciar_dois_jogadores();
        }
        else
        {
            iniciar_um_jogador();
        }

        printf("\n\n\n\n--> Deseja jogar de novo? (1) Sim - (2) - Não\n");
        int opcao;
        scanf("%d", &opcao);
        if (opcao != 1)
        {
            printf("\nAté mais! Espero que tenha gostado do jogo!\n");
            break;
        }
    }
}

void iniciar_um_jogador()
{
    printf("\nIniciando modo de um jogador!\n");

    char *tabela = criar_tabela();
    char player1[21];

    solicitar_nome_do_usuario(player1);

    int proximo = 1;

    while (1)
    {
        int posicao_escolhida;
        char proximo_nome[21];

        imprimir_tabela(tabela);
        if (proximo)
        {
            printf("É a sua vez, %s!\n", player1);
            strcpy(proximo_nome, player1);
            solicitar_posicao(&posicao_escolhida);
        }
        else
        {
            printf("O computador já jogou!\n");
            strcpy(proximo_nome, "computador");

            computador_solicitar_posicao(&posicao_escolhida, tabela);
        }

        if (posicao_disponivel(posicao_escolhida, tabela))
        {
            marcar_posicao(posicao_escolhida, tabela, proximo);
            int fim_de_jogo = 0;
            if (houve_vitoria(tabela))
            {
                printf("\n\n\nVocê venceu, %s!\n", proximo_nome);
                fim_de_jogo = 1;
            }
            else if (houve_empate(tabela))
            {
                printf("\n\n\nJogo empatado!\n");
                fim_de_jogo = 1;
            }
            if (fim_de_jogo)
            {
                imprimir_tabela(tabela);
                break;
            }

            //proximo jogador
            proximo = !proximo;
        }
        else
        {
            printf("A posição escolhida não está disponível ou não é válida!\n");
        }
    }
    free(tabela);
}

void iniciar_dois_jogadores()
{
    printf("\nIniciando modo de dois jogadores!\n");
    char *tabela = criar_tabela();

    char player1[21];
    char player2[21];

    solicitar_nome_do_usuario(player1);
    solicitar_nome_do_usuario(player2);

    //variavel estática para que o próximo usuário alterne entre partidas
    static int proximo = 1;

    while (1)
    {
        char proximo_nome[21];

        imprimir_tabela(tabela);
        if (proximo)
        {
            strcpy(proximo_nome, player1);
        }
        else
        {
            strcpy(proximo_nome, player2);
        }
        printf("É sua vez, %s!\n", proximo_nome);

        int posicao_escolhida = 0;
        solicitar_posicao(&posicao_escolhida);

        if (posicao_disponivel(posicao_escolhida, tabela))
        {
            marcar_posicao(posicao_escolhida, tabela, proximo);
            int fim_de_jogo = 0;
            if (houve_vitoria(tabela))
            {
                printf("\n\n\nVocê venceu, %s!\n", proximo_nome);
                fim_de_jogo = 1;
            }
            else if (houve_empate(tabela))
            {
                printf("\n\n\nJogo empatado!\n");
                fim_de_jogo = 1;
            }
            if (fim_de_jogo)
            {
                imprimir_tabela(tabela);
                break;
            }
            //proximo jogador
            proximo = !proximo;
        }
        else
        {
            printf("A posição escolhida não está disponível ou não é válida!\n");
        }
    }
    free(tabela);
}
