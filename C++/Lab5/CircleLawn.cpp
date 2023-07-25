#include "CircleLawn.h"

namespace lab5
{
	CircleLawn::CircleLawn(unsigned int radius)
		: mRadius(radius)
	{
	}

	CircleLawn::~CircleLawn()
	{
	}

	unsigned int CircleLawn::GetArea() const
	{
		double radius = static_cast<double>(mRadius);
		double area = round(radius * radius * 3.14);
		return static_cast<unsigned int>(area);
	}
}

