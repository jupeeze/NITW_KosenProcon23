#pragma once

#include <array>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using namespace std;

struct Point {
	int row;
	int col;
};

enum class Cell {
	EMPTY,
	PLAYER1,
	PLAYER2,
	PLAYER1_WALL,
	PLAYER2_WALL,
	PLAYER_BASE,
	PLAYER_MARK,
	CASTLE_MARK,
	POND,
	CASTLE,
};

class Board {
   public:
	static const int ROWS = 11;
	static const int COLS = 11;
	static const int PLAYER_NUM = 2;
	static const int WORKER_NUM = 2;

	static Cell m_board[ROWS][COLS];
	static Cell new_board[ROWS][COLS];

	map<Cell, array<Point, WORKER_NUM>> seed_worker;
	const array<Cell, PLAYER_NUM> PLAYERS = {Cell::PLAYER1, Cell::PLAYER2};

	Board();

	void Spawn();
	void Count(Cell player);
	void PrintBoard() const;
	void PlacePiece(Cell cell, int row, int col);
	void ScanLineSeedFill(Point seed, Cell player);
	void CallScanLineSeedFill(Cell player);
	vector<int> GetLegalMoves(array<Point, WORKER_NUM> seeds);

	static bool IsOccupied(int row, int col);

	Cell GetPlayerWall(Cell player) const;

	vector<pair<int, int>> GetEmptyCells() const;
	void SortWorker();

   private:
	map<Cell, int> count_closed;

	void CopyBoard();
	bool CouldFillCell(Point p);
};
