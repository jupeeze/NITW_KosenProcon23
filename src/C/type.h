#ifndef TYPE_H
#define TYPE_H

typedef enum { pEmpty, pMove, pBuild, pCrash } Pattern;

typedef enum {
	EMPTY = 0,
	PLAYER1 = 1,
	PLAYER2 = 2,
	PLAYER1_WALL = 3,
	PLAYER2_WALL = 4,
	PLAYER_BASE = 5,
	PLAYER_MARK = 6,
	CASTLE_MARK = 7,
	POND = 8,
	CASTLE = 9,
} Square;

#endif
