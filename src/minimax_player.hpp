#pragma once

#include "board.hpp"
#include "player.hpp"

class MinimaxPlayer {
   public:
	MinimaxPlayer(Cell player);
	void MakeMove(Board& board) const;

   private:
	static const int MAX_DEPTH = 10;
	Cell m_player;
	array<Player, Board::WORKER_NUM> m_players;
	int Minimax(int depth, Board& board, bool maxflag, int alpha,
				int beta) const;
};
