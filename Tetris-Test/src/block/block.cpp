#include "block.hpp"
#include "../utils/utils.hpp"

#include <algorithm>
#include <random>

namespace block {
	Block::Block(const BlockType blockType) : m_BlockType(blockType)
	{
		this->defineComponents();
	}

	bool Block::moveBlock(const direction::Direction direction, const board::Board* board)
	{
		switch (direction)
		{
		case direction::Direction::LEFT:
			if (this->m_MinWidth - 1 < 0)
				return false;
			for (int i = 0; i < NUMBER_COMPONENTS; ++i)
				if (!(std::find(this->m_BlockPos.begin(), this->m_BlockPos.end(), this->m_BlockPos.at(i) - maths::position(1, 0)) != this->m_BlockPos.end())
					&& board->getBlockComponent(this->m_BlockPos.at(i).get_x_pos() - 1, this->m_BlockPos.at(i).get_y_pos())->isActive())
					return false;
			for (int i = 0; i < block::Block::NUMBER_COMPONENTS; ++i)
				this->m_BlockPos.at(i) -= maths::position(1, 0);
			--this->m_MinWidth;
			--this->m_MaxWidth;
			return true;
		case direction::Direction::RIGHT:
			if (this->m_MaxWidth + 1 >= board::Board::WIDTH)
				return false;
			for (int i = 0; i < NUMBER_COMPONENTS; ++i)
				if (!(std::find(this->m_BlockPos.begin(), this->m_BlockPos.end(), this->m_BlockPos.at(i) + maths::position(1, 0)) != this->m_BlockPos.end())
					&& board->getBlockComponent(this->m_BlockPos.at(i).get_x_pos() + 1, this->m_BlockPos.at(i).get_y_pos())->isActive())
					return false;
			for (int i = 0; i < block::Block::NUMBER_COMPONENTS; ++i)
				this->m_BlockPos.at(i) += maths::position(1, 0);
			++this->m_MaxWidth;
			++this->m_MinWidth;
			return true;
		case direction::Direction::DOWN:
			if (this->m_MaxHeight + 1 >= board::Board::HEIGHT)
				return false;
			for (int i = 0; i < NUMBER_COMPONENTS; ++i)
				if (!(std::find(this->m_BlockPos.begin(), this->m_BlockPos.end(), this->m_BlockPos.at(i) + maths::position(0, 1)) != this->m_BlockPos.end())
					&& board->getBlockComponent(this->m_BlockPos.at(i).get_x_pos(), this->m_BlockPos.at(i).get_y_pos() + 1)->isActive())
					return false;
			for (int i = 0; i < block::Block::NUMBER_COMPONENTS; ++i)
				this->m_BlockPos.at(i) += maths::position(0, 1);
			++this->m_MaxHeight;
			++this->m_MinHeight;
			return true;
		case direction::Direction::UP: break;
		}
		return false;
	}
	 
	bool Block::rotateBlock(const board::Board* board)
	{
		maths::position tmpNewPos[4] =
		{
			this->m_BlockPos.at(0), this->m_BlockPos.at(1), this->m_BlockPos.at(2), this->m_BlockPos.at(3)
		};

		for (int i = this->m_MinHeight; i <= this->m_MaxHeight; ++i) {
			const int deltaHeight = this->m_MaxHeight - i;
			for (int j = 0; j < NUMBER_COMPONENTS; ++j) {
				if (this->m_BlockPos.at(j).get_y_pos() == i) {
					const int oldPosX = this->m_BlockPos.at(j).get_x_pos();
					tmpNewPos[j].set_x_pos(this->m_MinWidth + deltaHeight);
					tmpNewPos[j].set_y_pos(this->m_MinHeight - (this->m_MinWidth - oldPosX));
				}
			}
		}

		for (int i = 0; i < NUMBER_COMPONENTS; ++i)
			board->getBlockComponent(this->m_BlockPos.at(i).get_x_pos(), this->m_BlockPos.at(i).get_y_pos())->setActive(false);

		for (auto& tmpNewPo : tmpNewPos)
		{
			if (tmpNewPo.get_x_pos() < 0 || tmpNewPo.get_x_pos() >= board::Board::WIDTH ||
				tmpNewPo.get_y_pos() < 0 || tmpNewPo.get_y_pos() >= board::Board::HEIGHT || 
				board->getBlockComponent(tmpNewPo.get_x_pos(), tmpNewPo.get_y_pos())->isActive()) {
				for (int i = 0; i < NUMBER_COMPONENTS; ++i)
					board->getBlockComponent(this->m_BlockPos.at(i).get_x_pos(), this->m_BlockPos.at(i).get_y_pos())->setActive(true);
				return false;
			}
		}

		for (int i = 0; i < NUMBER_COMPONENTS; ++i) {
			this->m_BlockPos.at(i).set_x_pos(tmpNewPos[i].get_x_pos());
			this->m_BlockPos.at(i).set_y_pos(tmpNewPos[i].get_y_pos());
		}
		this->updateBordersFromPositions();
		return true;
	}

	void Block::defineComponents()
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
		}
	}

	void Block::defineTBlock()
	{
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2) - 2, 0));
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2) - 1, 0));
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2), 0));
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2) - 1, 1));

		this->m_MinWidth = (board::Board::WIDTH / 2) - 2;
		this->m_MaxWidth = (board::Board::WIDTH / 2);
		this->m_MinHeight = 0;
		this->m_MaxHeight = 1;

	}

	void Block::defineIBlock()
	{
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2) - 2, 0));
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2) - 1, 0));
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2), 0));
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2) + 1, 0));

		this->m_MinWidth = (board::Board::WIDTH / 2) - 2;
		this->m_MaxWidth = (board::Board::WIDTH / 2) + 1;
		this->m_MinHeight = 0;
		this->m_MaxHeight = 0;
	}

	void Block::defineJBlock()
	{
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2) - 2, 0));
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2) - 1, 0));
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2), 0));
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2), 1));

		this->m_MinWidth = (board::Board::WIDTH / 2) - 2;
		this->m_MaxWidth = (board::Board::WIDTH / 2);
		this->m_MinHeight = 0;
		this->m_MaxHeight = 1;
	}

	void Block::defineLBlock()
	{
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2) - 2, 1));
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2) - 1, 1));
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2), 1));
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2), 0));

		this->m_MinWidth = (board::Board::WIDTH / 2) - 2;
		this->m_MaxWidth = (board::Board::WIDTH / 2);
		this->m_MinHeight = 0;
		this->m_MaxHeight = 1;
	}

	void Block::defineOBlock()
	{
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2) - 1, 0));
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2), 0));
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2) - 1, 1));
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2), 1));

		this->m_MinWidth = (board::Board::WIDTH / 2) - 1;
		this->m_MaxWidth = (board::Board::WIDTH / 2);
		this->m_MinHeight = 0;
		this->m_MaxHeight = 1;
	}

	void Block::defineSBlock()
	{
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2) - 2, 0));
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2) - 1, 0));
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2) - 1, 1));
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2), 1));

		this->m_MinWidth = (board::Board::WIDTH / 2) - 2;
		this->m_MaxWidth = (board::Board::WIDTH / 2);
		this->m_MinHeight = 0;
		this->m_MaxHeight = 1;
	}

	void Block::defineZBlock()
	{
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2) - 2, 1));
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2) - 1, 1));
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2) - 1, 0));
		this->m_BlockPos.push_back(maths::position((board::Board::WIDTH / 2), 0));

		this->m_MinWidth = (board::Board::WIDTH / 2) - 2;
		this->m_MaxWidth = (board::Board::WIDTH / 2);
		this->m_MinHeight = 0;
		this->m_MaxHeight = 1;
	}

	void Block::updateBordersFromPositions()
	{
		int tmpMinHeight = this->m_BlockPos.at(0).get_y_pos();
		int tmpMaxHeight = this->m_BlockPos.at(0).get_y_pos();
		int tmpMinWidth = this->m_BlockPos.at(0).get_x_pos();
		int tmpMaxWidth = this->m_BlockPos.at(0).get_x_pos();

		for (int i = 0; i < NUMBER_COMPONENTS; ++i) {
			if (this->m_BlockPos.at(i).get_y_pos() < tmpMinHeight)
				tmpMinHeight = this->m_BlockPos.at(i).get_y_pos();
			if (this->m_BlockPos.at(i).get_y_pos() > tmpMaxHeight)
				tmpMaxHeight = this->m_BlockPos.at(i).get_y_pos();
			if (this->m_BlockPos.at(i).get_x_pos() < tmpMinWidth)
				tmpMinWidth = this->m_BlockPos.at(i).get_x_pos();
			if (this->m_BlockPos.at(i).get_x_pos() > tmpMaxWidth)
				tmpMaxWidth = this->m_BlockPos.at(i).get_x_pos();
		}

		this->m_MaxHeight = tmpMaxHeight;
		this->m_MinHeight = tmpMinHeight;
		this->m_MinWidth = tmpMinWidth;
		this->m_MaxWidth = tmpMaxWidth;
	}

	Block* Block::instantiateRandomBlock()
	{
		const int var = rand() % BLOCK_TYPE_NUMBER;
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
			return {0.0f, 0.78f, 1.0f, 1.0f};
		case BlockType::J:
			return {0.0f, 0.0f, 1.0f , 1.0f};
		case BlockType::L:
			return {1.0f, 0.5f, 0.0f, 1.0f};
		case BlockType::O:
			return { 1.0f, 0.95f, 0.0f, 1.0f};
		case BlockType::S:
			return {0.0f, 1.0f, 0.0f, 1.0f};
		case BlockType::T:
			return {0.5f, 0.0f, 1.0f, 1.0f};
		case BlockType::Z:
			return {1.0f, 0.0f, 0.0f, 1.0f};
		}
		return {};
	}
}
