#pragma once

#include "../block/blockComponant.hpp"
#include "../block/block.hpp"

namespace board {

	class Board
	{
	private:
		const unsigned int HEIGHT = 20;
		const unsigned int WIDTH = 10;

		block::BlockComponant*** m_Board;

	public:
		Board();
		~Board();

		inline block::BlockComponant* getBlockComponant(const unsigned int x, const unsigned int y) const { return this->m_Board[y][x]; }

		void placeBlock(const block::Block& block);

		friend std::ostream& operator<<(std::ostream& stream, const Board& board);
	};
}