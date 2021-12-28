#pragma once

#include "../block/blockComponant.hpp"
#include "../block/block.hpp"

namespace block {
	class Block;
}

namespace board {

	class Board
	{
	public:
		const static unsigned int HEIGHT = 20;
		const static unsigned int WIDTH = 10;

	private:
		block::BlockComponant*** m_Board;

	public:
		Board();
		~Board();

		inline block::BlockComponant* getBlockComponant(const unsigned int x, const unsigned int y) const { return this->m_Board[y][x]; }

		void placeBlock(const block::Block& block);
		void moveBlock(const block::Block& block, direction::Direction direction);
		void rotateBlock(const block::Block& block);

		void verifLine(const block::Block& block);
#if 0
		friend std::ostream& operator<<(std::ostream& stream, const Board& board);
#endif
	};
}