#pragma once
#include <stdbool.h>

#include <algorithm>
#include <climits>

#include "type.h"

#define SIZE 11
#define WorkerNum 2

using namespace std;

typedef array<array<Square, SIZE>, SIZE> ArraySq11x11;

Square StageCopy[SIZE][SIZE] = {EMPTY};
int patterns[] = {11, 12, 13, 14, 16, 17, 18, 19,
				  22, 24, 26, 28, 32, 34, 36, 38};

extern Square Stage[SIZE][SIZE];
extern int Worker[2][WorkerNum];

ArraySq11x11 GetUpdatedStage(int pattern, ArraySq11x11 Stage) {
	copy(&Stage[0][0], &Stage[0][0] + (SIZE * SIZE), &StageCopy[0][0]);

	Move(pattern, )
}

bool IsNotException(int y, int x, int value) {
	if (y < 0 || y >= SIZE) return false;
	if (x < 0 || x >= SIZE) return false;

	StageCopy[y][x] = static_cast<Square>(value);
	return true;
}

bool Move(int value, int playerNum, int num, ArraySq11x11 Stage) {
	int mass = value % 10;
	Pattern pattern = static_cast<Pattern>(value / 10);

	int x = Worker[playerNum][num] % SIZE;
	int y = Worker[playerNum][num] / SIZE;

	switch (pattern) {
		case pMove:
			switch (mass) {
				case 1:
				case 2:
				case 3:
					if (IsNotException(y - 1, x + (mass - 2), playerNum + 1)) {
						Stage[y][x] = EMPTY;
						Worker[playerNum][num] -= SIZE - (mass - 2);
					} else {
						return false;
					}
					break;
				case 4:
				case 6:
					if (IsNotException(y, x + (mass - 5), playerNum + 1)) {
						Stage[y][x] = EMPTY;
						Worker[playerNum][num] += mass - 5;
					} else {
						return false;
					}
					break;
				case 7:
				case 8:
				case 9:
					if (IsNotException(y + 1, x + (mass - 8), playerNum + 1)) {
						Stage[y][x] = EMPTY;
						Worker[playerNum][num] += SIZE + (mass - 8);
					} else {
						return false;
					}
					break;
			}
			break;
		case pBuild:
			switch (mass) {
				case 2:
					if (!IsNotException(y - 1, x, playerNum + 3)) {
						return false;
					}
					break;
				case 4:
					if (!IsNotException(y, x - 1, playerNum + 3)) {
						return false;
					}
					break;
				case 6:
					if (!IsNotException(y, x + 1, playerNum + 3)) {
						return false;
					}
					break;
				case 8:
					if (!IsNotException(y + 1, x, playerNum + 3)) {
						return false;
					}
					break;
			}
			break;
		case pCrash:
			switch (mass) {
				case 2:
					StageCopy[y - 1][x] = EMPTY;
					break;
				case 4:
					StageCopy[y][x - 1] = EMPTY;
					break;
				case 6:
					StageCopy[y][x + 1] = EMPTY;
					break;
				case 8:
					StageCopy[y + 1][x] = EMPTY;
					break;
			}
			break;
	}
	return true;
}

int Evaluate(ArraySq11x11 Stage) {}

// アルファベータ法を使用した探索
int AlphaBeta(int depth, bool player, ArraySq11x11 Stage, int alpha, int beta) {
	// 終端ノードに到達した場合、評価関数を呼び出して評価値を返す
	if (depth == 0) return Evaluate(Stage);

	if (player) {
		int bestValue = INT_MIN;
		for (int pattern : patterns) {
			int value = AlphaBeta(depth - 1, false, pattern, alpha, beta);
			bestValue = max(bestValue, value);
			alpha = max(alpha, bestValue);
			if (beta <= alpha) break;
		}
		return bestValue;
	} else {
		int bestValue = INT_MAX;
		for (int pattern : patterns) {
			int value = AlphaBeta(depth - 1, true, pattern, alpha, beta);
			bestValue = min(bestValue, value);
			beta = min(beta, bestValue);
			if (beta <= alpha) break;
		}
		return bestValue;
	}
}

// ルートノードを呼び出すための関数
int callAlphaBeta(int depth) {
	std::array<std::array<Square, SIZE>, SIZE> square_array;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			square_array[i][j] = Stage[i][j];
		}
	}

	return AlphaBeta(depth, true, square_array, INT_MIN, INT_MAX);
}

void Algo(int playerNum) { callAlphaBeta(8); }
