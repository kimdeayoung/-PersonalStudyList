#include "EquilateralTriangleLawn.h"

namespace lab5
{
	EquilateralTriangleLawn::EquilateralTriangleLawn(unsigned int leg)
		: mLeg(leg)
	{
	}

	EquilateralTriangleLawn::~EquilateralTriangleLawn()
	{
	}

	unsigned int EquilateralTriangleLawn::GetArea() const
	{
		double area = round((mLeg * mLeg) / 4.0 * sqrt(3.0));
		return static_cast<unsigned int>(area);
	}

	unsigned int EquilateralTriangleLawn::GetMinimumFencesCount() const
	{
		constexpr unsigned int fenceUseCount = static_cast<unsigned int>(eFenceInfo::FENCEUSECOUNT);
		constexpr unsigned int legCount = 3;

		return mLeg * fenceUseCount * legCount;
	}

	unsigned int EquilateralTriangleLawn::GetFencePrice(eFenceType fenceType) const
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