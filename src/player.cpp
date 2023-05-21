#include "player.hpp"

#include <cstdlib>
#include <ctime>

using namespace std;

Player::Player(Point seed, Cell player)
	: m_player_seed(seed), m_player(player) {}

void Player::Work(pair<Pattern, Point> pattern, Board& board) const {
	Cell wall;
	int row = m_player_seed.row + pattern.second.row;
	int col = m_player_seed.col + pattern.second.col;
	if (!board.IsInRange(row, col)) return;

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

void Player::SpawnPlayer(Cell cell, Player& player, Board& board) {
	while (true) {
		int row = rand() % Board::ROWS;
		int col = rand() % Board::COLS;
		if (board.m_board[row][col] == Cell::EMPTY) {
			board.m_board[row][col] = cell;
			player.m_player_seed = {row, col};
			break;
		}
		cout << "seed Row:" << player.m_player_seed.row + 1 << endl;
		cout << "seed Col:" << player.m_player_seed.col + 1 << endl;
	}
}

vector<pair<Pattern, Point>> Player::GetLegalMoves(Board board) const {
	vector<pair<Pattern, Point>> moves;
	int delta[] = {-1, 0, 1};
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if ((row == 0 && col == 1) ||
				(row == 1 && (col == 0 || col == 2)) ||
				(row == 2 && col == 1)) {
				if (board.m_board[m_player_seed.row + delta[row]]
								 [m_player_seed.col + delta[col]] ==
					Cell::EMPTY) {
					moves.push_back(
						{Pattern::PLACE, Point{delta[row], delta[col]}});
				}
				if (board.m_board[m_player_seed.row + delta[row]]
								 [m_player_seed.col + delta[col]] ==
						Cell::PLAYER1_WALL ||
					board.m_board[m_player_seed.row + delta[row]]
								 [m_player_seed.col + delta[col]] ==
						Cell::PLAYER2_WALL) {
					moves.push_back(
						{Pattern::CRASH, Point{delta[row], delta[col]}});
				}
			}
			if (board.m_board[m_player_seed.row + delta[row]]
							 [m_player_seed.col + delta[col]] == Cell::EMPTY) {
				moves.push_back({Pattern::MOVE, Point{delta[row], delta[col]}});
			}
		}
	}
	return moves;
}

void Player::SortWorker(array<Player, Board::WORKER_NUM> players) {
	for (int i = 0; i < Board::WORKER_NUM; i++)
		for (int j = i + 1; j < Board::WORKER_NUM; j++)
			if (players[i].m_player_seed.row > players[j].m_player_seed.row)
				swap(players[i], players[j]);
}

Cell Player::GetOpponent() const {
	return (m_player == Cell::PLAYER1) ? Cell::PLAYER2 : Cell::PLAYER1;
}
