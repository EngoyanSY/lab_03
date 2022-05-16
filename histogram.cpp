#include <iostream>
#include <vector>

using namespace std;

struct Input {
	vector<double> numbers;
	size_t bin_count;
};

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

vector<size_t>
make_histogram(struct Input input)
{
	vector<size_t> bins(input.bin_count, 0);
	double min, max;
	find_minmax(input.numbers, min, max);
	double bin_size = (max - min) / input.bin_count;

	for (double number : input.numbers)
	{
		bool found = false;
		for (size_t j = 0; j < (input.bin_count - 1) && !found; j++)
		{
			auto lo = min + bin_size * j;
			auto hi = min + bin_size * (j + 1);

			if ((lo <= number) && (number < hi))
			{
				bins[j]++;
				found = true;
			}

		}
		if (!found)
		{
			bins[input.bin_count - 1]++;
		}
	}
	return bins;
}
