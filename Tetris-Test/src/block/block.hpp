#pragma once

#include "blockType.hpp"
#include "../maths/position.hpp"
#include "../direction/direction.hpp"

namespace block {

	class Block
	{
	private:
		const static int NUMBER_COMPONANTS = 4;

		const BlockType m_BlockType;
		maths::Position** m_BlockPositions;

		int m_MaxWidth;
		int m_MinWidth;
		int m_MaxHeight;
		int m_MinHeight;

		bool current;

	public:
		~Block();

		static Block* instantiateRandomBlock();

		inline static int getNumberComponants() { return Block::NUMBER_COMPONANTS; }

		inline BlockType getBlockType() const { return this->m_BlockType; }

		inline unsigned int getMaxWidth() const { return this->m_MaxWidth; }
		inline unsigned int getMinWidth() const { return this->m_MinWidth; }
		inline unsigned int getMaxHeight() const { return this->m_MaxHeight; }
		inline unsigned int getMinHeight() const { return this->m_MinHeight; }

		inline bool isCurrent() const { return this->current; }

		inline maths::Position getPositionAtIndex(const unsigned int i) const { return *this->m_BlockPositions[i]; }

		void setCurrent(bool current);

		bool moveBlock(direction::Direction direction);

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