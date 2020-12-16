#include "board_state.h"

template<typename T>
static constexpr bool allEqual(T first, T second, T third);

const int8_t BoardState::NEUTRAL = 0, BoardState::WIN = 1, BoardState::LOSS = -1;

BoardState::BoardState(Cell* const cells[3][3])
{
	for (uint8_t row = 0; row < 3; row++)
		for (uint8_t cell = 0; cell < 3; cell++)
			state[row][cell] = *cells[row][cell];
}

BoardState BoardState::of(Cell* const cells[3][3])
{
	return BoardState(cells);
}

Cell::State& BoardState::operator()(uint8_t row, uint8_t cell)
{
	return state[row][cell];
}

const Cell::State& BoardState::operator()(uint8_t row, uint8_t cell) const
{
	return state[row][cell];
}

int BoardState::evaluate(Cell::State perspective) const
{
	const BoardState& board = *this;

	// cols
	for (uint8_t row = 0; row < 3; row++)
		if (allEqual(board(row, 0), board(row, 1), board(row, 2)) && !Cell::isBlank(board(row, 0)))
			return (board(row, 0) == perspective) ? WIN : LOSS;

	// rows
	for (uint8_t cell = 0; cell < 3; cell++)
		if (allEqual(board(0, cell), board(1, cell), board(2, cell)) && !Cell::isBlank(board(0, cell)))
			return (board(0, cell) == perspective) ? WIN : LOSS;

	// diags
	bool diag1 = allEqual(board(0, 0), board(1, 1), board(2, 2));
	bool diag2 = allEqual(board(2, 0), board(1, 1), board(0, 2));
	if ((diag1 || diag2) && !Cell::isBlank(board(1, 1)))
		return (board(1, 1) == perspective) ? WIN : LOSS;

	return NEUTRAL;
}

template<typename T>
constexpr bool allEqual(T first, T second, T third)
{
	return (first == second) && (second == third);
}

bool BoardState::movesLeft() const
{
	for (uint8_t row = 0; row < 3; row++)
		for (uint8_t cell = 0; cell < 3; cell++)
			if (Cell::isBlank(state[row][cell]))
				return true;
	return false;
}