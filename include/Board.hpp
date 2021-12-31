#include <Bitboard.hpp>
#include <string>

class Board {
	int side; // 0 for white, 1 for black
	Bitboard pawns[2];
	Bitboard rooks[2];
	Bitboard knights[2];
	Bitboard bishops[2];
	Bitboard queens[2];
	Bitboard kings[2];
	Bitboard all[2];
	Bitboard allPieces;

	bool castling[2][2];

	std::string enPassantSquare;

	int movesFifty;
	int fullMoves;

public:
	Board();

	std::string getFen();
};