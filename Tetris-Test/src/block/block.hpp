#pragma once

#include "blockType.h"

namespace block {

	class Block
	{
	private:
		BlockType m_BlockType;

	public:
		Block* instantiateRandomBlock();

	private:
		Block(BlockType blockType);
	};

}