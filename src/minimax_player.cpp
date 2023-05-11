#include "minimax_player.hpp"

#include <climits>

constexpr array<pair<Pattern, Point>, 17> Player::patterns = {
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
;

using namespace std;

MinimaxPlayer::MinimaxPlayer(Cell player)
	: m_player(player), m_players({Player({0, 0}), Player({0, 0})}) {}

void MinimaxPlayer::MakeMove(Board& board) const {
	vector<pair<int, int>> emptyCells = board.GetEmptyCells();
	vector<int> scores(emptyCells.size());

	for (size_t i = 0; i < emptyCells.size(); ++i) {
		Board newBoard(board);
		newBoard.PlacePiece(m_player, emptyCells[i].first,
							emptyCells[i].second);
		scores[i] = Minimax(MAX_DEPTH, board, true, INT_MIN, INT_MAX);
	}

	int maxScoreIndex = 0;
	int maxScore = INT_MIN;
	for (size_t i = 0; i < scores.size(); ++i) {
		if (scores[i] > maxScore) {
			maxScore = scores[i];
			maxScoreIndex = i;
		}
	}

	board.PlacePiece(m_player, emptyCells[maxScoreIndex].first,
					 emptyCells[maxScoreIndex].second);
}

int Evaluate() { return 0; }

int MinimaxPlayer::Minimax(int depth, Board& board, bool maxflag, int alpha,
						   int beta) const {
	if (depth <= 0) return Evaluate();

	if (maxflag) {
		int bestValue = INT_MIN;
		for (auto pattern : Player::patterns) {
			Board newBoard(board);
			m_players[0].Work(pattern, newBoard);
			for (auto move : Player::patterns) {
				m_players[1].Work(pattern, newBoard);
				int value = Minimax(depth - 1, newBoard, false, alpha, beta);
				bestValue = max(bestValue, value);
				alpha = max(alpha, bestValue);
				if (beta <= alpha) break;
			}
		}
		return bestValue;
	} else {
		int bestValue = INT_MAX;
		for (auto pattern : Player::patterns) {
			Board newBoard(board);
			m_players[0].Work(pattern, newBoard);
			for (auto move : Player::patterns) {
				m_players[1].Work(pattern, newBoard);
				int value = Minimax(depth - 1, board, true, alpha, beta);
				bestValue = min(bestValue, value);
				beta = min(beta, bestValue);
				if (beta <= alpha) break;
			}
		}
		return bestValue;
	}
}
