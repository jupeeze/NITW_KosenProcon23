#include "player.hpp"

#include <cstdlib>
#include <ctime>

using namespace std;

Player::Player(Point seed) : m_player_seed(seed) {}

void Player::Work(pair<Pattern, Point> pattern, Board& board) const {
	int row, col;
	switch (pattern.first) {
		case Pattern::NONE:
			break;
		case Pattern::MOVE:
			board.m_board[m_player_seed.row][m_player_seed.col] = Cell::EMPTY;

			row = m_player_seed.row + pattern.second.row;
			col = m_player_seed.col + pattern.second.col;

			m_player_seed = {row, col};
			board.m_board[row][col] = m_player;
			break;
		case Pattern::PLACE:
			row = m_player_seed.row + pattern.second.row;
			col = m_player_seed.col + pattern.second.col;

			Cell wall = board.GetPlayerWall(m_player);
			board.PlacePiece(wall, row, col);
			break;
		case Pattern::CRASH:
			row = m_player_seed.row + pattern.second.row;
			col = m_player_seed.col + pattern.second.col;

			board.PlacePiece(Cell::EMPTY, row, col);
			break;
	}
}

Cell Player::GetOpponent() const {
	return (m_player == Cell::PLAYER1) ? Cell::PLAYER2 : Cell::PLAYER1;
}
