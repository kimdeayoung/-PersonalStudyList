#include "Lawn.h"
#include <cassert>

namespace lab5
{
	Lawn::Lawn()
	{
	}

	Lawn::~Lawn()
	{
	}

	unsigned int Lawn::GetGrassPrice(eGrassType grassType) const
	{
		unsigned int grassUnitPrice = 0;
		switch (grassType)
		{
		case BERMUDA:
			grassUnitPrice = 800;
			break;
		case BAHIA:
			grassUnitPrice = 500;
			break;
		case BENTGRASS:
			grassUnitPrice = 300;
			break;
		case PERENNIAL_RYEGRASS:
			grassUnitPrice = 250;
			break;
		case ST_AUGUSTINE:
			grassUnitPrice = 450;
			break;
		default:
			assert(0);
			break;
		}
		double price = ceil(static_cast<double>(grassUnitPrice * GetArea()) / 100.0);
		return static_cast<unsigned int>(price);
	}

	unsigned int Lawn::GetMinimumSodRollsCount() const
	{
		double area = static_cast<double>(GetArea());
		return static_cast<unsigned int>(ceil(area / 0.3));
	}
}