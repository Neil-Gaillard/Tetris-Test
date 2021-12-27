#include "block.hpp"
#include "../utils/utils.hpp"

#include <algorithm>
#include <random>

namespace block {
	Block::Block(const BlockType blockType) : m_BlockType(blockType)
	{
		this->defineComponants();
	}

	bool Block::moveBlock(const direction::Direction direction, const board::Board* board)
	{
		switch (direction)
		{
		case direction::Direction::LEFT:
			if (this->m_MinWidth - 1 < 0)
				return false;
			for (int i = 0; i < NUMBER_COMPONANTS; ++i)
				if (!(std::find(this->m_BlockPos.begin(), this->m_BlockPos.end(), this->m_BlockPos.at(i) - maths::Position(1, 0)) != this->m_BlockPos.end())
					&& board->getBlockComponant(this->m_BlockPos.at(i).getXPos() - 1, this->m_BlockPos.at(i).getYPos())->isActive())
					return false;
			for (int i = 0; i < this->NUMBER_COMPONANTS; ++i)
				this->m_BlockPos.at(i) -= maths::Position(1, 0);
			--this->m_MinWidth;
			--this->m_MaxWidth;
			return true;
		case direction::Direction::RIGHT:
			if (this->m_MaxWidth + 1 >= board::Board::WIDTH)
				return false;
			for (int i = 0; i < NUMBER_COMPONANTS; ++i)
				if (!(std::find(this->m_BlockPos.begin(), this->m_BlockPos.end(), this->m_BlockPos.at(i) + maths::Position(1, 0)) != this->m_BlockPos.end())
					&& board->getBlockComponant(this->m_BlockPos.at(i).getXPos() + 1, this->m_BlockPos.at(i).getYPos())->isActive())
					return false;
			for (int i = 0; i < this->NUMBER_COMPONANTS; ++i)
				this->m_BlockPos.at(i) += maths::Position(1, 0);
			++this->m_MaxWidth;
			++this->m_MinWidth;
			return true;
		case direction::Direction::DOWN:
			if (this->m_MaxHeight + 1 >= board::Board::HEIGHT)
				return false;
			for (int i = 0; i < NUMBER_COMPONANTS; ++i)
				if (!(std::find(this->m_BlockPos.begin(), this->m_BlockPos.end(), this->m_BlockPos.at(i) + maths::Position(0, 1)) != this->m_BlockPos.end())
					&& board->getBlockComponant(this->m_BlockPos.at(i).getXPos(), this->m_BlockPos.at(i).getYPos() + 1)->isActive())
						return false;
			for (int i = 0; i < this->NUMBER_COMPONANTS; ++i)
				this->m_BlockPos.at(i) += maths::Position(0, 1);
			++this->m_MaxHeight;
			++this->m_MinHeight;
			return true;
		}
		return false;
	}

	bool Block::rotateBlock(direction::Direction direction, const board::Board* board)
	{
		// x2 = cos(45) * x1 - sin(45)*y1
		// y2 = sin(45) * x1 + cos(45)*y1
	}

	void Block::defineComponants()
	{
		switch (this->m_BlockType)
		{
		case BlockType::I:
			this->defineIBlock();
			return;
		case BlockType::J:
			this->defineJBlock();
			return;
		case BlockType::L:
			this->defineLBlock();
			return;
		case BlockType::O:
			this->defineOBlock();
			return;
		case BlockType::S:
			this->defineSBlock();
			return;
		case BlockType::T:
			this->defineTBlock();
			return;
		case BlockType::Z:
			this->defineZBlock();
			return;
		default:
			throw;
		}
	}

	void Block::defineTBlock()
	{
		this->m_BlockPos.push_back(maths::Position(0, 0));
		this->m_BlockPos.push_back(maths::Position(1, 0));
		this->m_BlockPos.push_back(maths::Position(2, 0));
		this->m_BlockPos.push_back(maths::Position(1, 1));

		this->m_MinWidth = 0;
		this->m_MaxWidth = 2;
		this->m_MinHeight = 0;
		this->m_MaxHeight = 1;

	}

	void Block::defineIBlock()
	{
		this->m_BlockPos.push_back(maths::Position(0, 0));
		this->m_BlockPos.push_back(maths::Position(1, 0));
		this->m_BlockPos.push_back(maths::Position(2, 0));
		this->m_BlockPos.push_back(maths::Position(3, 0));

		this->m_MinWidth = 0;
		this->m_MaxWidth = 3;
		this->m_MinHeight = 0;
		this->m_MaxHeight = 0;
	}

	void Block::defineJBlock()
	{
		this->m_BlockPos.push_back(maths::Position(0, 0));
		this->m_BlockPos.push_back(maths::Position(1, 0));
		this->m_BlockPos.push_back(maths::Position(1, 1));
		this->m_BlockPos.push_back(maths::Position(1, 2));

		this->m_MinWidth = 0;
		this->m_MaxWidth = 1;
		this->m_MinHeight = 0;
		this->m_MaxHeight = 2;
	}

	void Block::defineLBlock()
	{
		this->m_BlockPos.push_back(maths::Position(0, 0));
		this->m_BlockPos.push_back(maths::Position(0, 1));
		this->m_BlockPos.push_back(maths::Position(0, 2));
		this->m_BlockPos.push_back(maths::Position(1, 0));

		this->m_MinWidth = 0;
		this->m_MaxWidth = 1;
		this->m_MinHeight = 0;
		this->m_MaxHeight = 2;
	}

	void Block::defineOBlock()
	{
		this->m_BlockPos.push_back(maths::Position(0, 0));
		this->m_BlockPos.push_back(maths::Position(1, 0));
		this->m_BlockPos.push_back(maths::Position(0, 1));
		this->m_BlockPos.push_back(maths::Position(1, 1));

		this->m_MinWidth = 0;
		this->m_MaxWidth = 1;
		this->m_MinHeight = 0;
		this->m_MaxHeight = 1;
	}

	void Block::defineSBlock()
	{
		this->m_BlockPos.push_back(maths::Position(0, 0));
		this->m_BlockPos.push_back(maths::Position(1, 0));
		this->m_BlockPos.push_back(maths::Position(1, 1));
		this->m_BlockPos.push_back(maths::Position(2, 1));

		this->m_MinWidth = 0;
		this->m_MaxWidth = 2;
		this->m_MinHeight = 0;
		this->m_MaxHeight = 1;
	}

	void Block::defineZBlock()
	{
		this->m_BlockPos.push_back(maths::Position(0, 1));
		this->m_BlockPos.push_back(maths::Position(1, 1));
		this->m_BlockPos.push_back(maths::Position(1, 0));
		this->m_BlockPos.push_back(maths::Position(2, 0));

		this->m_MinWidth = 0;
		this->m_MaxWidth = 2;
		this->m_MinHeight = 0;
		this->m_MaxHeight = 1;
	}

	Block* Block::instantiateRandomBlock()
	{
		int var = rand() % BLOCK_TYPE_NUMBER;
		switch (var)
		{
		case 0:
			return new Block(BlockType::I);
		case 1:
			return new Block(BlockType::J);
		case 2:
			return new Block(BlockType::L);
		case 3:
			return new Block(BlockType::O);
		case 4:
			return new Block(BlockType::S);
		case 5:
			return new Block(BlockType::T);
		case 6:
			return new Block(BlockType::Z);
		default:
			throw;
		}
	}
}