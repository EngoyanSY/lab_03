#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
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

	size_t data_size = item_count * item_size;

	buffer->write(static_cast<const char*>(items), data_size);

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

		if (!res) //Индивидуальное задание вариант 6
		{
			double size;
			res = curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD, &size);
			if (!res) {
				fprintf(stderr, "Downloaded %.0f bytes\n\n", size);
			}
		}

		if (res != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n\n", curl_easy_strerror(res));
			exit(1);
		}
		curl_easy_cleanup(curl);
	}
	return read_input(buffer, false);
}

int
main(int argc, char* argv[]) 
{
	//Ввод данных
	
	Input input;
	if (argc > 1) {
		input = download(argv[1]);
	}
	else {
		input = read_input(cin, true);
	}


	cerr << "Choose fills: \n";

	const vector<string> fills = choose_colors(input.bin_count, cin);
	

	//Рассчет гистограммы

	const vector<size_t> bins = make_histogram(input);
	

	//Вывод данных
	show_histogram_svg(bins, fills);

}