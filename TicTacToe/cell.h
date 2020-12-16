#pragma once

#include <iostream>

struct Cell
{
	Cell();
	Cell(uint8_t, uint8_t);

	enum class State { BLANK, X, O };
	static State oppositeOf(State);
	static bool isBlank(State);

	operator State()            const;
	void     operator=(State);
	void     draw()             const;

private:
	static const char* const X[3];
	static const char* const O[3];

	uint8_t homeX, homeY;
	State currentState;
};