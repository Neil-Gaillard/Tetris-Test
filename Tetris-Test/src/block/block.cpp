#include "block.h"

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
			return &Block::Block(BlockType::I);
		case 1:
			return &Block::Block(BlockType::J);
		case 2:
			return &Block::Block(BlockType::L);
		case 3:
			return &Block::Block(BlockType::O);
		case 4:
			return &Block::Block(BlockType::S);
		case 5:
			return &Block::Block(BlockType::T);
		case 6:
			return &Block::Block(BlockType::Z);
		default:
			return;
		}
	}
}