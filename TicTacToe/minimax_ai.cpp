#include <algorithm>
#include "ai.h"

BoardPos::BoardPos() : BoardPos(0, 0) {}
BoardPos::BoardPos(uint8_t row, uint8_t cell) : row(row), cell(cell) {}

AIPlayer::AIPlayer()                 : AIPlayer(Cell::State::X) {}
AIPlayer::AIPlayer(Cell::State sign) : aiSign(sign) {}

static int minimax(BoardState state, int depth, Cell::State perspective, bool maximizing)
{
	Cell::State opponent = Cell::oppositeOf(perspective);
	int eval = state.evaluate(perspective);

	if (!state.movesLeft())
		return state.NEUTRAL;

	if (eval == state.WIN)
		if (maximizing)
			return eval - depth;
		else
			return eval + depth;
	else if (eval == state.LOSS)
		return eval;

	int bestScore = maximizing ? INT_MIN : INT_MAX;

	for (uint8_t row = 0; row < 3; row++)
		for (uint8_t cell = 0; cell < 3; cell++)
			if (Cell::isBlank(state(row, cell)))
			{
				if (maximizing)
				{
					state(row, cell) = perspective;
					bestScore = std::max(bestScore, minimax(state, depth + 1, perspective, !maximizing));
				}
				else
				{
					state(row, cell) = opponent;
					bestScore = std::min(bestScore, minimax(state, depth + 1, perspective, !maximizing));
				}

				state(row, cell) = Cell::State::BLANK;
			}

	return bestScore;
}

const BoardPos AIPlayer::decideMove(BoardState board) const
{
	BoardPos out;
	int bestMoveScore = INT_MIN;

	for (uint8_t row = 0; row < 3; row++)
		for (uint8_t cell = 0; cell < 3; cell++)
			if (Cell::isBlank(board(row, cell)))
			{
				board(row, cell) = aiSign;

				int moveScore = minimax(board, 0, aiSign, false);

				board(row, cell) = Cell::State::BLANK;

				if (moveScore > bestMoveScore)
				{
					out.row = row;
					out.cell = cell;
					bestMoveScore = moveScore;
				}
			}

	return out;
}

void AIPlayer::setSign(Cell::State sign)
{
	aiSign = sign;
}