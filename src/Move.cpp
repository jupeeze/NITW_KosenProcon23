#pragma once
#include <stdbool.h>
#include <stdio.h>

#include "type.h"

#define SIZE 11
#define WorkerNum 2

extern Square Stage[SIZE][SIZE];
extern int Worker[2][WorkerNum];

bool IsNotException(int y, int x, int value) {
	if (y < 0 || y >= SIZE) return false;
	if (x < 0 || x >= SIZE) return false;

	Stage[y][x] = static_cast<Square>(value);
	return true;
}

bool Move(int value, int playerNum, int num) {
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
					Stage[y - 1][x] = EMPTY;
					break;
				case 4:
					Stage[y][x - 1] = EMPTY;
					break;
				case 6:
					Stage[y][x + 1] = EMPTY;
					break;
				case 8:
					Stage[y + 1][x] = EMPTY;
					break;
			}
			break;
	}
	return true;
}
