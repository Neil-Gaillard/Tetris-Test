#include "blockComponant.hpp"

namespace block {

	BlockComponant::BlockComponant(unsigned int x, unsigned int y, bool active) : m_Pos(x, y), active(active)
	{

	}

	BlockComponant::BlockComponant(unsigned int x, unsigned int y) : BlockComponant(x, y, false)
	{

	}

	std::ostream& operator<<(std::ostream& stream, const BlockComponant& blockComponant)
	{
		switch (blockComponant.active) {
		case true:
			stream << "*";
			break;
		case false:
			stream << " ";
		}
		return stream;
	}
}