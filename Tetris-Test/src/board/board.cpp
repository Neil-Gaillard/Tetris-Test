#include "board.hpp"

namespace board {

	Board::Board()
	{
		this->m_Board = new block::BlockComponant**[HEIGHT];
		for (int i = 0; i < HEIGHT; i++) {
			this->m_Board[i] = new block::BlockComponant * [WIDTH];
			for (int j = 0; j < WIDTH; j++)
				this->m_Board[i][j] = new block::BlockComponant(i, j, maths::vec4(0,0,0,0));
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
			this->m_Board[block.getPositionAt(i).getYPos()][block.getPositionAt(i).getXPos()]->setActive(true);
			this->m_Board[block.getPositionAt(i).getYPos()][block.getPositionAt(i).getXPos()]->setColor(block.getColorFromType());
		}
	}

	void Board::moveBlock(const block::Block& block, direction::Direction direction)
	{
		switch (direction)
		{
		case direction::Direction::LEFT:
			for (int i = 0; i < block::Block::getNumberComponants(); ++i)
				this->m_Board[block.getPositionAt(i).getYPos()][block.getPositionAt(i).getXPos() + 1]->setActive(false);
			break;
		case direction::Direction::RIGHT:
			for (int i = 0; i < block::Block::getNumberComponants(); ++i)
				this->m_Board[block.getPositionAt(i).getYPos()][block.getPositionAt(i).getXPos() - 1]->setActive(false);
			break;
		case direction::Direction::DOWN:
			for (int i = 0; i < block::Block::getNumberComponants(); ++i)
				this->m_Board[block.getPositionAt(i).getYPos() - 1][block.getPositionAt(i).getXPos()]->setActive(false);
			break;
		case direction::Direction::UP:
			break;
		}
		this->placeBlock(block);
	}

	void Board::verifLine(const block::Block& block)
	{

	}

#if 0
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
#endif
}