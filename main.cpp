#include <iostream>
#include <string>
#include <vector>

#include "histogram.h"
#include "SVG.h"

using namespace std;

vector<double> 
input_numbers(size_t count)
{
	vector<double> result(count);
	for (size_t i = 0; i < count; i++)
	{
		cin >> result[i];
	}
	return result;
}


vector<size_t> 
make_histogram(const vector<double> numbers, size_t bin_count)
{
	vector<size_t> bins(bin_count,0);
	double min, max;
	find_minmax(numbers, min, max);
	double bin_size = (max - min) / bin_count;

	for (double number : numbers)
	{
		bool found = false;
		for (size_t j = 0; j < (bin_count - 1) && !found; j++)
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
			bins[bin_count - 1]++;
		}
	}
	return bins;

}



int main()
{
	//Ввод данных
	size_t  number_count;
	cerr << "Enter number count: ";
	cin >> number_count;

	if (number_count == 0)
	{
		cout << "Number count = 0";
		return 0;
	}

	cerr << "Enter number: ";
	const auto numbers = input_numbers(number_count);

	size_t bin_count;
	cerr << "Enter bin count: \n";
	cin >> bin_count;


	cerr << "Choose fills: \n";
	auto fills = choose_colors(bin_count);
	

	//Рассчет гистограммы

	const auto bins = make_histogram(numbers, bin_count);

	//Вывод данных
	show_histogram_svg(bins, fills);
}