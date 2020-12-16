#include "board_state.h"

const int8_t BoardState::NEUTRAL = 0, BoardState::WIN = 10, BoardState::LOSS = -10;

BoardState::BoardState(Cell* const cells[3][3])
{
	for (uint8_t col = 0; col < 3; col++)
		for (uint8_t row = 0; row < 3; row++)
			state[col][row] = *cells[col][row];
}

Cell::State& BoardState::operator()(uint8_t col, uint8_t row)
{
	return state[col][row];
}

const Cell::State& BoardState::operator()(uint8_t col, uint8_t row) const
{
	return state[col][row];
}

template<typename T>
static constexpr bool allEqual(T first, T second, T third)
{
	return (first == second) && (second == third);
}

int BoardState::evaluate(Cell::State perspective) const
{
	const BoardState& board = *this;

	// rows
	for (uint8_t col = 0; col < 3; col++)
		if (allEqual(board(col, 0), board(col, 1), board(col, 2)) && !Cell::isBlank(board(col, 0)))
			return (board(col, 0) == perspective) ? WIN : LOSS;

	// cols
	for (uint8_t row = 0; row < 3; row++)
		if ((board(0, row) == board(1, row)) && (board(1, row) == board(2, row)) && !Cell::isBlank(board(0, row)))
			return (board(0, row) == perspective) ? WIN : LOSS;

	// diags
	bool diag1 = allEqual(board(0, 0), board(1, 1), board(2, 2));
	bool diag2 = allEqual(board(2, 0), board(1, 1), board(0, 2));
	if ((diag1 || diag2) && !Cell::isBlank(board(1, 1)))
		return (board(1, 1) == perspective) ? WIN : LOSS;

	return NEUTRAL;
}

bool BoardState::moves_left() const
{
	for (uint8_t col = 0; col < 3; col++)
		for (uint8_t row = 0; row < 3; row++)
			if (Cell::isBlank(state[col][row]))
				return true;
	return false;
}