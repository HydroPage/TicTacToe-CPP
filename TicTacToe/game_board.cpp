#include <iostream>
#include "terminal_control.h"
#include "game_board.h"

using namespace std;

Board::Board(uint8_t homeY, uint8_t homeX) : homeY(homeY), homeX(homeX)
{
	for (uint8_t row = 0; row < 3; row++)
		for (uint8_t col = 0; col < 3; col++)
			cells[row][col] = new Cell(homeY + (col * 4), homeX + (row * 4));
}

Board::~Board()
{
	for (uint8_t col = 0; col < 3; col++)
		for (uint8_t row = 0; row < 3; row++)
			delete cells[col][row];
}

Cell& const Board::operator()(uint8_t col, uint8_t row) const
{
	return *cells[col - 1][row - 1];
}

const BoardState Board::getState() const
{
	return BoardState(cells);
}

void Board::clear() const
{
	for (uint8_t col = 0; col < 3; col++)
		for (uint8_t cell = 0; cell < 3; cell++)
			*cells[col][cell] = Cell::State::BLANK;
}

static void drawBackground(uint8_t xOff)
{
	BACKWARD_R(xOff);
	for (uint8_t col = 0; col < 3; col++)
	{
		for (uint8_t line = 0; line < 3; line++)
		{
			FORWARD_R(xOff);
			cout << "   |   |\n";
		}

		if (col != 2)
		{
			FORWARD_R(xOff);
			cout << "---+---+---\n";
		}
	}
}

void Board::draw() const
{
	GOTO_R(homeY, homeX);

	drawBackground(homeX - 1);

	for (uint8_t col = 0; col < 3; col++)
		for (uint8_t cell = 0; cell < 3; cell++)
			cells[col][cell]->draw();
}