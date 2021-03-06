#include <Board.hpp>
#include <string>

Board::Board() {
	this->side = 0;

	this->pawns[0] = Bitboard((uint64_t)0x000000000000FF00);
	this->pawns[1] = Bitboard((uint64_t)0x00FF000000000000);

	this->kings[0] = Bitboard((uint64_t)1 << 4);
	this->kings[1] = Bitboard((uint64_t)1 << 60);

	this->queens[0] = Bitboard((uint64_t)1 << 3);
	this->queens[1] = Bitboard((uint64_t)1 << 59);

	this->rooks[0] = Bitboard(((uint64_t)1 << 0) | ((uint64_t)1 << 7));
	this->rooks[1] = Bitboard(((uint64_t)1 << 63) | ((uint64_t)1 << 56));

	this->knights[0] = Bitboard(((uint64_t)1 << 1) | ((uint64_t)1 << 6));
	this->knights[1] = Bitboard(((uint64_t)1 << 62) | ((uint64_t)1 << 57));

	this->bishops[0] = Bitboard(((uint64_t)1 << 2) | ((uint64_t)1 << 5));
	this->bishops[1] = Bitboard(((uint64_t)1 << 61) | ((uint64_t)1 << 58));

	this->all[0] = rooks[0] | knights[0] | bishops[0] | queens[0] | kings[0] | pawns[0];
	this->all[1] = rooks[1] | knights[1] | bishops[1] | queens[1] | kings[1] | pawns[1];

	this->allPieces = Bitboard(all[0].getBB() | all[1].getBB());

	this->castling[0][0] = true;
	this->castling[0][1] = true;
	this->castling[1][0] = true;
	this->castling[1][1] = true;

	this->enPassantSquare = "-";

	this->movesFifty = 0;
	this->fullMoves = 1;
}

std::string Board::getFen() {
	std::string fen = "";
	// iterating overs indexes (decreasing)
	for (int rank = 7; rank >= 0; rank--) {
		// iterating overs rows
		int empty = 0;
		for (int file = 0; file < 8; file++) {
			bool squareOccupied = this->allPieces.get(file, rank);
			if (!squareOccupied) {
				empty++;
				if (file == 7) {
					fen += std::to_string(empty);
				}
			}
			else if (empty != 0) {
				fen += std::to_string(empty);
			}
			else {
				// rooks
				if (this->rooks[0].get(file, rank)) {
					fen += "R";
				}
				if (this->rooks[1].get(file, rank)) {
					fen += "r";
				}
				
				// knights
				if (this->knights[0].get(file, rank)) {
					fen += "N";
				}
				if (this->knights[1].get(file, rank)) {
					fen += "n";
				}

				// bishops
				if (this->bishops[0].get(file, rank)) {
					fen += "B";
				}
				if (this->bishops[1].get(file, rank)) {
					fen += "b";
				}

				// kings
				if (this->kings[0].get(file, rank)) {
					fen += "K";
				}
				if (this->kings[1].get(file, rank)) {
					fen += "k";
				}

				// queens
				if (this->queens[0].get(file, rank)) {
					fen += "Q";
				}
				if (this->queens[1].get(file, rank)) {
					fen += "q";
				}

				// pawns
				if (this->pawns[0].get(file, rank)) {
					fen += "P";
				}
				if (this->pawns[1].get(file, rank)) {
					fen += "p";
				}
			}
		}

		if (rank != 0) fen += "/";
	}

	// Side who has the turn
	if (this->side == 0) {
		fen += " w";
	}
	else {
		fen += " b";
	}

	// Castling rights
	bool canCastle = false;
	std::string castlingRights = " ";
	if (this->castling[0][0]) {
		castlingRights += "K";
		canCastle = true;
	}
	if (this->castling[0][1]) {
		castlingRights += "Q";
		canCastle = true;
	}
	if (this->castling[1][0]) {
		castlingRights += "k";
		canCastle = true;
	}
	if (this->castling[1][0]) {
		castlingRights += "q";
		canCastle = true;
	}
	if (canCastle) {
		fen += castlingRights;
	}

	// Last move
	fen += " ";
	fen += this->enPassantSquare;

	// Number of half-moves for the 50 moves rules
	fen += " " + std::to_string(this->movesFifty);

	// Number of full moves (incremented each time
	// Black moves)
	fen += " " + std::to_string(this->fullMoves);

	return fen;
}