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

	void Board::placeBlock(const block::Block& block)
	{
		for (int i = 0; i < block::Block::getNumberComponants(); ++i) {
			maths::Position tmpPos = block.getPositionAtIndex(i);
			this->m_Board[tmpPos.getYPos()][tmpPos.getXPos()]->setActive(true);
		}
	}

	void Board::moveBlock(const block::Block& block, direction::Direction direction)
	{
		switch (direction)
		{
		case direction::Direction::LEFT:
			for (int i = 0; i < block::Block::getNumberComponants(); ++i) {
				maths::Position tmpPos = block.getPositionAtIndex(i);
				this->m_Board[tmpPos.getYPos()][tmpPos.getXPos() + 1]->setActive(false);
			}
			this->placeBlock(block);
			return;
		case direction::Direction::RIGHT:
			for (int i = 0; i < block::Block::getNumberComponants(); ++i) {
				maths::Position tmpPos = block.getPositionAtIndex(i);
				this->m_Board[tmpPos.getYPos()][tmpPos.getXPos() - 1]->setActive(false);
			}
			this->placeBlock(block);
			return;
		case direction::Direction::DOWN:
			for (int i = 0; i < block::Block::getNumberComponants(); ++i) {
				maths::Position tmpPos = block.getPositionAtIndex(i);
				this->m_Board[tmpPos.getYPos() - 1][tmpPos.getXPos()]->setActive(false);
			}
			this->placeBlock(block);
			return;
		default:
			throw;
		}
	}

	std::ostream& operator<<(std::ostream& stream, const Board& board)
	{
		for (int i = 0; i < board.HEIGHT; ++i) {
			for (int j = 0; j < board.WIDTH; ++j)
				stream << "|" << *(board.m_Board[i][j]);
			stream << "|" << std::endl;
			for (int j = 0; j <= board.WIDTH*2; ++j)
				stream << "-";
			stream << std::endl;
		}
		return stream;
	}
}