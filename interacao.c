#include <stdio.h>
#include "interacao.h"

int solicitar_modo_de_jogo() {
    printf("\nModo de jogo: (1) Um jogador - (2) Dois jogadores\n");
    printf("--> Escolha o modo de jogo: ");
    
    int modo;
    scanf("%d", &modo);
    if (modo != 1 && modo != 2) {
        modo = 1;
    }
    
    printf("\n");
    
    return modo;
}

void solicitar_nome_do_usuario(char nome[21]) {
    printf("\n--> Informe seu nome de usuário (20 caracteres): ");
	scanf("%20s", nome);
}

void solicitar_posicao(int *posicao) {
	printf("\n--> Escolha onde deseja jogar (Ex.: B2, A0, etc): ");
	char input[3];
	scanf(" %2s", input);
	int pos[2];
	
	switch (input[0]) {
		case 'A': case 'a':
			pos[0] = 0;
			break;
		case 'B': case 'b':
			pos[0] = 1;
			break;
		case 'C': case 'c':
			pos[0] = 2;
			break;
		default:
			pos[0] = 0;
	}
	
	pos[1] = input[1] - '0';
	
	*posicao = (pos[1] * 3) + pos[0];
}
