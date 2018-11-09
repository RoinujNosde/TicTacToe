tictactoe: TicTacToe.c interacao.c tabela.c
	gcc -o TicTacToe interacao.c tabela.c ai.c TicTacToe.c
clean:
	rm -rf TicTacToe
