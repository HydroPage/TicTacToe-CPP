#include <iostream>
#include "terminal_control.h"
#include "game_board.h"

using namespace std;

static void drawBackground(uint8_t);

Board::Board(uint8_t homeY, uint8_t homeX) : homeY(homeY), homeX(homeX)
{
	for (uint8_t row = 0; row < 3; row++)
		for (uint8_t cell = 0; cell < 3; cell++)
		{
			GOTO_R(homeY + (row * 4), homeX + (cell * 4));
			cells[row][cell] = new Cell(homeY + (row * 4), homeX + (cell * 4));
		}
}

Board::~Board()
{
	for (uint8_t row = 0; row < 3; row++)
		for (uint8_t cell = 0; cell < 3; cell++)
			delete cells[row][cell];
}

Cell& Board::operator()(uint8_t row, uint8_t cell) const
{
	return *cells[row][cell];
}

const BoardState Board::getState() const
{
	return BoardState::of(cells);
}

void Board::clear() const
{
	for (uint8_t row = 0; row < 3; row++)
		for (uint8_t cell = 0; cell < 3; cell++)
			*cells[row][cell] = Cell::State::BLANK;
}

void Board::draw() const
{
	GOTO_R(homeY, homeX);

	drawBackground(homeX - 1);

	for (uint8_t row = 0; row < 3; row++)
		for (uint8_t cell = 0; cell < 3; cell++)
			cells[row][cell]->draw();
}

void drawBackground(uint8_t xOff)
{
	BACKWARD_R(xOff);
	for (uint8_t row = 0; row < 3; row++)
	{
		for (uint8_t line = 0; line < 3; line++)
		{
			FORWARD_R(xOff);
			cout << "   |   |\n";
		}

		if (row != 2)
		{
			FORWARD_R(xOff);
			cout << "---+---+---\n";
		}
	}
}