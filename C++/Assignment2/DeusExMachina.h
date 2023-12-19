#pragma once

#include "Vehicle.h"

namespace assignment2
{
	enum eManagedVehicleInfo
	{
		MANAGED_VEHICLE_COUNT = 10,
	};

	class DeusExMachina
	{
	public:
		DeusExMachina(const DeusExMachina&) = delete;
		DeusExMachina& operator=(const DeusExMachina&) = delete;

		static DeusExMachina* GetInstance();
		void Travel() const;
		bool AddVehicle(Vehicle* vehicle);
		bool RemoveVehicle(unsigned int i);
		Vehicle* GetVehicle(unsigned int i);
		const Vehicle* GetFurthestTravelled() const;
	private:
		DeusExMachina();
		~DeusExMachina();
		
		static DeusExMachina* mInstance;

		unsigned int mVehicleCount;
		Vehicle* mVehicles[MANAGED_VEHICLE_COUNT];
	};
}