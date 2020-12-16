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
	const TextBox *textWarn, *textMain, *textBottom;

	std::string input(const char* const) const;
	Cell::State player_select()          const;
};