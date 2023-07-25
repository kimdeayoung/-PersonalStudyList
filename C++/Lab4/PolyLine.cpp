#include <cstring>
#include <cmath>
#include "PolyLine.h"

namespace lab4
{
	PolyLine::PolyLine()
		: mPointCount(0)
	{
		for (unsigned int i = 0; i < pointCount; ++i)
		{
			mPoints[i] = nullptr;
		}
	}

	PolyLine::PolyLine(const PolyLine& other)
		: mPointCount(other.mPointCount)
	{
		DeepCopyPoints(other);
	}

	PolyLine::~PolyLine()
	{
		for (unsigned int i = 0; i < mPointCount; ++i)
		{
			delete mPoints[i];
		}
	}

	bool PolyLine::AddPoint(float x, float y)
	{
		if (mPointCount < pointCount)
		{
			*(mPoints + mPointCount++) = new Point(x, y);
			return true;
		}

		return false;
	}

	bool PolyLine::AddPoint(const Point* point)
	{
		if (mPointCount < pointCount)
		{
			*(mPoints + mPointCount++) = point;
			return true;
		}

		return false;
	}

	bool PolyLine::RemovePoint(unsigned int i)
	{
		if (i >= mPointCount)
		{
			return false;
		}

		if (mPoints[i] != nullptr)
		{
			delete mPoints[i];
			mPoints[i] = nullptr;
			--mPointCount;

			for (unsigned int index = i; index < mPointCount; ++index)
			{
				mPoints[index] = mPoints[index + 1];
			}
			mPoints[mPointCount] = nullptr;

			return true;
		}
		return false;
	}

	bool PolyLine::TryGetMinBoundingRectangle(Point* outMin, Point* outMax) const
	{
		if (mPointCount > 0)
		{
			float minX = std::numeric_limits<float>::max();
			float minY = std::numeric_limits<float>::max();

			float maxX = std::numeric_limits<float>::lowest();
			float maxY = std::numeric_limits<float>::lowest();

			for (unsigned int i = 0; i < pointCount; ++i)
			{
				if (mPoints[i] != nullptr)
				{
					float x = mPoints[i]->GetX();
					float y = mPoints[i]->GetY();

					if (minX > x)
					{
						minX = x;
					}
					if (maxX < x)
					{
						maxX = x;
					}

					if (minY > y)
					{
						minY = y;
					}
					if (maxY < y)
					{
						maxY = y;
					}
				}
			}

			outMin->SetPoint(minX, minY);
			outMax->SetPoint(maxX, maxY);
			return true;
		}
		return false;
	}

	const Point* PolyLine::operator[](unsigned int i) const
	{
		if (i >= pointCount)
		{
			return nullptr;
		}

		return *(mPoints + i);
	}

	PolyLine& PolyLine::operator=(const PolyLine& other)
	{
		if (*this == other)
		{
			return *this;
		}

		for (unsigned int i = 0; i < mPointCount; ++i)
		{
			delete mPoints[i];
		}

		mPointCount = other.mPointCount;
		DeepCopyPoints(other);

		return *this;
	}

	bool PolyLine::operator==(const PolyLine& other) const
	{
		if (mPointCount != other.mPointCount)
		{
			return false;
		}

		for (unsigned int i = 0; i < pointCount; ++i)
		{
			const Point* point = other[i];
			if (mPoints[i] != point)
			{
				return false;
			}
		}

		return true;
	}

	void PolyLine::DeepCopyPoints(const PolyLine& rawPolyLine)
	{
		for (unsigned int i = 0; i < pointCount; ++i)
		{
			const Point* point = rawPolyLine[i];
			if (point == nullptr)
			{
				mPoints[i] = nullptr;
			}
			else
			{
				mPoints[i] = new Point(*point);
			}
		}
	}
}