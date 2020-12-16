#include <iostream>
#include "cell.h"
#include "terminal_control.h"

Cell::Cell(uint8_t homeY, uint8_t homeX) : homeY(homeY), homeX(homeX), currentState(Cell::State::BLANK) {}
Cell::Cell() : Cell(0, 0) {};

const char* const Cell::X[3] = { RED("\\ /") ,  RED(" X "),  RED("/ \\") };
const char* const Cell::O[3] = { CYAN("/-\\") , CYAN("| |"), CYAN("\\-/") };

Cell::State Cell::oppositeOf(Cell::State state)
{
	switch (state)
	{
	case Cell::State::X:
		return Cell::State::O;
		break;
	case Cell::State::O:
		return Cell::State::X;
		break;
	default:
		return Cell::State::BLANK;
	}
}

bool Cell::isBlank(Cell::State state)
{
	return state == Cell::State::BLANK;
}

Cell::operator State() const
{
	return currentState;
}

void Cell::operator=(State new_state)
{
	currentState = new_state;
	draw();
}

void Cell::draw() const
{
	GOTO_R(homeY, 1);

	for (uint8_t line = 0; line < 3; line++)
	{
		FORWARD_R(homeX - 1);

		switch (currentState)
		{
		case State::BLANK:
			std::cout << "   ";
			break;
		case State::X:
			std::cout << X[line];
			break;
		case State::O:
			std::cout << O[line];
		}

		std::cout << "\n";
	}
}