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
	curl_global_init(CURL_GLOBAL_ALL);

	if (argc > 1)
	{
		CURL* curl = curl_easy_init();
		if (curl) {
			CURLcode res;
			curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
			res = curl_easy_perform(curl);
			if (res != CURLE_OK)
				fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));
			curl_easy_cleanup(curl);
		}
		exit(1);
	}

	
	//Ввод данных
	
	Input input = read_input(cin, true);

	//Рассчет гистограммы

	const auto bins = make_histogram(input);

	//Вывод данных
	show_histogram_svg(bins);
}