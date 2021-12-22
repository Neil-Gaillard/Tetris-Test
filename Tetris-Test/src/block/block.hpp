#pragma once

#include "blockType.hpp"
#include "../position/position.hpp"

namespace block {

	class Block
	{
	private:
		const BlockType m_BlockType;
		position::Position m_Pos;

	public:
		Block* instantiateRandomBlock();

		inline BlockType getBlockType() const { return this->m_BlockType; }

		inline position::Position getPos() const { return this->m_Pos; }

		inline void setPosX(const int x) { this->m_Pos.setXPos(x); }
		inline void setPosY(const int y) { this->m_Pos.setYPos(y); }

	private:
		Block(BlockType blockType);
	};
}