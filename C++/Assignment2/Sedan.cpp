#include "Sedan.h"
#include "Trailer.h"

namespace assignment2
{
	Sedan::Sedan()
		: Vehicle(4), mTrailer(nullptr)
	{
		initializeTravelInfo();
	}

	Sedan::Sedan(const Sedan& other)
		: Vehicle(other), mTrailer(nullptr)
	{
		if (other.mTrailer != nullptr)
		{
			AddTrailer(new Trailer(*(other.mTrailer)));
		}

		initializeTravelInfo();
	}

	Sedan::~Sedan()
	{
		if (mTrailer != nullptr)
		{
			delete mTrailer;
		}
	}

	Sedan& Sedan::operator=(const Sedan& other)
	{
		if (this == &other)
		{
			return *this;
		}

		RemoveTrailer();
		Vehicle::operator=(other);

		if (other.mTrailer != nullptr)
		{
			AddTrailer(new Trailer(*(other.mTrailer)));
		}
		
		initializeTravelInfo();
		return *this;
	}

	bool Sedan::AddTrailer(const Trailer* trailer)
	{
		if (mTrailer == nullptr)
		{
			mTrailer = trailer;
			initializeTravelInfo();
			return true;
		}

		return false;
	}

	bool Sedan::RemoveTrailer()
	{
		if (mTrailer != nullptr)
		{
			delete mTrailer;
			mTrailer = nullptr;
			initializeTravelInfo();

			return true;
		}

		return false;
	}

	unsigned int Sedan::GetMaxSpeed() const
	{
		return GetDriveSpeed();
	}

	unsigned int Sedan::GetDriveSpeed() const
	{
		unsigned int weights = getPassengersWeight();
		if (mTrailer != nullptr)
		{
			weights += mTrailer->GetWeight();
		}

		if (weights > 350)
		{
			return 300;
		}
		else if (weights > 260)
		{
			return 380;
		}
		else if (weights > 160)
		{
			return 400;
		}
		else if (weights > 80)
		{
			return 458;
		}
		else
		{
			return 480;
		}
	}

	void Sedan::initializeTravelInfo()
	{
		mTravelCount = 5;
		if (mTrailer == nullptr)
		{
			mRestCount = 1;
		}
		else
		{
			mRestCount = 2;
		}
	}
}