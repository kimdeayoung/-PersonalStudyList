#include "Airplane.h"
#include "Boat.h"
#include "Boatplane.h"

namespace assignment2
{
	Airplane::Airplane(unsigned int maxPassengersCount)
		: Vehicle(maxPassengersCount)
	{
		initializeTravelInfo();
	}

	Airplane::~Airplane()
	{
	}

	Boatplane Airplane::operator+(Boat& boat)
	{
		Boatplane bp = Boatplane(mMaxPassengersCount + boat.GetMaxPassengersCount());
		bp.TransferToVehicle(*this);
		bp.TransferToVehicle(boat);

		return bp;
	}

	unsigned int Airplane::GetMaxSpeed() const
	{
		unsigned int flySpeed = GetFlySpeed();
		unsigned int driveSpeed = GetDriveSpeed();
		return flySpeed > driveSpeed ? flySpeed : driveSpeed;
	}

	unsigned int Airplane::GetFlySpeed() const
	{
		return calcaulteFlySpeed(200.0, 800.0, 500.0);
	}

	unsigned int Airplane::GetDriveSpeed() const
	{
		double value = 4.0 * exp((-static_cast<double>(getPassengersWeight()) + 400.0) / 70.0);
		return static_cast<unsigned int>(round(value));
	}

	void Airplane::initializeTravelInfo()
	{
		mTravelCount = 1;
		mRestCount = 3;
	}
}