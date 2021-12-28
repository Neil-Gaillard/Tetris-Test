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
	 
	bool Block::rotateBlock(const board::Board* board)
	{
		maths::Position tmpNewPos[4] =
		{
			this->m_BlockPos.at(0), this->m_BlockPos.at(1), this->m_BlockPos.at(2), this->m_BlockPos.at(3)
		};

		for (int i = this->m_MinHeight; i <= this->m_MaxHeight; ++i) {
			int deltaHeight = this->m_MaxHeight - i;
			for (int j = 0; j < NUMBER_COMPONANTS; ++j) {
				if (this->m_BlockPos.at(j).getYPos() == i) {
					int oldPosX = this->m_BlockPos.at(j).getXPos();
					tmpNewPos[j].setXPos(this->m_MinWidth + deltaHeight);
					tmpNewPos[j].setYPos(this->m_MinHeight - (this->m_MinWidth - oldPosX));
				}
			}
		}

		for (int i = 0; i < NUMBER_COMPONANTS; ++i)
			board->getBlockComponant(this->m_BlockPos.at(i).getXPos(), this->m_BlockPos.at(i).getYPos())->setActive(false);

		for (int i = 0; i < NUMBER_COMPONANTS; ++i) {
			if (tmpNewPos[i].getXPos() < 0 || tmpNewPos[i].getXPos() >= board::Board::WIDTH ||
				tmpNewPos[i].getYPos() < 0 || tmpNewPos[i].getYPos() >= board::Board::HEIGHT || 
				board->getBlockComponant(tmpNewPos[i].getXPos(), tmpNewPos[i].getYPos())->isActive()) {
				for (int i = 0; i < NUMBER_COMPONANTS; ++i)
					board->getBlockComponant(this->m_BlockPos.at(i).getXPos(), this->m_BlockPos.at(i).getYPos())->setActive(true);
				return false;
			}
		}

		for (int i = 0; i < NUMBER_COMPONANTS; ++i) {
			this->m_BlockPos.at(i).setXPos(tmpNewPos[i].getXPos());
			this->m_BlockPos.at(i).setYPos(tmpNewPos[i].getYPos());
		}
		this->updateBordersFromPositions();
		return true;
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
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2) - 2, 0));
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2) - 1, 0));
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2), 0));
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2) - 1, 1));

		this->m_MinWidth = (board::Board::WIDTH / 2) - 2;
		this->m_MaxWidth = (board::Board::WIDTH / 2);
		this->m_MinHeight = 0;
		this->m_MaxHeight = 1;

	}

	void Block::defineIBlock()
	{
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2) - 2, 0));
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2) - 1, 0));
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2), 0));
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2) + 1, 0));

		this->m_MinWidth = (board::Board::WIDTH / 2) - 2;
		this->m_MaxWidth = (board::Board::WIDTH / 2) + 1;
		this->m_MinHeight = 0;
		this->m_MaxHeight = 0;
	}

	void Block::defineJBlock()
	{
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2) - 1, 0));
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2), 0));
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2), 1));
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2), 2));

		this->m_MinWidth = (board::Board::WIDTH / 2) - 1;
		this->m_MaxWidth = (board::Board::WIDTH / 2);
		this->m_MinHeight = 0;
		this->m_MaxHeight = 2;
	}

	void Block::defineLBlock()
	{
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2) - 2, 1));
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2) - 1, 1));
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2), 1));
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2), 0));

		this->m_MinWidth = (board::Board::WIDTH / 2) - 2;
		this->m_MaxWidth = (board::Board::WIDTH / 2);
		this->m_MinHeight = 0;
		this->m_MaxHeight = 1;
	}

	void Block::defineOBlock()
	{
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2) - 1, 0));
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2), 0));
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2) - 1, 1));
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2), 1));

		this->m_MinWidth = (board::Board::WIDTH / 2) - 1;
		this->m_MaxWidth = (board::Board::WIDTH / 2);
		this->m_MinHeight = 0;
		this->m_MaxHeight = 1;
	}

	void Block::defineSBlock()
	{
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2) - 2, 0));
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2) - 1, 0));
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2) - 1, 1));
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2), 1));

		this->m_MinWidth = (board::Board::WIDTH / 2) - 2;
		this->m_MaxWidth = (board::Board::WIDTH / 2);
		this->m_MinHeight = 0;
		this->m_MaxHeight = 1;
	}

	void Block::defineZBlock()
	{
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2) - 2, 1));
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2) - 1, 1));
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2) - 1, 0));
		this->m_BlockPos.push_back(maths::Position((board::Board::WIDTH / 2), 0));

		this->m_MinWidth = (board::Board::WIDTH / 2) - 2;
		this->m_MaxWidth = (board::Board::WIDTH / 2);
		this->m_MinHeight = 0;
		this->m_MaxHeight = 1;
	}

	void Block::updateBordersFromPositions()
	{
		int tmpMinHeight = this->m_BlockPos.at(0).getYPos();
		int tmpMaxHeight = this->m_BlockPos.at(0).getYPos();
		int tmpMinWidth = this->m_BlockPos.at(0).getXPos();
		int tmpMaxWidth = this->m_BlockPos.at(0).getXPos();

		for (int i = 0; i < NUMBER_COMPONANTS; ++i) {
			if (this->m_BlockPos.at(i).getYPos() < tmpMinHeight)
				tmpMinHeight = this->m_BlockPos.at(i).getYPos();
			if (this->m_BlockPos.at(i).getYPos() > tmpMaxHeight)
				tmpMaxHeight = this->m_BlockPos.at(i).getYPos();
			if (this->m_BlockPos.at(i).getXPos() < tmpMinWidth)
				tmpMinWidth = this->m_BlockPos.at(i).getXPos();
			if (this->m_BlockPos.at(i).getXPos() > tmpMaxWidth)
				tmpMaxWidth = this->m_BlockPos.at(i).getXPos();
		}

		this->m_MaxHeight = tmpMaxHeight;
		this->m_MinHeight = tmpMinHeight;
		this->m_MinWidth = tmpMinWidth;
		this->m_MaxWidth = tmpMaxWidth;
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
	maths::vec4 Block::getColorFromType() const
	{
		switch (this->m_BlockType)
		{
		case BlockType::I:
			return maths::vec4(0.0f, 0.78f, 1.0f, 1.0f);
		case BlockType::J:
			return maths::vec4(0.0f, 0.0f, 1.0f , 1.0f);
		case BlockType::L:
			return maths::vec4(1.0f, 0.5f, 0.0f, 1.0f);
		case BlockType::O:
			return maths::vec4(1.0f, 0.95f, 0.0f, 1.0f);
		case BlockType::S:
			return maths::vec4(0.0f, 1.0f, 0.0f, 1.0f);
		case BlockType::T:
			return maths::vec4(0.5f, 0.0f, 1.0f, 1.0f);
		case BlockType::Z:
			return maths::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		default:
			throw;
		}
	}
}