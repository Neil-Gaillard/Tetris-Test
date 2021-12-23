#pragma once

#include "blockType.hpp"
#include "blockComponant.hpp"

namespace block {

	class Block
	{
	private:
		const static int NUMBER_COMPONANTS = 4;

		const BlockType m_BlockType;
		BlockComponant** m_blockComponants;

		unsigned int m_MaxWidth;
		unsigned int m_MinWidth;
		unsigned int m_MaxHeight;
		unsigned int m_MinHeight;

	public:
		~Block();

		Block* instantiateRandomBlock();

		inline BlockType getBlockType() const { return this->m_BlockType; }

		inline unsigned int getMaxWidth() const { return this->m_MaxWidth; }
		inline unsigned int getMinWidth() const { return this->m_MinWidth; }
		inline unsigned int getMaxHeight() const { return this->m_MaxHeight; }
		inline unsigned int getMinHeight() const { return this->m_MinHeight; }


	private:
		Block(BlockType blockType);
		static void defineComponants();
		static void defineTBlock();
		static void defineIBlock();
		static void defineJBlock();
		static void defineLBlock();
		static void defineOBlock();
		static void defineSBlock();
		static void defineZBlock();
	};
}