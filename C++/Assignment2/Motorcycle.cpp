#include "Motorcycle.h"

namespace assignment2
{
	Motorcycle::Motorcycle()
		: Vehicle(2)
	{
		initializeTravelInfo();
	}

	Motorcycle::~Motorcycle()
	{
	}

	unsigned int Motorcycle::GetMaxSpeed() const
	{
		return GetDriveSpeed();
	}

	unsigned int Motorcycle::GetDriveSpeed() const
	{
		int weights = static_cast<int>(getPassengersWeight());
		double value = round(pow(-(static_cast<double>(weights) / 15.0), 3.0));
		return static_cast<unsigned int>(std::max((static_cast<int>(value) + (2 * weights) + 400), 0));
	}

	void Motorcycle::initializeTravelInfo()
	{
		mTravelCount = 5;
		mRestCount = 1;
	}
}