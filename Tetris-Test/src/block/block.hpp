#pragma once

#include "blockType.hpp"

#include "../maths/position.hpp"
#include "../maths/vec4.hpp"

#include "../direction/direction.hpp"

#include "../board/board.hpp"

#include <vector>

namespace board {
	class Board;
}

namespace block {

	class Block
	{
	private:
		constexpr static int NUMBER_COMPONENTS = 4;

		const BlockType m_BlockType;
		std::vector<maths::position> m_BlockPos;

		int m_MaxWidth{};
		int m_MinWidth{};
		int m_MaxHeight{};
		int m_MinHeight{};

	public:
		static Block* instantiateRandomBlock();

		inline static int getNumberComponents() { return Block::NUMBER_COMPONENTS; }

		inline BlockType getBlockType() const { return this->m_BlockType; }
		maths::vec4 getColorFromType() const;
		
		inline unsigned int getMaxWidth() const { return this->m_MaxWidth; }
		inline unsigned int getMinWidth() const { return this->m_MinWidth; }
		inline unsigned int getMaxHeight() const { return this->m_MaxHeight; }
		inline unsigned int getMinHeight() const { return this->m_MinHeight; }

		inline maths::position getPositionAt(const unsigned int i) const { return this->m_BlockPos.at(i); }

		bool moveBlock(const direction::Direction direction, const board::Board* board);
		bool rotateBlock(const board::Board* board);

	private:
		explicit Block(const BlockType blockType);
		void defineComponents();
		void defineTBlock();
		void defineIBlock();
		void defineJBlock();
		void defineLBlock();
		void defineOBlock();
		void defineSBlock();
		void defineZBlock();

		void updateBordersFromPositions();
	};
}