#include "board.hpp"

#include <iomanip>
#include <ios>

using namespace std;

const array<Cell, Board::PLAYER_NUM> PLAYERS = {Cell::PLAYER1, Cell::PLAYER2};

Board::Board() {
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
			m_board[row][col] = Cell::EMPTY;
		}
	}
}

bool Board::IsInRange(int row, int col) const {
	if (row < 0 || row >= Board::ROWS) return false;
	if (col < 0 || col >= Board::COLS) return false;
	return true;
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
}

void Board::PrintBoard(Cell board[Board::ROWS][Board::COLS]) const {
	cout << endl;
	cout << "  | 1 2 3 4 5 6 7 8 9 0 1 " << endl;
	cout << "--+---------------------- " << endl;

	for (int row = 0; row < ROWS; row++) {
		cout << setw(2) << row + 1 << "| ";
		for (int col = 0; col < COLS; col++) {
			if (board[row][col] == Cell::EMPTY)
				cout << "  ";
			else
				cout << static_cast<int>(board[row][col]) << " ";
			// switch (board[row][col]) {
			// 	case Cell::EMPTY:
			// 		cout << "\x1b[49m･ ";
			// 		break;
			// 	case Cell::PLAYER1:
			// 		cout << "\x1b[41m# ";
			// 		break;
			// 	case Cell::PLAYER2:
			// 		cout << "\x1b[44m# ";
			// 		break;
			// 	case Cell::PLAYER1_WALL:
			// 		cout << "\x1b[41m･ ";
			// 		break;
			// 	case Cell::PLAYER2_WALL:
			// 		cout << "\x1b[44m･ ";
			// 		break;
			// 	case Cell::POND:
			// 		cout << "\x1b[46m･ ";
			// 		break;
			// 	case Cell::CASTLE:
			// 		cout << "\x1b[47m･ ";
			// 		break;
			// }
		}
		cout << "" << endl;
	}
	cout << "" << endl;
}

void Board::PlacePiece(Cell cell, int row, int col) {
	m_board[row][col] = cell;
}

void Board::CopyBoard(Cell board[Board::ROWS][Board::COLS]) {
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
			board[row][col] = m_board[row][col];
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

bool Board::CouldFillCell(Point p, Cell player) {
	switch (new_board[p.row][p.col]) {
		case Cell::EMPTY:
			new_board[p.row][p.col] = Cell::PLAYER_BASE;
			break;
		case Cell::PLAYER1:
		case Cell::PLAYER2:
			new_board[p.row][p.col] = Cell::PLAYER_MARK;
			break;
		case Cell::CASTLE:
			new_board[p.row][p.col] = Cell::CASTLE_MARK;
			break;
		default:
			return false;
	}
	return true;
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

		if (!CouldFillCell(p, player)) continue;

		for (int i = 0; i < 4; i++) {
			Point neighbor = {p.col + dx[i], p.row + dy[i]};
			stack.push_back(neighbor);
		}
	}
}

void Board::CallScanLineSeedFill(Cell player) {
	CopyBoard(new_board);
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

void Board::ScanAllFill(Point p, Cell player) {
	int dx[4] = {1, 0, -1, 0};
	int dy[4] = {0, 1, 0, -1};

	if (CouldFillCell(p, player)) {
		for (int i = 0; i < 4; i++) {
			Point seed = {p.row + dx[i], p.col + dy[i]};
			if (!IsInRange(seed.row, seed.col)) continue;
			ScanAllFill(seed, player);
		}
	}
}

void Board::CallScanAllFill(Cell player) {
	CopyBoard(new_board);
	for (int row = 0; row < Board::ROWS; row++) {
		for (int col = 0; col < Board::COLS; col++) {
			if (new_board[row][col] == GetPlayerWall(player)) break;
			ScanAllFill({row, col}, player);
		}
	}
	for (int row = 0; row < Board::ROWS; row++) {
		for (int col = Board::COLS - 1; col >= 0; col--) {
			if (new_board[row][col] == GetPlayerWall(player)) break;
			ScanAllFill({row, col}, player);
		}
	}
	for (int col = 0; col < Board::COLS; col++) {
		for (int row = 0; row < Board::ROWS; row++) {
			if (new_board[row][col] == GetPlayerWall(player)) break;
			ScanAllFill({row, col}, player);
		}
	}
	for (int col = 0; col < Board::COLS; col++) {
		for (int row = Board::ROWS - 1; row >= 0; row--) {
			if (new_board[row][col] == GetPlayerWall(player)) break;
			ScanAllFill({row, col}, player);
		}
	}
}

Cell GetOpponent(Cell player) {
	return (player == Cell::PLAYER1) ? Cell::PLAYER2 : Cell::PLAYER1;
}
