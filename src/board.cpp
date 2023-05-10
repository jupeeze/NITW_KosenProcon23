#include "board.hpp"

#include <iomanip>
#include <ios>

using namespace std;

Board::Board() {
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
			m_board[row][col] = Cell::EMPTY;
		}
	}
}

void Board::Spawn() {
	int row, col;

	while (true) {
		row = rand() % ROWS;
		col = rand() % COLS;
		if (m_board[row][col] == Cell::EMPTY) {
			m_board[row][col] = Cell::POND;
			break;
		}
	}

	while (true) {
		row = rand() % ROWS;
		col = rand() % COLS;
		if (m_board[row][col] == Cell::EMPTY) {
			m_board[row][col] = Cell::CASTLE;
			break;
		}
	}

	for (Cell player : PLAYERS) {
		for (int i = 0; i < WORKER_NUM; i++) {
			while (true) {
				row = rand() % ROWS;
				col = rand() % COLS;
				if (m_board[row][col] == Cell::EMPTY) {
					m_board[row][col] = player;
					seed_worker[player][i] = {row, col};

					break;
				}
			}
		}
	}
}

void Board::PrintBoard() const {
	cout << endl;
	cout << "  | 1 2 3 4 5 6 7 8 9 0 1 " << endl;
	cout << "--+---------------------- " << endl;

	for (int row = 0; row < ROWS; row++) {
		cout << setw(2) << row + 1 << "| ";
		for (int col = 0; col < COLS; col++) {
			switch (m_board[row][col]) {
				case Cell::EMPTY:
					cout << "\x1b[49m･ ";
					break;
				case Cell::PLAYER1:
					cout << "\x1b[41m# ";
					break;
				case Cell::PLAYER2:
					cout << "\x1b[44m# ";
					break;
				case Cell::PLAYER1_WALL:
					cout << "\x1b[41m･ ";
					break;
				case Cell::PLAYER2_WALL:
					cout << "\x1b[44m･ ";
					break;
				case Cell::POND:
					cout << "\x1b[46m･ ";
					break;
				case Cell::CASTLE:
					cout << "\x1b[47m･ ";
					break;
			}
		}
		cout << "\x1b[0m" << endl;
	}
	cout << "\x1b[0m" << endl;

	cout << "field1: " << count_closed.at(Cell::PLAYER1) << endl;
	cout << "field2: " << count_closed.at(Cell::PLAYER2) << endl;
}

void Board::PlacePiece(Cell cell, int row, int col) {
	m_board[row][col] = cell;
}

void Board::CopyBoard() {
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
			new_board[row][col] = m_board[row][col];
		}
	}
}

void Board::Count(Cell player) {
	count_closed[player] = 0;
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
			if (new_board[row][col] == Cell::EMPTY)
				count_closed[player]++;
			else if (new_board[row][col] == player)
				count_closed[player]++;
			else if (new_board[row][col] == Cell::CASTLE)
				count_closed[player] += 10;
		}
	}
}

bool Board::CouldFillCell(Point p) {
	switch (new_board[p.row][p.col]) {
		case Cell::EMPTY:
			new_board[p.row][p.col] = Cell::PLAYER_BASE;
			return true;
		case Cell::PLAYER1:
		case Cell::PLAYER2:
			new_board[p.row][p.col] = Cell::PLAYER_MARK;
			return true;
		case Cell::CASTLE:
			new_board[p.row][p.col] = Cell::CASTLE_MARK;
			return true;
		default:
			return false;
	}
}

void Board::ScanLineSeedFill(Point seed, Cell player) {
	Cell player_wall = GetPlayerWall(player);

	vector<Point> stack;
	stack.push_back(seed);

	int dx[4] = {1, 0, -1, 0};
	int dy[4] = {0, 1, 0, -1};

	while (!stack.empty()) {
		Point p = stack.back();
		stack.pop_back();

		if (p.col < 0 || p.col >= COLS || p.row < 0 || p.row >= ROWS) continue;

		if (!CouldFillCell(p)) continue;

		for (int i = 0; i < 4; i++) {
			Point neighbor = {p.col + dx[i], p.row + dy[i]};
			stack.push_back(neighbor);
		}
	}
}

void Board::CallScanLineSeedFill(Cell player) {
	CopyBoard();
	for (int row = 0; row < ROWS; row++) {
		ScanLineSeedFill({row, 0}, player);
	}
	for (int col = 0; col < COLS; col++) {
		ScanLineSeedFill({0, col}, player);
	}
	for (int row = 0; row < ROWS; row++) {
		ScanLineSeedFill({row, COLS - 1}, player);
	}
	for (int col = 0; col < COLS; col++) {
		ScanLineSeedFill({ROWS - 1, col}, player);
	}
}

bool Board::IsOccupied(int row, int col) {
	return (m_board[row][col] != Cell::EMPTY);
}

Cell Board::GetPlayerWall(Cell player) const {
	switch (player) {
		case Cell::PLAYER1:
			return Cell::PLAYER1_WALL;
			break;
		case Cell::PLAYER2:
			return Cell::PLAYER2_WALL;
			break;
		default:
			return Cell::EMPTY;
			break;
	}
}

vector<pair<int, int>> Board::GetEmptyCells() const {
	vector<pair<int, int>> emptyCells;
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
			if (m_board[row][col] == Cell::EMPTY) {
				emptyCells.emplace_back(row, col);
			}
		}
	}
	return emptyCells;
}

// void Board::SortWorker() {
// 	for (int i = 0; i < WORKER_NUM; i++)
// 		for (int j = i + 1; j < WORKER_NUM; j++)
// 			if (seed_worker[m_player][i].row > seed_worker[m_player][j].row)
// 				swap(seed_worker[m_player][i], seed_worker[m_player][j]);
// }
