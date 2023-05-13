#pragma once

#include "board.hpp"

class RandomPlayer {
   public:
	Cell m_player;
	array<Player, Board::WORKER_NUM> m_players;

	RandomPlayer(Cell player);
	void MakeMove(Board &board) const;

   private:
};
