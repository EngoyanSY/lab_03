#include <iostream>
#include <string>
#include <vector>

#include <sstream>

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

size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx) 
{
	stringstream* buffer = reinterpret_cast<stringstream*>(ctx);

<<<<<<< HEAD
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
=======
	size_t data_size = item_count * item_size;

	buffer->write(static_cast<const char*>(items), data_size);
>>>>>>> lab_04

	return data_size;
}

Input
download(const string& address) 
{
	curl_global_init(CURL_GLOBAL_ALL);

	stringstream buffer;

	CURL* curl = curl_easy_init();
	if (curl)
	{
		CURLcode res;
		curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			exit(1);
		}
		curl_easy_cleanup(curl);
	}
<<<<<<< HEAD
	return bins;
=======

	return read_input(buffer, false);
>>>>>>> lab_04

}


<<<<<<< HEAD

int main()
{
	//���� ������
	size_t  number_count;
	cerr << "Enter number count: ";
	cin >> number_count;

	if (!number_count)
	{
		cout << "Number count = 0";
		return 0;
	}

	cerr << "Enter number: ";
	const auto numbers = input_numbers(number_count);

	size_t bin_count;
	cerr << "Enter bin count: \n";
	cin >> bin_count;
=======
int
main(int argc, char* argv[]) 
{
	//���� ������
	
	Input input;
	if (argc > 1) {
		input = download(argv[1]);
	}
	else {
		input = read_input(cin, true);
	}
>>>>>>> lab_04


	cerr << "Choose fills: \n";

	auto fills = choose_colors(bin_count, cin);
	

	//������� �����������

	const auto bins = make_histogram(input);

	//����� ������
<<<<<<< HEAD
	show_histogram_svg(bins, fills);
=======
	show_histogram_svg(bins);

	return 0;
>>>>>>> lab_04
}