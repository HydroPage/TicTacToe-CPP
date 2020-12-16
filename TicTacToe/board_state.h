#pragma once

#include "cell.h"

struct BoardState
{
	static const int8_t NEUTRAL, WIN, LOSS;

	static BoardState of(Cell* const [3][3]);

	Cell::State& operator()(uint8_t row, uint8_t cell);
	const Cell::State& operator()(uint8_t row, uint8_t cell) const;

	int evaluate(Cell::State perspective) const;
	bool movesLeft() const;

private:
	BoardState(Cell* const [3][3]);

	Cell::State state[3][3];
};