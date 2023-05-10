#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Algorithm.cpp"
#include "Move.cpp"
#include "type.h"

#define SIZE 11
#define WorkerNum 2

int isUsedCom = false;
int playerNowNum = 0;
int fieldNum[2] = {0};
int Worker[2][WorkerNum] = {0};

Square Stage[SIZE][SIZE] = {EMPTY};
Square StageCopy[SIZE][SIZE] = {EMPTY};

bool checkWinner() { return true; }

void Count(void) {
	fieldNum[playerNowNum] = 0;
	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			if (StageCopy[y][x] == EMPTY)
				fieldNum[playerNowNum]++;
			else if (StageCopy[y][x] == playerNowNum + 1)
				fieldNum[playerNowNum]++;
			else if (StageCopy[y][x] == CASTLE)
				fieldNum[playerNowNum] += 10;
		}
	}
}

void OutputStage() {
	printf("\n");
	printf("  | 1 2 3 4 5 6 7 8 9 0 1 \n");
	printf("--+---------------------- \n");
	for (int y = 0; y < SIZE; y++) {
		printf("%2d| ", y + 1);
		for (int x = 0; x < SIZE; x++) {
			switch (Stage[y][x]) {
				case EMPTY:
					printf("\x1b[49m･ ");
					break;
				case PLAYER1:
					printf("\x1b[41m# ");
					break;
				case PLAYER2:
					printf("\x1b[44m# ");
					break;
				case PLAYER1_WALL:
					printf("\x1b[41m･ ");
					break;
				case PLAYER2_WALL:
					printf("\x1b[44m･ ");
					break;
				case POND:
					printf("\x1b[46m･ ");
					break;
				case CASTLE:
					printf("\x1b[47m･ ");
					break;
				default:
					printf("%d ", Stage[y][x]);
					break;
			}
		}
		printf("\x1b[0m\n");
	}
	printf("\n");

	printf("field1: %d\n\n", fieldNum[0]);
	printf("field2: %d\n\n", fieldNum[1]);
}

void Spawn() {
	int x, y;

	while (true) {
		x = rand() % SIZE;
		y = rand() % SIZE;
		if (Stage[y][x] == EMPTY) {
			Stage[y][x] = POND;
			break;
		}
	}

	while (true) {
		x = rand() % SIZE;
		y = rand() % SIZE;
		if (Stage[y][x] == EMPTY) {
			Stage[y][x] = CASTLE;
			break;
		}
	}

	// shokunin
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < WorkerNum; j++) {
			while (true) {
				x = rand() % SIZE;
				y = rand() % SIZE;
				if (Stage[y][x] == EMPTY) {
					Square playerNum = (i == 0) ? PLAYER1 : PLAYER2;
					Stage[y][x] = playerNum;
					Worker[i][j] = y * SIZE + x;
					break;
				}
			}
		}
	}
}

bool CheckEmpty(int i, int j) {
	if (StageCopy[i][j] == EMPTY) {
		StageCopy[i][j] = PLAYER_BASE;
		return true;
	} else if (StageCopy[i][j] == PLAYER1 || StageCopy[i][j] == PLAYER2) {
		StageCopy[i][j] = PLAYER_MARK;
		return true;
	} else if (StageCopy[i][j] == CASTLE) {
		StageCopy[i][j] = CASTLE_MARK;
		return true;
	}
	return false;
}

void CheckSell(int i, int j) {
	if (CheckEmpty(i, j)) {
		if (j - 1 >= 0) CheckSell(i, j - 1);	// left
		if (j + 1 < SIZE) CheckSell(i, j + 1);	// right
		if (i - 1 >= 0) CheckSell(i - 1, j);	// up
		if (i + 1 < SIZE) CheckSell(i + 1, j);	// down
	}
}

void Loop(void) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			StageCopy[i][j] = Stage[i][j];
		}
	}

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (StageCopy[i][j] == playerNowNum + 3) break;
			CheckSell(i, j);
		}
	}
	for (int i = 0; i < SIZE; i++) {
		for (int j = SIZE - 1; j >= 0; j--) {
			if (StageCopy[i][j] == playerNowNum + 3) break;
			CheckSell(i, j);
		}
	}
	for (int j = 0; j < SIZE; j++) {
		for (int i = 0; i < SIZE; i++) {
			if (StageCopy[i][j] == playerNowNum + 3) break;
			CheckSell(i, j);
		}
	}
	for (int j = 0; j < SIZE; j++) {
		for (int i = SIZE - 1; i >= 0; i--) {
			if (StageCopy[i][j] == playerNowNum + 3) break;
			CheckSell(i, j);
		}
	}
}

void Work(int playerNum) {
	for (int i = 0; i < WorkerNum; i++) {
		int action;
		int x = Worker[playerNum][i] % SIZE;
		int y = Worker[playerNum][i] / SIZE;
		printf("Player%d worker%d x=%d y=%d \n", playerNum + 1, i + 1, x + 1,
			   y + 1);
		printf("1:stay 2:move 3:build 4:crash \n");
		scanf("%d", &action);
		switch (action) {
			int mass;
			case 2:
				printf("123\n456\n789\n");
				scanf("%d", &mass);
				if (!Move(10 + mass, playerNum, i)) i--;
				break;
			case 3:
				printf(" 1 \n2 3\n 4 \n");
				scanf("%d", &mass);
				if (!Move(20 + mass, playerNum, i)) i--;
				break;
			case 4:
				printf(" 1 \n2 3\n 4 \n");
				scanf("%d", &mass);
				if (!Move(30 + mass, playerNum, i)) i--;
				break;
		}
	}
}

void SortWorker(void) {
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < WorkerNum; j++)
			for (int k = j + 1; k < WorkerNum; k++)
				if (Worker[i][j] > Worker[i][k]) {
					int tmp = Worker[i][j];
					Worker[i][j] = Worker[i][k];
					Worker[i][k] = tmp;
				}
}

int main(void) {
	srand(time(NULL));

	Spawn();
	SortWorker();

	Count();
	OutputStage();

	char strUsedCom;
	printf("Use Computer? (y/n)：");
	scanf("%c", &strUsedCom);
	if (strUsedCom == 'y') isUsedCom = true;

	int countPlay = 0;
	const int countPlayMax = 100;
	while (countPlay < countPlayMax) {
		countPlay++;

		// Work(0);
		Algo(0);

		if (isUsedCom)
			Algo(1);
		else
			Work(1);

		playerNowNum = 0;
		Loop();
		Count();

		playerNowNum = 1;
		Loop();
		Count();

		OutputStage();
		SortWorker();
	}

	return 0;
}
