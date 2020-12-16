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

	COORD size;
	size.Y = 50; size.X = 50;
	SetConsoleScreenBufferSize(stdOut, size);

	TicTacToe game;

	game.loop();
}