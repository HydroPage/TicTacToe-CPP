#include <iostream>
#include <cstring>
#include <string>
#include "terminal_control.h"
#include "game.h"

using namespace std;

static const string invalidInput(const string&, size_t);

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
	textWarn = new WarnBox(pos.Y - 6, pos.X + 15);
}

TicTacToe::~TicTacToe()
{
	delete &computer, &board, &textMain, &textBottom, &textWarn;
}

static Cell::State player;
static Cell::State turn;

void TicTacToe::loop()
{
	const Board& board = *this->board;

	bool playerGoingFirst = true;

	while (1)
	{
		board.clear();

		player = playerSelect();
		Cell::State aiSign = Cell::oppositeOf(player);
		computer.setSign(aiSign);

		Cell::State turn = playerGoingFirst ? player : aiSign;

		while (1)
		{
			const BoardPos move = (turn == player) ? selectPos() : computer.decideMove(board.getState());
			board(move.row, move.cell) = turn;

			if (checkGameOver())
				break;

			turn = Cell::oppositeOf(turn);
		}

		string playAgain = input("Play again (y/n)? ");
		if (playAgain == "n")
		{
			textBottom->clear();
			textMain->show("Thanks for playing! <3");
			while (1) {}
		}

		textBottom->clear();
		playerGoingFirst ^= 1;
	}
}

bool TicTacToe::checkGameOver() const
{
	const Board& board = *this->board;

	BoardState currentState = board.getState();
	int8_t eval = currentState.evaluate(turn);

	if (eval == BoardState::WIN)
	{
		const char* const endMessage = (turn == player) ? 
			"You have beaten the computer!" :
			"The computer defeated you. Very sad";

		textBottom->show(endMessage);
		return true;
	}
	else if (!currentState.movesLeft())
	{
		textBottom->show("We've reached a draw");
		return true;
	}

	return false;
}

const Cell::State TicTacToe::playerSelect() const
{
	while (1)
	{
		string out = input(RED("X") " or " CYAN("O") "? ");

		if (out.length() != 1)
		{
			textWarn->show(invalidInput(out, 24).c_str());
			continue;
		}
		else
		{
			out[0] = toupper(out[0]);

			if (out == "X")
			{
				textWarn->clear();
				return Cell::State::X;
			}
			else if (out == "O")
			{
				textWarn->clear();
				return Cell::State::O;
			}
			else
				continue;
		}
	}
}

const string invalidInput(const string& input, size_t maxSize)
{
	string out("Invalid input \"");

	out.append(input);

	if (out.size() > maxSize)
	{
		out.resize(maxSize - 4);
		out.append("...\"");
	}
	else
	{
		out.append("\"");
	}

	return out;
}

const BoardPos TicTacToe::selectPos() const
{
	BoardPos out;
	string pos = input("Column and row (xy): ");

	const char cell[] = { pos[0], '\0' };
	const char row[] = { pos[1], '\0' };

	out.cell = atoi(cell) - 1;
	out.row = atoi(row) - 1;

	return out;
}

const string TicTacToe::input(const char* const query) const
{
	textMain->show(query);
	string in;

	getline(cin, in);

	return in;
}