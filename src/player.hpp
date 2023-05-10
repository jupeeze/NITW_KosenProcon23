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
	static constexpr array<pair<Pattern, Point>, 17> patterns = {
		{{Pattern::MOVE, {-1, -1}},
		 {Pattern::MOVE, {-1, +0}},
		 {Pattern::MOVE, {-1, +1}},
		 {Pattern::MOVE, {+0, -1}},
		 {Pattern::MOVE, {+0, +0}},
		 {Pattern::MOVE, {+0, +1}},
		 {Pattern::MOVE, {+1, -1}},
		 {Pattern::MOVE, {+1, +0}},
		 {Pattern::MOVE, {+1, +1}},
		 {Pattern::PLACE, {-1, +0}},
		 {Pattern::PLACE, {+0, -1}},
		 {Pattern::PLACE, {+0, +1}},
		 {Pattern::PLACE, {+1, +0}},
		 {Pattern::CRASH, {-1, +0}},
		 {Pattern::CRASH, {+0, -1}},
		 {Pattern::CRASH, {+0, +1}},
		 {Pattern::CRASH, {+1, +0}}}};

	void Move();
	void Place();
	void Crash();
	void Work(pair<Pattern, Point> pattern, Board board);

   private:
	Cell m_player;
	Point m_player_seed;
	Cell GetOpponent() const;
	pair<Pattern, Point> GetLegalMoves();
};
