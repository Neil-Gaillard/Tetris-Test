#include "board.hpp"

namespace board {

	std::ostream& operator<<(std::ostream& stream, Board& blockComponant)
	{
		stream << "*";
		return stream;
	}

}