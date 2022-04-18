#include <iostream>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

void
find_minmax(const vector<double> numbers, double& min, double& max)
{
	if (numbers.size() != 0)
	{
		min = numbers[0];
		max = numbers[0];

		for (double number : numbers)
		{
			if (number < min)
			{
				min = number;
			}

			else
				if (number > max)
				{
					max = number;
				}
		}
	}
}

vector<string>
choose_colors(size_t bin_count, istream& stream)
{
	vector<string> colors(bin_count);

	for (size_t i = 0; i < bin_count; i++)
	{
		cerr << "Color [" << i + 1 << "]: ";
		stream >> colors[i];
	}
	return colors;
}