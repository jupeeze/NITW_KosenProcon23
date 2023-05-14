#include "player.hpp"

#include <cstdlib>
#include <ctime>

using namespace std;

Player::Player(Point seed, Cell player)
	: m_player_seed(seed), m_player(player) {}

bool IsInRange(int row, int col) {
	if (row < 0 || row >= Board::ROWS) return false;
	if (col < 0 || col >= Board::COLS) return false;
	return true;
}

void Player::Work(pair<Pattern, Point> pattern, Board& board) const {
	Cell wall;
	int row = m_player_seed.row + pattern.second.row;
	int col = m_player_seed.col + pattern.second.col;
	if (!IsInRange(row, col)) return;

	switch (pattern.first) {
		case Pattern::NONE:
			break;
		case Pattern::MOVE:
			board.m_board[m_player_seed.row][m_player_seed.col] = Cell::EMPTY;

			m_player_seed = {row, col};
			board.m_board[row][col] = m_player;
			break;
		case Pattern::PLACE:
			wall = board.GetPlayerWall(m_player);
			board.PlacePiece(wall, row, col);
			break;
		case Pattern::CRASH:
			wall = Cell::EMPTY;
			board.PlacePiece(wall, row, col);
			break;
	}
}

void Player::SpawnPlayer(Cell cell, Player& player) {
	while (true) {
		int row = rand() % Board::ROWS;
		int col = rand() % Board::COLS;
		if (Board::m_board[row][col] == Cell::EMPTY) {
			Board::m_board[row][col] = cell;
			player.m_player_seed = {row, col};
			break;
		}
		cout << "seed Row:" << player.m_player_seed.row + 1 << endl;
		cout << "seed Col:" << player.m_player_seed.col + 1 << endl;
	}
}

Cell Player::GetOpponent() const {
	return (m_player == Cell::PLAYER1) ? Cell::PLAYER2 : Cell::PLAYER1;
}
