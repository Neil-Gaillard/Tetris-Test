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

		void placeBlock(const block::Block& block);

		friend std::ostream& operator<<(std::ostream& stream, const Board& board);
	};
}