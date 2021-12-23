#pragma once

#include "../block/blockComponant.hpp"

namespace board {

	class Board
	{
	private:
		const static unsigned int HEIGHT = 20;
		const static unsigned int WIDTH = 10;

		block::BlockComponant*** m_Board;
	public:

		friend std::ostream& operator<<(std::ostream& stream, const Board& blockComponant);
	};

}