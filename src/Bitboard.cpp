#include <Bitboard.hpp>
#include <stdexcept>

Bitboard::Bitboard(uint64_t bitboard) {
	this->bitboard = bitboard;
}

uint64_t Bitboard::getBB() {
	return this->bitboard;
}

bool Bitboard::get(int file, int rank) {
	int square = this->checkAndGetSquare(file, rank);
	return static_cast<bool>(this->bitboard & ((uint64_t)1 << square));
}

void Bitboard::set(int file, int rank, bool value) {
	int square = this->checkAndGetSquare(file, rank);

	if (value) {
		this->bitboard = this->bitboard | (1 << square);
	}
	else {
		this->bitboard = this->bitboard & ~(1 << square);
	}
}

int Bitboard::checkAndGetSquare(int file, int rank) {
	if (!( (0 <= file && file <= 63) && (0 <= rank && rank <= 63) )) {
		throw std::invalid_argument("Indices value must be between 0 and 63");
	}

	return 8 * rank + file;
}