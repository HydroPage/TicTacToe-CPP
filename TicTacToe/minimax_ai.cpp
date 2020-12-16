#include <algorithm>
#include "ai.h"

BoardPos::BoardPos() : BoardPos(0, 0) {}
BoardPos::BoardPos(uint8_t col, uint8_t row) : col(col), row(row) {}

AIPlayer::AIPlayer()                 : AIPlayer(Cell::State::X) {}
AIPlayer::AIPlayer(Cell::State sign) : aiSign(sign) {}

static int minimax(BoardState state, int depth, Cell::State perspective, bool maximizing)
{
	Cell::State opponent = Cell::oppositeOf(perspective);
	int eval = state.evaluate(perspective);

	if (!state.moves_left())
		return state.NEUTRAL;

	if (eval == state.WIN || eval == state.LOSS)
		return eval;

	int best_score = maximizing ? INT_MIN : INT_MAX;

	for (uint8_t col = 0; col < 3; col++)
		for (uint8_t row = 0; row < 3; row++)
			if (Cell::isBlank(state(col, row)))
			{
				if (maximizing)
				{
					state(col, row) = perspective;
					best_score = std::max(best_score, minimax(state, depth + 1, perspective, !maximizing));
				}
				else
				{
					state(col, row) = opponent;
					best_score = std::min(best_score, minimax(state, depth + 1, perspective, !maximizing));
				}

				state(col, row) = Cell::State::BLANK;
			}

	return best_score;
}

const BoardPos AIPlayer::decideMove(BoardState board) const
{
	BoardPos out;
	int bestMoveScore = INT_MIN;

	for (uint8_t col = 0; col < 3; col++)
		for (uint8_t row = 0; row < 3; row++)
			if (Cell::isBlank(board(col, row)))
			{
				board(col, row) = aiSign;

				int moveScore = minimax(board, 0, aiSign, false);

				board(col, row) = Cell::State::BLANK;

				if (moveScore > bestMoveScore)
				{
					out.col = col;
					out.row = row;
					bestMoveScore = moveScore;
				}
			}

	out.col += 1;
	out.row += 1;

	return out;
}

void AIPlayer::setSign(Cell::State sign)
{
	aiSign = sign;
}