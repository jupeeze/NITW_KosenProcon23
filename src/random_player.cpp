#include "random_player.hpp"

#include <cstdlib>
#include <ctime>

using namespace std;

RandomPlayer::RandomPlayer(Cell player)
	: m_player(player),
	  m_players{Player({0, 0}, m_player), Player({0, 0}, m_player)} {}

void RandomPlayer::MakeMove(Board &board) const {
	int randomIndex = rand() % Player::patterns.size();
	m_players[0].Work(Player::patterns[randomIndex], board);
	randomIndex = rand() % Player::patterns.size();
	m_players[1].Work(Player::patterns[randomIndex], board);
}
