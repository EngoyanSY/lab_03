#include <iostream>
#include <string>
#include <vector>

#include "histogram.h"
#include "SVG.h"

#include <curl/curl.h>
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
read_input(istream& in, bool promt)
{
	Input data;

	if (promt)
		cerr << "Enter number count: ";
	size_t number_count;
	in >> number_count;

	if (promt)
		cerr << "Enter numbers: ";
	data.numbers = input_numbers(in, number_count);

	if (promt)
		cerr << "Enter bin count: ";
	in >> data.bin_count;

	return data;
}


int
main(int argc, char* argv[]) 
{

	if (argc > 1)
	{
		for (int i = 0; i < argc; i++)
			cerr << "argv[" << i << "] = " << argv[i] << "\n";
		return 0;
	}

	curl_global_init(CURL_GLOBAL_ALL);
	//���� ������
	
	Input input = read_input(cin, true);

	//������� �����������

	const auto bins = make_histogram(input);

	//����� ������
	show_histogram_svg(bins);
}