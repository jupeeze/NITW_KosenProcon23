#pragma once

#include <array>
#include <iomanip>
#include <ios>
#include <utility>

#include "board.hpp"

using namespace std;

enum Pattern {
	NONE,
	MOVE,
	PLACE,
	CRASH,
};

class Player {
   public:
	Cell m_player;
	mutable Point m_player_seed;

	Player(Point seed, Cell player);

	static const array<pair<Pattern, Point>, 4> patterns;

	void Work(pair<Pattern, Point> pattern, Board& board) const;
	void SpawnPlayer(Cell cell, Player& player, Board& board);
	vector<pair<Pattern, Point>> GetLegalMoves(Board board) const;
	static void SortWorker(array<Player, Board::WORKER_NUM> players);

   private:
	Cell GetOpponent() const;
};
