#include <Windows.h>
#include <iostream>
#include "terminal_control.h"
#include "game.h"

using namespace std;

TicTacToe::TicTacToe()
{
	// TODO: Change home thingy to start referencing from this instead
	cout << BOLD() << "##################################\n";
	cout << "          " << BG_CYAN() << "TIC" << BG_BLACK() << " ";
	cout << FG_BLACK() << BG_WHITE() << "TAC" << FG_WHITE() << BG_BLACK() << " ";
	cout << BG_RED() << "TOE" << CLEAR_FORMAT() << "\n";
	cout << BOLD() << "##################################\n\n" << CLEAR_FORMAT();
	cout << "    1   2   3";
	cout << "\n\n\n 1 \n\n\n\n 2 \n\n\n\n 3 ";

	COORD pos = getCursorPosition();
	board = new Board(pos.Y - 8, pos.X + 1);
	board->draw();

	textBottom = new TextBox(pos.Y + 4, pos.X);
	textMain = new TextBox(pos.Y - 3, pos.X + 15);
	textWarn = new TextBox(pos.Y - 6, pos.X + 15);
}

TicTacToe::~TicTacToe()
{
	delete &computer, &board, &textWarn, &textMain, &textBottom;
}

void TicTacToe::loop()
{
	const Board& board = *this->board;

	bool playerGoingFirst = true;

	while (1)
	{
		board.clear();
		Cell::State playerSign = player_select();
		Cell::State aiSign = Cell::oppositeOf(playerSign);
		computer.setSign(aiSign);

		Cell::State currentTurn = playerGoingFirst ? playerSign : aiSign;
		bool gameOver = false;

		while (!gameOver)
		{
			if (currentTurn == playerSign)
			{
				string pos = input("Row and col (xy): ");
				const char row[] = { pos[0], '\0' };
				const char col[] = { pos[1], '\0' };

				board(atoi(row), atoi(col)) = playerSign;
			}
			else
			{
				BoardPos ai_move = computer.decideMove(board.getState());

				board(ai_move.col, ai_move.row) = aiSign;
			}

			BoardState currentState = board.getState();
			int eval = currentState.evaluate(currentTurn);
			if (eval == BoardState::WIN)
			{
				gameOver = true;
				textBottom->clear();
				if (currentTurn == playerSign)
					textBottom->show("You have beaten the computer!");
				else
					textBottom->show("The computer defeated you. Very sad");
			}
			else if (!currentState.moves_left())
			{
				gameOver = true;
				textBottom->clear();
				textBottom->show("We've reached a draw");
			}

			currentTurn = Cell::oppositeOf(currentTurn);
		}

		string playAgain = input("Play again (y/n)? ");
		if (playAgain == "n")
		{
			textMain->clear();
			textBottom->clear();
			textMain->show("Thanks for playing! <3");
			while (1) {}
		}

		textBottom->clear();
		playerGoingFirst ^= 1;
	}
}

Cell::State TicTacToe::player_select() const
{
	string chosen_player = input(RED("X") " or " CYAN("O") "? ");

	if (chosen_player == "X")
		return Cell::State::X;
	else if (chosen_player == "O")
		return Cell::State::O;
}

string TicTacToe::input(const char* const query) const
{
	textMain->show(query);
	string in;
	cin >> in;

	return in;
}