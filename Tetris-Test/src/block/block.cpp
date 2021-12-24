#include "block.hpp"

#include <random>

namespace block {
	Block::Block(const BlockType blockType) : m_BlockType(blockType)
	{
		this->m_BlockPositions = new maths::Position*[NUMBER_COMPONANTS];
		this->defineComponants();
	}

	void Block::setCurrent(bool current)
	{
		this->current = current;
	}

	void Block::defineComponants()
	{
		switch (this->m_BlockType)
		{
		case BlockType::I:
			this->defineIBlock();
			break;
		case BlockType::J:
			this->defineJBlock();
			break;
		case BlockType::L:
			this->defineLBlock();
			break;
		case BlockType::O:
			this->defineOBlock();
			break;
		case BlockType::S:
			this->defineSBlock();
			break;
		case BlockType::T:
			this->defineTBlock();
			break;
		case BlockType::Z:
			this->defineZBlock();
			break;
		default:
			throw;
		}
	}

	void Block::defineTBlock()
	{
		this->m_BlockPositions[0] = new maths::Position(0, 0);
		this->m_BlockPositions[1] = new maths::Position(1, 0);
		this->m_BlockPositions[2] = new maths::Position(2, 0);
		this->m_BlockPositions[3] = new maths::Position(1, 1);

		this->m_MinWidth = 0;
		this->m_MaxWidth = 2;
		this->m_MinHeight = 0;
		this->m_MaxHeight = 1;

	}

	void Block::defineIBlock()
	{
		this->m_BlockPositions[0] = new maths::Position(0, 0);
		this->m_BlockPositions[1] = new maths::Position(1, 0);
		this->m_BlockPositions[2] = new maths::Position(2, 0);
		this->m_BlockPositions[3] = new maths::Position(3, 0);


		this->m_MinWidth = 0;
		this->m_MaxWidth = 3;
		this->m_MinHeight = 0;
		this->m_MaxHeight = 0;
	}

	void Block::defineJBlock()
	{
		this->m_BlockPositions[0] = new maths::Position(0, 0);
		this->m_BlockPositions[1] = new maths::Position(1, 0);
		this->m_BlockPositions[2] = new maths::Position(1, 1);
		this->m_BlockPositions[3] = new maths::Position(1, 2);


		this->m_MinWidth = 0;
		this->m_MaxWidth = 1;
		this->m_MinHeight = 0;
		this->m_MaxHeight = 2;
	}

	void Block::defineLBlock()
	{
		this->m_BlockPositions[0] = new maths::Position(0, 0);
		this->m_BlockPositions[1] = new maths::Position(0, 1);
		this->m_BlockPositions[2] = new maths::Position(0, 2);
		this->m_BlockPositions[3] = new maths::Position(1, 0);


		this->m_MinWidth = 0;
		this->m_MaxWidth = 1;
		this->m_MinHeight = 0;
		this->m_MaxHeight = 2;
	}

	void Block::defineOBlock()
	{
		this->m_BlockPositions[0] = new maths::Position(0, 0);
		this->m_BlockPositions[1] = new maths::Position(1, 0);
		this->m_BlockPositions[2] = new maths::Position(0, 1);
		this->m_BlockPositions[3] = new maths::Position(1, 1);


		this->m_MinWidth = 0;
		this->m_MaxWidth = 1;
		this->m_MinHeight = 0;
		this->m_MaxHeight = 1;
	}

	void Block::defineSBlock()
	{
		this->m_BlockPositions[0] = new maths::Position(0, 0);
		this->m_BlockPositions[1] = new maths::Position(1, 0);
		this->m_BlockPositions[2] = new maths::Position(1, 1);
		this->m_BlockPositions[3] = new maths::Position(2, 1);


		this->m_MinWidth = 0;
		this->m_MaxWidth = 2;
		this->m_MinHeight = 0;
		this->m_MaxHeight = 1;
	}

	void Block::defineZBlock()
	{
		this->m_BlockPositions[0] = new maths::Position(0, 1);
		this->m_BlockPositions[1] = new maths::Position(1, 1);
		this->m_BlockPositions[2] = new maths::Position(1, 0);
		this->m_BlockPositions[3] = new maths::Position(2, 0);


		this->m_MinWidth = 0;
		this->m_MaxWidth = 2;
		this->m_MinHeight = 0;
		this->m_MaxHeight = 1;
	}

	Block::~Block()
	{
		for (int i = 0; i < NUMBER_COMPONANTS; i++)
			delete this->m_BlockPositions[i];
		delete[] this->m_BlockPositions;
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