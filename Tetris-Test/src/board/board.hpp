#pragma once

#include "../block/BlockComponent.hpp"
#include "../block/block.hpp"

namespace block {
	class Block;
}

namespace board {

	class Board
	{
	public:
		constexpr static int HEIGHT = 20;
		constexpr static int WIDTH = 10;

	private:
		block::BlockComponent*** m_Board;

	public:
		Board();
		~Board();

		inline block::BlockComponent* getBlockComponent(const int x, const int y) const { return this->m_Board[y][x]; }

		void placeBlock(const block::Block& block) const;
		void moveBlock(const block::Block& block, direction::Direction direction) const;

		void lineVerification(const block::Block& block, int &score) const;
	};
}