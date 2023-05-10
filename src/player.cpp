#include "player.hpp"

#include <cstdlib>
#include <ctime>

using namespace std;

void Player::Work(pair<Pattern, Point> pattern, Board board) {
	switch (pattern.first) {
		case Pattern::NONE:
			break;
		case Pattern::MOVE:
			board.m_board[m_player_seed.row][m_player_seed.col] = Cell::EMPTY;

			int row = m_player_seed.row + pattern.second.row;
			int col = m_player_seed.col + pattern.second.col;

			m_player_seed = {row, col};
			board.m_board[row][col] = m_player;
		case Pattern::PLACE:
			int row = m_player_seed.row + pattern.second.row;
			int col = m_player_seed.col + pattern.second.col;

			Cell wall = board.GetPlayerWall(m_player);
			board.PlacePiece(wall, row, col);
		case Pattern::CRASH:
			int row = m_player_seed.row + pattern.second.row;
			int col = m_player_seed.col + pattern.second.col;

			board.PlacePiece(Cell::EMPTY, row, col);
	}
}

Cell Player::GetOpponent() const {
	return (m_player == Cell::PLAYER1) ? Cell::PLAYER2 : Cell::PLAYER1;
}
