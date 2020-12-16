#pragma once

#include "game_board.h"

struct BoardPos
{
	BoardPos();
	BoardPos(uint8_t col, uint8_t row);

	uint8_t col, row;
};

struct AIPlayer
{
	AIPlayer();
	AIPlayer(Cell::State);

	const BoardPos decideMove(BoardState) const;
	void  setSign(Cell::State);

private:
	Cell::State aiSign;
};