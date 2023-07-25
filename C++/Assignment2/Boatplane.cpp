#include "Boatplane.h"

namespace assignment2
{
	Boatplane::Boatplane(unsigned int maxPassengersCount)
		: Vehicle(maxPassengersCount)
	{
		initializeTravelInfo();
	}

	Boatplane::~Boatplane()
	{
	}

	unsigned int Boatplane::GetMaxSpeed() const
	{
		unsigned int flySpeed = GetFlySpeed();
		unsigned int sailSpeed = GetSailSpeed();

		return flySpeed > sailSpeed ? flySpeed : sailSpeed;
	}

	unsigned int Boatplane::GetFlySpeed() const
	{
		return calcaulteFlySpeed(150.0, 500.0, 300.0);
	}

	unsigned int Boatplane::GetSailSpeed() const
	{
		double value = round((1.7 * static_cast<double>(getPassengersWeight())));
		return std::max((800 - static_cast<int>(value)), 20);
	}

	void Boatplane::initializeTravelInfo()
	{
		mTravelCount = 1;
		mRestCount = 3;
	}
}