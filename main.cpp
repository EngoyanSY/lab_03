#include <iostream>
#include <string>
#include <vector>

#include "histogram.h"
#include "SVG.h"

using namespace std;

struct Input {
	vector<double> numbers;
	size_t bin_count;
};

vector<double> 
input_numbers(istream& in, size_t count)
{
	vector<double> result(count);
	for (size_t i = 0; i < count; i++)
	{
		in >> result[i];
	}
	return result;
}

Input
read_input(istream& in)
{
	Input data;

	cerr << "Enter number count: ";
	size_t number_count;
	in >> number_count;

	cerr << "Enter numbers: ";
	data.numbers = input_numbers(in, number_count);

	cerr << "Enter bin count: ";
	in >> data.bin_count;

	return data;
}

vector<size_t> 
make_histogram(const vector<double> numbers, size_t bin_count)
{
	vector<size_t> bins(bin_count,0);
	double min, max;
	find_minmax(numbers, min, max);
	double bin_size = (max - min) / bin_count;

	for (size_t i = 0; i < numbers.size(); i++)
	{
		bool found = false;
		for (size_t j = 0; j < (bin_count - 1) && !found; j++)
		{
			auto lo = min + bin_size * j;
			auto hi = min + bin_size * (j + 1);

			if ((lo <= numbers[i]) && (numbers[i] < hi))
			{
				bins[j]++;
				found = true;
			}

		}
		if (!found)
		{
			bins[bin_count - 1]++;
		}
	}
	return bins;
}


int main()
{
	//Ввод данных
	
	Input input = read_input(cin);

	//Рассчет гистограммы

	const auto bins = make_histogram(input.numbers, input.bin_count);

	//Вывод данных
	show_histogram_svg(bins);
}