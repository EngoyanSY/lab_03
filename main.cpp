#include <iostream>
#include <vector>

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

void 
	find_minmax(const vector<double> numbers, double& min, double&max)
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

vector<size_t> 
	make_histogram(const vector<double> numbers, size_t bin_count, double min, double max)
{
	vector<size_t> bins(bin_count,0);

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

void
	show_histogram(const vector<size_t> bins, double min, double max)
{
	const size_t SCREEN_WIDTH = 80;
	const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

	size_t max_bins = bins[0];
	for (size_t bin : bins)
	{
		if (bin > max)
		{
			max_bins = bin;
		}
	}

	double height;


	for (size_t bin : bins)
	{
		height = bin;
		if (max_bins > MAX_ASTERISK)
		{
			height = MAX_ASTERISK * (static_cast<double>(bin) / max_bins);
		}

		if (bin < 100)
		{
			cout << ' ';
		}
		if (bin < 10)
		{
			cout << ' ';
		}

		cout << bin << '|';
		for (size_t i = 1; i <= height; i++)
		{
			cout << '*';
		}
		cout << "\n";
	}
}

int main()
{
	//Ввод данных
	size_t  number_count;

	cerr << "Enter number count: ";
	cin >> number_count;

	cerr << "Enter number: ";
	const auto numbers = input_numbers(number_count);

	size_t bin_count;
	cerr << "Enter bin count: ";
	cin >> bin_count;

	//Рассчет гистограммы
	double max, min;
	find_minmax(numbers, min, max);

	const auto bins = make_histogram(numbers, bin_count, min, max);

	//Вывод данных 
	show_histogram(bins, min, max);
}