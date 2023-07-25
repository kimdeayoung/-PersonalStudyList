#pragma once

namespace lab9
{
	class Random final
	{
	public:
		Random(int seed);
		~Random() = default;

		int GetNext();

	private:
		int mSeed;
		int mIndex;

		enum { ROW_SIZE = 10, COLUMN_SIZE = 20 };

		static int mNumbers[ROW_SIZE][COLUMN_SIZE];
	};
}