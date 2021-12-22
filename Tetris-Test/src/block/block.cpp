#include "block.hpp"

#include <random>

namespace block {

	Block::Block(BlockType blockType) : m_BlockType(blockType)
	{

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