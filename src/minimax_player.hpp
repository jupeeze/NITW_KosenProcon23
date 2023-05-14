#pragma once

#include "board.hpp"
#include "player.hpp"

class MinimaxPlayer {
   public:
	Cell m_player;
	array<Player, Board::WORKER_NUM> m_players;

	MinimaxPlayer(Cell player);
	void MakeMove(Board board) const;

   private:
	static const int MAX_DEPTH = 5;
	int Minimax(int depth, Board board, bool maxflag, int alpha,
				int beta) const;
};
