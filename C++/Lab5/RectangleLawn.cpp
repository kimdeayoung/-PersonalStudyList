#include "RectangleLawn.h"

namespace lab5
{
	RectangleLawn::RectangleLawn(unsigned int width, unsigned int height)
		: mWidth(width), mHeight(height)
	{
	}

	RectangleLawn::~RectangleLawn()
	{
	}

	unsigned int RectangleLawn::GetArea() const
	{
		return mWidth * mHeight;
	}

	unsigned int RectangleLawn::GetMinimumFencesCount() const
	{
		constexpr unsigned int fenceUseCount = static_cast<unsigned int>(eFenceInfo::FENCEUSECOUNT);
		constexpr unsigned int sideCount = 2;

		return (mWidth * fenceUseCount + mHeight * fenceUseCount) * sideCount;
	}

	unsigned int RectangleLawn::GetFencePrice(eFenceType fenceType) const
	{
		unsigned int price = 0;
		constexpr unsigned int fenceUseCount = static_cast<unsigned int>(eFenceInfo::FENCEUSECOUNT);
		switch (fenceType)
		{
		case RED_CEDAR:
			price = static_cast<unsigned int>(eFencePrice::RED_CEDAR_PRICE);
			break;
		case SPRUCE:
			price = static_cast<unsigned int>(eFencePrice::SPRUCE_PRICE);
			break;
		default:
			break;
		}

		return GetMinimumFencesCount() * price / fenceUseCount;
	}
}

