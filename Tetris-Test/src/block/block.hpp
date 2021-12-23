#pragma once

#include "blockType.hpp"
#include "../maths/position.hpp"

namespace block {

	class Block
	{
	private:
		const static int NUMBER_COMPONANTS = 4;

		const BlockType m_BlockType;
		maths::Position** m_BlockPositions;

		unsigned int m_MaxWidth;
		unsigned int m_MinWidth;
		unsigned int m_MaxHeight;
		unsigned int m_MinHeight;

	public:
		~Block();

		static Block* instantiateRandomBlock();

		inline static int getNumberComponants() { return Block::NUMBER_COMPONANTS; }

		inline BlockType getBlockType() const { return this->m_BlockType; }

		inline unsigned int getMaxWidth() const { return this->m_MaxWidth; }
		inline unsigned int getMinWidth() const { return this->m_MinWidth; }
		inline unsigned int getMaxHeight() const { return this->m_MaxHeight; }
		inline unsigned int getMinHeight() const { return this->m_MinHeight; }

		inline maths::Position getPositionAtIndex(const unsigned int i) const { return *this->m_BlockPositions[i]; }

	private:
		Block(const BlockType blockType);
		void defineComponants();
		void defineTBlock();
		void defineIBlock();
		void defineJBlock();
		void defineLBlock();
		void defineOBlock();
		void defineSBlock();
		void defineZBlock();
	};
}