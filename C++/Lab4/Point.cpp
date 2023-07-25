#include "Point.h"

namespace lab4
{
	Point::Point(float x, float y)
		: mX(x), mY(y)
	{
	}

	Point::Point(const Point& other)
		: mX(other.mX), mY(other.mY)
	{
	}

	Point::~Point()
	{
	}

	Point Point::operator+(const Point& other) const
	{
		return Point(mX + other.mX, mY + other.mY);
	}

	Point Point::operator-(const Point& other) const
	{
		return Point(mX - other.mX, mY - other.mY);
	}

	float Point::Dot(const Point& other) const
	{
		return mX * other.mX + mY * other.mY;
	}

	Point Point::operator*(float operand) const
	{
		return Point(mX * operand, mY * operand);
	}

	Point operator*(float operand, const Point& other)
	{
		return Point(other.mX * operand, other.mY * operand);
	}

	bool Point::operator!=(const Point& other) const
	{
		return mX != other.mX || mY != other.mY;
	}

	float Point::GetX() const
	{
		return mX;
	}

	float Point::GetY() const
	{
		return mY;
	}

	void Point::SetPoint(float x, float y)
	{
		mX = x;
		mY = y;
	}
}