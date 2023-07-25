#include "Boat.h"
#include "Airplane.h"

namespace assignment2
{
	Boat::Boat(unsigned int maxPassengersCount)
		: Vehicle(maxPassengersCount)
	{
		initializeTravelInfo();
	}

	Boat::~Boat()
	{
	}

	Boatplane Boat::operator+(Airplane& plane)
	{
		Boatplane bp = Boatplane(mMaxPassengersCount + plane.GetMaxPassengersCount());
		bp.TransferToVehicle(plane);
		bp.TransferToVehicle(*this);

		return bp;
	}

	unsigned int Boat::GetSailSpeed() const
	{
		return std::max((800 - 10 * static_cast<int>(getPassengersWeight())), 20);
	}

	unsigned int Boat::GetMaxSpeed() const
	{
		return GetSailSpeed();
	}

	void Boat::initializeTravelInfo()
	{
		mTravelCount = 2;
		mRestCount = 1;
	}
}