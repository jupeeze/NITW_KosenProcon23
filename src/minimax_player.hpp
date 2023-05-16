#pragma once

#include "board.hpp"
#include "player.hpp"
#include "random_player.hpp"

class MinimaxPlayer {
   public:
	Cell m_player;
	RandomPlayer* m_opponent;
	array<Player, Board::WORKER_NUM> m_players;

	MinimaxPlayer(Cell player, RandomPlayer* opponent);
	void MakeMove(Board& board) const;

   private:
	static const int MAX_DEPTH = 5;
	int Evaluate(Board board) const;
	int Minimax(int depth, Board board, bool maxflag, int alpha,
				int beta) const;
};
