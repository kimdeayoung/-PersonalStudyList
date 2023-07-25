#pragma once

#include "Point.h"

namespace lab4
{
	class PolyLine
	{
		enum
		{
			pointCount = 10,
		};

	public:
		PolyLine();
		PolyLine(const PolyLine& other);
		~PolyLine();

		bool AddPoint(float x, float y);
		bool AddPoint(const Point* point);
		bool RemovePoint(unsigned int i);
		bool TryGetMinBoundingRectangle(Point* outMin, Point* outMax) const;

		const Point* operator[](unsigned int i) const;
		PolyLine& operator=(const PolyLine& other);
		bool operator==(const PolyLine& other) const;

		void DeepCopyPoints(const PolyLine& rawPolyLine);
	private:

		unsigned int mPointCount;
		const Point* mPoints[pointCount];
	};
}