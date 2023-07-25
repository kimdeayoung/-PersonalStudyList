#pragma once

#include "Lawn.h"

namespace lab5
{
	class CircleLawn : public Lawn
	{
	public:
		CircleLawn(unsigned int radius);
		~CircleLawn();

		unsigned int GetArea() const;
	private:
		const unsigned int mRadius;
	};
}


