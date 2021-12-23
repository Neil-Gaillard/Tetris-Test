#include "blockComponant.hpp"

namespace block {

	BlockComponant::BlockComponant(unsigned int x, unsigned int y) : m_Pos(x, y)
	{
		
	}

	std::ostream& operator<<(std::ostream& stream, const BlockComponant& blockComponant)
	{
		stream << "*";
		return stream;
	}
}