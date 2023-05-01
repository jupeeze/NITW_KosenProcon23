#ifndef SQUARE_H
#define SQUARE_H

typedef enum {
	EMPTY = 0,
	PLAYER1 = 1,
	PLAYER2 = 2,
	PLAYER1_WALL = 3,
	PLAYER2_WALL = 4,
	PLAYER_BASE = 5,
	CASTLE_BASE = 6,
	POND = 7,
	CASTLE = 8,
} Square;

#endif
