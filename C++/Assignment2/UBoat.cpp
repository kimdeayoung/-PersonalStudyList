#include "UBoat.h"

namespace assignment2
{
	UBoat::UBoat()
		: Vehicle(50)
	{
		initializeTravelInfo();
	}

	UBoat::~UBoat()
	{
	}

	unsigned int UBoat::GetMaxSpeed() const
	{
		unsigned int diveSpeed = GetDiveSpeed();
		unsigned int sailSpeed = GetSailSpeed();

		return diveSpeed > sailSpeed ? diveSpeed : sailSpeed;
	}

	unsigned int UBoat::GetDiveSpeed() const
	{
		return static_cast<unsigned int>(std::max(550 - (static_cast<int>(getPassengersWeight() / 10)), 200));
	}

	unsigned int UBoat::GetSailSpeed() const
	{
		double passengersWeight = static_cast<double>(getPassengersWeight());
		return static_cast<unsigned int>(500.0 * log((passengersWeight + 150.0) / 150.0) + 30.0);
	}

	void UBoat::initializeTravelInfo()
	{
		mTravelCount = 2;
		mRestCount = 4;
	}
}