#include <Windows.h>
#include "game.h"

int main()
{
	HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode;
	GetConsoleMode(stdOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(stdOut, dwMode);

	SetConsoleTitle(L"Tic Tac Toe");

	TicTacToe game;

	game.loop();
}