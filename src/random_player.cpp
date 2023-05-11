#include "random_player.hpp"

#include <cstdlib>
#include <ctime>

using namespace std;

RandomPlayer::RandomPlayer(Cell player)
	: m_player(player), m_players({Player({0, 0}), Player({0, 0})}) {}

void RandomPlayer::MakeMove(Board &board) const {
	vector<pair<int, int>> emptyCells = board.GetEmptyCells();

	int randomIndex = rand() % emptyCells.size();

	pair<int, int> randomCell = emptyCells[randomIndex];
	board.PlacePiece(m_player, randomCell.first, randomCell.second);
}
