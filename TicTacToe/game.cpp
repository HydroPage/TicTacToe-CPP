#include <iostream>
#include <cstring>
#include <string>
#include "terminal_control.h"
#include "game.h"

using namespace std;

static bool isNumeric(const string&);
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

TicTacToe::BadInput::BadInput(const char* const msg) : msg(msg) {}
TicTacToe::BadInput::BadInput(const string& msgStr) : BadInput(msgStr.c_str()) {}

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

		turn = playerGoingFirst ? player : aiSign;

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

const BoardPos TicTacToe::selectPos() const
{
	BoardPos out;

	while (true)
	try
	{
		string posInputStr = input("Column and row (xy): ");

		if (isNumeric(posInputStr))
		{
			if (posInputStr.size() == 2)
			{
				const char cell[] = { posInputStr[0], '\0' };
				const char row[]  = { posInputStr[1], '\0' };

				out.cell = atoi(cell) - 1;
				out.row  = atoi(row)  - 1;

				bool cellInRange = out.cell >= 0 && out.cell <= 2;
				bool rowInRange  = out.row  >= 0 && out.row  <= 2;

				if (cellInRange && rowInRange)
				{
					return out;
				}
				else throw BadInput("Only numbers 1-3");
			}
			else throw BadInput(string("Just two numbers, that's ") + to_string(posInputStr.size()));
		}
		else throw BadInput("Numbers only please");
	}
	catch (BadInput& err)
	{
		textWarn->show(err.msg);
	}
}

bool isNumeric(const string& str)
{
	for (const auto &c : str)
	{
		if (!isdigit(c))
			return false;
	}

	return true;
}

const string TicTacToe::input(const char* const query) const
{
	textMain->show(query);
	string in;

	getline(cin, in);

	return in;
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