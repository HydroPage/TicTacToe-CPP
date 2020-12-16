#pragma once

#include <stdint.h>
#include "board_state.h"

struct Board
{
	Board(uint8_t homeY, uint8_t homeX);
	~Board();

	Cell& operator()(uint8_t col, uint8_t row) const;

	const BoardState getState() const;

	void clear() const;
	void draw()  const;

private:
	uint8_t homeY, homeX;
	Cell* cells[3][3];
};