#include "board.hpp"

namespace board {

	Board::Board() : m_Board(new block::BlockComponent**[HEIGHT])
	{
		for (int i = 0; i < HEIGHT; i++) {
			this->m_Board[i] = new block::BlockComponent * [WIDTH];
			for (int j = 0; j < WIDTH; j++)
				this->m_Board[i][j] = new block::BlockComponent(i, j, maths::vec4(0,0,0,0));
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

	void Board::placeBlock(const block::Block& block) const
	{
		for (int i = 0; i < block::Block::getNumberComponents(); ++i) {
			this->m_Board[block.getPositionAt(i).get_y_pos()][block.getPositionAt(i).get_x_pos()]->setActive(true);
			this->m_Board[block.getPositionAt(i).get_y_pos()][block.getPositionAt(i).get_x_pos()]->setColor(block.getColorFromType());
		}
	}

	void Board::moveBlock(const block::Block& block, direction::Direction direction) const
	{
		switch (direction)
		{
		case direction::Direction::LEFT:
			for (int i = 0; i < block::Block::getNumberComponents(); ++i)
				this->m_Board[block.getPositionAt(i).get_y_pos()][block.getPositionAt(i).get_x_pos() + 1]->setActive(false);
			break;
		case direction::Direction::RIGHT:
			for (int i = 0; i < block::Block::getNumberComponents(); ++i)
				this->m_Board[block.getPositionAt(i).get_y_pos()][block.getPositionAt(i).get_x_pos() - 1]->setActive(false);
			break;
		case direction::Direction::DOWN:
			for (int i = 0; i < block::Block::getNumberComponents(); ++i)
				this->m_Board[block.getPositionAt(i).get_y_pos() - 1][block.getPositionAt(i).get_x_pos()]->setActive(false);
			break;
		case direction::Direction::UP:
			break;
		}
		this->placeBlock(block);
	}

	void Board::lineVerification(const block::Block& block, int &score) const
	{
		int number = 0;
		int goal = block.getMinHeight();
		for (int i = block.getMaxHeight(); i >= goal; --i) {
			bool verification = true;
			for (int j = 0; j < Board::WIDTH; ++j)
				verification = verification && this->m_Board[i][j]->isActive();
			if (verification) {
				for (int j = 0; j < Board::WIDTH; ++j)
					this->m_Board[i][j]->setActive(false);
				for (int j = i; j > 0; --j) {
					for (int k = 0;  k < Board::WIDTH; ++k) {
						this->m_Board[j][k]->setActive(this->m_Board[j - 1][k]->isActive());
						this->m_Board[j][k]->setColor(this->m_Board[j - 1][k]->getColor());
					}
				}
				++i;
				++goal;
				++number;
			}
		}
		score += number;
	}
}