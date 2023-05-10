#pragma once

#include "board.hpp"

class RandomPlayer {
   public:
	RandomPlayer(Cell player);
	void MakeMove(Board &board) const;

   private:
	Cell m_player;
	array<Player, Board::WORKER_NUM> m_players;
};
