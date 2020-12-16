#pragma once

#include "game_board.h"

struct BoardPos
{
	BoardPos();
	BoardPos(uint8_t row, uint8_t cell);

	uint8_t row, cell;
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