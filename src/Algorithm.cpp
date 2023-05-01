#pragma once
#include <stdbool.h>

#include "Move.cpp"
#include "square.h"

#define SIZE 11
#define WorkerNum 2

extern Square Stage[SIZE][SIZE];
extern int Worker[2][WorkerNum];

bool CanMove(int y, int x, int value) {
	if (Stage[y][x] != value) return false;
	if (!IsNotException(y, x, Stage[y][x])) return false;
	return true;
}

void Algo(int playerNum) {
	int value = 0;
	for (int num = 0; num < WorkerNum; num++) {
		int x = Worker[playerNum][num] % SIZE;
		int y = Worker[playerNum][num] / SIZE;

		// Build
		if (CanMove(y - 1, x, 0))
			value = 22;
		else if (CanMove(y, x - 1, 0))
			value = 24;
		else if (CanMove(y, x + 1, 0))
			value = 26;
		else if (CanMove(y + 1, x, 0))
			value = 28;

		// Move
		else if (CanMove(y - 1, x - 1, 0))
			value = 11;
		else if (CanMove(y - 1, x, 0))
			value = 12;
		else if (CanMove(y - 1, x + 1, 0))
			value = 13;
		else if (CanMove(y, x - 1, 0))
			value = 14;
		else if (CanMove(y, x + 1, 0))
			value = 16;
		else if (CanMove(y + 1, x - 1, 0))
			value = 17;
		else if (CanMove(y + 1, x, 0))
			value = 18;
		else if (CanMove(y + 1, x + 1, 0))
			value = 19;

		// Crash
		else if (CanMove(y - 1, x - 1, 4 - playerNum))
			value = 32;
		else if (CanMove(y - 1, x + 1, 4 - playerNum))
			value = 34;
		else if (CanMove(y + 1, x - 1, 4 - playerNum))
			value = 36;
		else if (CanMove(y + 1, x + 1, 4 - playerNum))
			value = 38;

		printf("%d ", value);
		Move(value, playerNum, num);
	}
}
