#pragma once

#include "cell.h"

struct BoardState
{
	static const int8_t NEUTRAL, WIN, LOSS;

	BoardState(Cell* const [3][3]);

	Cell::State& operator()(uint8_t col, uint8_t row);
	const Cell::State& operator()(uint8_t col, uint8_t row) const;

	int evaluate(Cell::State perspective) const;
	bool moves_left() const;

private:
	Cell::State state[3][3];
};