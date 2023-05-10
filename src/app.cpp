#include "board.cpp"
#include "minimax_player.cpp"
#include "random_player.cpp"

using namespace std;

int main() {
	srand(time(NULL));

	Board board;
	MinimaxPlayer minimaxPlayer(Cell::PLAYER1);
	RandomPlayer randomPlayer(Cell::PLAYER2);

	board.Spawn();
	board.PrintBoard();

	// SortWorker();

	int countPlay = 0;
	const int countPlayMax = 100;
	while (countPlay < countPlayMax) {
		countPlay++;

		minimaxPlayer.MakeMove(board);
		randomPlayer.MakeMove(board);

		board.CallScanLineSeedFill(Cell::PLAYER1);
		board.Count(Cell::PLAYER1);

		board.CallScanLineSeedFill(Cell::PLAYER2);
		board.Count(Cell::PLAYER2);

		board.PrintBoard();

		// SortWorker();
	}

	return 0;
}
