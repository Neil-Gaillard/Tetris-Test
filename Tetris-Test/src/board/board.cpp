#include "board.hpp"

namespace board {

	Board::Board()
	{
		this->m_Board = new block::BlockComponant**[HEIGHT];
		for (int i = 0; i < HEIGHT; i++) {
			this->m_Board[i] = new block::BlockComponant * [WIDTH];
			for (int j = 0; j < WIDTH; j++)
				this->m_Board[i][j] = new block::BlockComponant(i, j);
		}
	}

	Board::~Board()
	{
		for (int i = 0; i < HEIGHT; ++i) {
			for (int j = 0; j < WIDTH; ++j)
				delete this->m_Board[i][j];
			delete[] this->m_Board[i];
 		}
		delete[] this->m_Board;
	}

	std::ostream& operator<<(std::ostream& stream, const Board& board)
	{
		for (int i = 0; i < board.HEIGHT; ++i) {
			for (int j = 0; j < board.WIDTH; ++j)
				stream << *(board.m_Board[i][j]);
			stream << std::endl;
		}
		return stream;
	}
}