#pragma once

#include "game_utils.h"
#include "game_board.h"
#include "text.h"
#include "ai.h"

struct TicTacToe
{
	TicTacToe();
	~TicTacToe();

	void loop();

private:
	AIPlayer computer;
	const Board* board;
	const TextBox *textMain, *textBottom;
	const WarnBox *textWarn;

	bool checkGameOver() const;
	const BoardPos selectPos() const;
	const Cell::State playerSelect() const;
	const std::string input(const char* const) const;
};