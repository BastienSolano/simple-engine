#include <Bitboard.hpp>

class Board {
	int side; // 0 for white, 1 for black
	Bitboard pawns[2];
	Bitboard rooks[2];
	Bitboard knights[2];
	Bitboard bishops[2];
	Bitboard queens[2];
	Bitboard kings[2];

public:
	/*
	* Some redundant information for easier computations
	*/
	enum enumPieces {
		nWhite, // all white pieces
		nBlack, // all black pieces
		nWhitePawn, // all white pawns
		nBlackPawn // all black pawns
	};
};