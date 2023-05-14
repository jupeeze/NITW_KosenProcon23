#include "minimax_player.hpp"

#include <climits>

using namespace std;

constexpr array<pair<Pattern, Point>, 4> Player::patterns = {{
	{Pattern::PLACE, {-1, +0}},
	{Pattern::PLACE, {+0, -1}},
	{Pattern::PLACE, {+0, +1}},
	{Pattern::PLACE, {+1, +0}},
	//  {Pattern::MOVE, {-1, -1}},
	//  {Pattern::MOVE, {-1, +0}},
	//  {Pattern::MOVE, {-1, +1}},
	//  {Pattern::MOVE, {+0, -1}},
	//  {Pattern::MOVE, {+0, +0}},
	//  {Pattern::MOVE, {+0, +1}},
	//  {Pattern::MOVE, {+1, -1}},
	//  {Pattern::MOVE, {+1, +0}},
	//  {Pattern::MOVE, {+1, +1}},
	//  {Pattern::CRASH, {-1, +0}},
	//  {Pattern::CRASH, {+0, -1}},
	//  {Pattern::CRASH, {+0, +1}},
	//  {Pattern::CRASH, {+1, +0}}
}};

MinimaxPlayer::MinimaxPlayer(Cell player)
	: m_player(player),
	  m_players{Player({0, 0}, m_player), Player({0, 0}, m_player)} {}

void MinimaxPlayer::MakeMove(Board board) const {
	int bestValue = INT_MIN;
	int alpha = INT_MIN;
	int beta = INT_MAX;
	pair<Pattern, Point> bestPattern1, bestPattern2;

	for (auto pattern1 : Player::patterns) {
		Board newBoard(board);
		m_players[0].Work(pattern1, newBoard);
		for (auto pattern2 : Player::patterns) {
			m_players[1].Work(pattern2, newBoard);
			int value = Minimax(MAX_DEPTH - 1, newBoard, false, alpha, beta);
			if (value > bestValue) {
				bestValue = value;
				bestPattern1 = pattern1;
				bestPattern2 = pattern2;
			}
			alpha = max(alpha, bestValue);
			if (beta <= alpha) break;
		}
	}

	m_players[0].Work(bestPattern1, board);
	m_players[1].Work(bestPattern2, board);
}

int Evaluate() { return 0; }

int MinimaxPlayer::Minimax(int depth, Board board, bool maxflag, int alpha,
						   int beta) const {
	if (depth <= 0) return Evaluate();

	if (maxflag) {
		int bestValue = INT_MIN;
		for (auto pattern1 : Player::patterns) {
			Board newBoard(board);
			m_players[0].Work(pattern1, newBoard);
			for (auto pattern2 : Player::patterns) {
				m_players[1].Work(pattern2, newBoard);
				int value = Minimax(depth - 1, newBoard, false, alpha, beta);
				bestValue = max(bestValue, value);
				alpha = max(alpha, bestValue);
				if (beta <= alpha) break;
			}
		}
		return bestValue;
	} else {
		int bestValue = INT_MAX;
		for (auto pattern1 : Player::patterns) {
			Board newBoard(board);
			m_players[0].Work(pattern1, newBoard);
			for (auto pattern2 : Player::patterns) {
				m_players[1].Work(pattern2, newBoard);
				int value = Minimax(depth - 1, board, true, alpha, beta);
				bestValue = min(bestValue, value);
				beta = min(beta, bestValue);
				if (beta <= alpha) break;
			}
		}
		return bestValue;
	}
}
