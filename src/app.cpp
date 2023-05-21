#include "board.cpp"
#include "minimax_player.cpp"
#include "player.cpp"
#include "random_player.cpp"

using namespace std;

int main(void) {
	srand(time(NULL));

	Board board;
	board.Spawn();

	RandomPlayer randomPlayer(Cell::PLAYER2);
	for (Player& player : randomPlayer.m_players)
		player.SpawnPlayer(randomPlayer.m_player, player, board);
	MinimaxPlayer minimaxPlayer(Cell::PLAYER1, &randomPlayer);
	for (Player& player : minimaxPlayer.m_players)
		player.SpawnPlayer(minimaxPlayer.m_player, player, board);

	board.PrintBoard(board.m_board);
	// Player::SortWorker(randomPlayer.m_players);
	// Player::SortWorker(minimaxPlayer.m_players);

	int countPlay = 0;
	const int countPlayMax = 5;
	while (countPlay < countPlayMax) {
		countPlay++;

		minimaxPlayer.MakeMove(board);
		randomPlayer.MakeMove(board);

		board.CallScanLineSeedFill(Cell::PLAYER1);
		board.Count(Cell::PLAYER1);

		board.CallScanLineSeedFill(Cell::PLAYER2);
		board.Count(Cell::PLAYER2);

		board.PrintBoard(board.m_board);
	}

	return 0;
}
