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

	Player(Point seed);

	static const array<pair<Pattern, Point>, 17> patterns;

	void Move();
	void Place();
	void Crash();
	void Work(pair<Pattern, Point> pattern, Board board) const;
	void SpawnPlayer(Cell cell, Player& player);

   private:
	Cell GetOpponent() const;
	pair<Pattern, Point> GetLegalMoves();
};
