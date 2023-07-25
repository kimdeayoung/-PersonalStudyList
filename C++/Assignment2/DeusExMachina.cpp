#include "DeusExMachina.h"

namespace assignment2
{
	DeusExMachina* DeusExMachina::mInstance = nullptr;

	DeusExMachina::DeusExMachina()
		: mVehicleCount(0), mVehicles{nullptr, }
	{
	}

	DeusExMachina::~DeusExMachina()
	{
		for (unsigned int i = 0; i < mVehicleCount; ++i)
		{
			delete mVehicles[i];
		}
	}

	DeusExMachina* DeusExMachina::GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new DeusExMachina();
		}
		return mInstance;
	}

	void DeusExMachina::Travel() const
	{
		for (unsigned int i = 0; i < mVehicleCount; ++i)
		{
			mVehicles[i]->Travel();
		}
	}

	bool DeusExMachina::AddVehicle(Vehicle* vehicle)
	{
		if (mVehicleCount < MANAGED_VEHICLE_COUNT)
		{
			*(mVehicles + mVehicleCount++) = vehicle;
			return true;
		}

		return false;
	}

	bool DeusExMachina::RemoveVehicle(unsigned int i)
	{
		if (mVehicleCount > i)
		{
			delete mVehicles[i];
			--mVehicleCount;

			Vehicle** replaceVehicle = mVehicles + i;
			Vehicle** replaceNextVehicle = mVehicles + i + 1;
			for (unsigned int index = i; index < mVehicleCount; ++index)
			{
				*replaceVehicle++ = *replaceNextVehicle++;
			}
			*(replaceVehicle) = nullptr;

			return true;
		}

		return false;
	}

	Vehicle* DeusExMachina::GetVehicle(unsigned int i)
	{
		return *(mVehicles + i);
	}

	const Vehicle* DeusExMachina::GetFurthestTravelled() const
	{
		if (mVehicleCount == 0)
		{
			return nullptr;
		}

		Vehicle* result = mVehicles[0];
		for (unsigned int i = 1; i < mVehicleCount; ++i)
		{
			if (result->GetTravelDistance() < mVehicles[i]->GetTravelDistance())
			{
				result = mVehicles[i];
			}
		}

		return result;
	}
}
