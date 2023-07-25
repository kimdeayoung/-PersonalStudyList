#pragma once

namespace lab4
{
	class Point
	{
	public:
		Point(float x, float y);
		Point(const Point& other);
		~Point();

		Point operator+(const Point& other) const;
		Point operator-(const Point& other) const;
		float Dot(const Point& other) const;
		Point operator*(float operand) const;
		friend Point operator*(float operand, const Point& other);
		bool operator!=(const Point& other) const;

		float GetX() const;
		float GetY() const;

		void SetPoint(float x, float y);
		
	private:
		float mX;
		float mY;
	};
}