#include "Vehicle.h"

namespace assignment2
{
	Vehicle::Vehicle(unsigned int maxPassengersCount)
		: mPassengersCount(0), mMaxPassengersCount(maxPassengersCount), mTravelCount(0), mRestCount(0), mTravelDistance(0)
	{
		for (unsigned int i = 0; i < mMaxPassengersCount; ++i)
		{
			mPassengers[i] = nullptr;
		}
	}

	Vehicle::Vehicle(const Vehicle& other)
		: mPassengersCount(other.mPassengersCount), mMaxPassengersCount(other.mMaxPassengersCount), mTravelCount(other.mTravelCount), mRestCount(other.mRestCount), mTravelDistance(other.mTravelDistance)
	{
		for (unsigned int i = 0; i < other.mPassengersCount; ++i)
		{
			mPassengers[i] = new Person(*(other.mPassengers[i]));
		}
	}

	Vehicle::~Vehicle()
	{
		destroyPassengers();
	}

	Vehicle& Vehicle::operator=(const Vehicle& other)
	{
		if (this == &other)
		{
			return *this;
		}

		destroyPassengers();

		mPassengersCount = other.mPassengersCount;
		mMaxPassengersCount = other.mMaxPassengersCount;
		mTravelCount = other.mTravelCount;
		mRestCount = other.mRestCount;
		mTravelDistance = other.mTravelDistance;
		for (unsigned int i = 0; i < other.mPassengersCount; ++i)
		{
			mPassengers[i] = new Person(*(other.mPassengers[i]));
		}

		return *this;
	}

	bool Vehicle::AddPassenger(const Person* person)
	{
		if (person == nullptr)
		{
			return false;
		}
		else if (mPassengersCount >= mMaxPassengersCount)
		{
			return false;
		}

		*(mPassengers + mPassengersCount++) = person;
		return true;
	}

	bool Vehicle::RemovePassenger(unsigned int i)
	{
		if (i >= mPassengersCount)
		{
			return false;
		}

		delete mPassengers[i];
		--mPassengersCount;

		for (unsigned int index = i; index < mPassengersCount; ++index)
		{
			mPassengers[index] = mPassengers[index + 1];
		}
		mPassengers[mPassengersCount] = nullptr;
		return true;
	}

	unsigned int Vehicle::GetPassengersCount() const
	{
		return mPassengersCount;
	}

	unsigned int Vehicle::GetMaxPassengersCount() const
	{
		return mMaxPassengersCount;
	}

	const Person* Vehicle::GetPassenger(unsigned int i) const
	{
		if (i >= mMaxPassengersCount)
		{
			return nullptr;
		}

		return mPassengers[i];
	}

	void Vehicle::TransferToVehicle(Vehicle& existingVehicle)
	{
		for (unsigned int i = 0; i < existingVehicle.GetPassengersCount(); ++i)
		{
			AddPassenger(existingVehicle.GetPassenger(i));
		}

		existingVehicle.clearPassengers();
	}

	void Vehicle::Travel()
	{
		if (mTravelCount > 0)
		{
			--mTravelCount;
			mTravelDistance += GetMaxSpeed();
		}
		else
		{
			if (--mRestCount == 0)
			{
				initializeTravelInfo();
			}
		}
	}

	unsigned int Vehicle::GetTravelDistance()
	{
		return mTravelDistance;
	}

	unsigned int Vehicle::getPassengersWeight() const
	{
		unsigned int weights = 0;
		for (unsigned int i = 0; i < mPassengersCount; ++i)
		{
			weights += mPassengers[i]->GetWeight();
		}

		return weights;
	}

	unsigned int Vehicle::calcaulteFlySpeed(double value1, double value2, double value3) const
	{
		double value = value1 * exp((-static_cast<double>(getPassengersWeight()) + value2) / value3);
		return static_cast<unsigned int>(round(value));
	}

	void Vehicle::clearPassengers()
	{
		for (unsigned int i = 0; i < mPassengersCount; ++i)
		{
			mPassengers[i] = nullptr;
		}
		mPassengersCount = 0;
	}

	void Vehicle::destroyPassengers()
	{
		for (unsigned int i = 0; i < mPassengersCount; ++i)
		{
			delete mPassengers[i];
		}
	}
}