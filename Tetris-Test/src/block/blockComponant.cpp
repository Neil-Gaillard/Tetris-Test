#include "blockComponant.hpp"

namespace block {

	BlockComponant::BlockComponant(unsigned int x, unsigned int y) : m_Pos(x, y), active(false)
	{
		
	}

	std::ostream& operator<<(std::ostream& stream, const BlockComponant& blockComponant)
	{
		switch (blockComponant.active) {
		case true:
			stream << "*";
			return stream;
		case false:
			stream << " ";
			return stream;
		}
	}
}