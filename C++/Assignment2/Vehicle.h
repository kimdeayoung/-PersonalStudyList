#pragma once

#include "Person.h"

namespace assignment2
{
	class Vehicle
	{
		enum eVehicleInfo
		{
			PASSENGERS_LIMIT = 100
		};

	public:
		Vehicle(unsigned int maxPassengersCount);
		Vehicle(const Vehicle& other);
		virtual ~Vehicle();

		Vehicle& operator=(const Vehicle& other);

		virtual unsigned int GetMaxSpeed() const = 0;

		bool AddPassenger(const Person* person);
		bool RemovePassenger(unsigned int i);
		const Person* GetPassenger(unsigned int i) const;
		unsigned int GetPassengersCount() const;
		unsigned int GetMaxPassengersCount() const;

		void TransferToVehicle(Vehicle& existingVehicle);
		void Travel();
		unsigned int GetTravelDistance();
	protected:
		virtual void initializeTravelInfo() = 0;

		unsigned int getPassengersWeight() const;

		unsigned int calcaulteFlySpeed(double value1, double value2, double value3) const;
		
		unsigned int mPassengersCount;
		unsigned int mMaxPassengersCount;
		const Person* mPassengers[PASSENGERS_LIMIT];

		unsigned int mTravelCount;
		unsigned int mRestCount;
		unsigned int mTravelDistance;
	private:
		void clearPassengers();
		void destroyPassengers();
	};
}