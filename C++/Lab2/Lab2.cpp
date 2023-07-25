#include "Lab2.h"
#include <limits>
#include <iomanip>

namespace lab2
{
	void PrintIntegers(std::istream& in, std::ostream& out)
	{
		const int octWidth = 12;
		const int decWidth = 10;
		const int hexWidth = 8;

		out << "         oct        dec      hex" << std::endl;
		out << "------------ ---------- --------" << std::endl;

		unsigned int value;
		std::string trashText;

		while (in.eof() == false)
		{
			in >> value;
			if (in.fail())
			{
				in.clear();
				in >> trashText;
			}
			else
			{
				out << std::right << std::uppercase
					<< std::setw(octWidth) << std::oct << value << " "
					<< std::setw(decWidth) << std::dec << value << " "
					<< std::setw(hexWidth) << std::hex << value << std::endl;
			}
		}
	}

	void PrintMaxFloat(std::istream& in, std::ostream& out)
	{
		const int width = 15;
		const int precisionWidth = 3;

		float value;
		float higerValue = std::numeric_limits<float>::lowest();
		std::string trashText;

		while (in.eof() == false)
		{
			in >> value;
			if (in.fail())
			{
				in.clear();
				in >> trashText;
			}
			else
			{
				if (value > higerValue)
				{
					higerValue = value;
				}

				out << "     " << std::setw(width) << std::internal << std::setprecision(precisionWidth) << std::showpos << std::fixed << value << std::endl;
			}
		}

		out << "max: " << std::setw(width) << std::internal << std::setprecision(precisionWidth) << std::showpos << std::fixed << higerValue << std::endl;
	}
}