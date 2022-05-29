#pragma once
#include <iostream>
#include <vector>

using namespace std;

void
find_minmax(const vector<double> numbers, double& min, double& max);

vector<string>
choose_colors(size_t bin_count, istream& stream);

vector<size_t>
make_histogram(struct Input input);

