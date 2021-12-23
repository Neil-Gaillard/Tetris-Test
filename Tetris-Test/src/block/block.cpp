#include "block.hpp"

#include <random>

namespace block {

	Block::Block(const BlockType blockType) : m_BlockType(blockType)
	{
		this->m_BlockPositions = new position::Position*[NUMBER_COMPONANTS];
		for (int i = 0; i < NUMBER_COMPONANTS; i++)
			this->m_BlockPositions[i] = new position::Position(0, 0);
		this->defineComponants();
	}

	void Block::defineComponants()
	{

	}

	void Block::defineTBlock()
	{

	}

	void Block::defineIBlock()
	{

	}

	void Block::defineJBlock()
	{

	}

	void Block::defineLBlock()
	{

	}

	void Block::defineOBlock()
	{

	}

	void Block::defineSBlock()
	{

	}

	void Block::defineZBlock()
	{

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