#include "histogram.h"

#include <cassert>
#include <vector>
#include <string>

void
test_positive()
{
	double min = 0;
	double max = 0;
	find_minmax({ 1, 2, 3 }, min, max);
	assert(min == 1);
	assert(max == 3);
}

void
test_negative()
{
	double min = 0;
	double max = 0;
	find_minmax({ -1, -2, -3 }, min, max);
	assert(min == -3);
	assert(max == -1);
}

void 
test_similar()
{
	double min = 0;
	double max = 0;
	find_minmax({ 7, 7, 7 }, min, max);
	assert(max == 7);
	assert(min == 7);;
}

void
test_single()
{
	double min = 0;
	double max = 0;
	find_minmax({ 5 }, min, max);
	assert(max == 5);
	assert(min == 5);
	
}

void
test_void()
{
	double min = 5;
	double max = 10;
	find_minmax({ }, min, max);
	assert(min == 5);
	assert(max == 10);
}

void
test_size_colors()
{
	auto colors = choose_colors(3);
	assert(colors.size() == 3);
}

void test_rgb()
{
	auto colors = choose_colors(3);
	assert(colors[0] == "red");
	assert(colors[1] == "green");
	assert(colors[2] == "blue");
}

int
main() 
{
	test_positive();
	test_negative();
	test_similar();
	test_single();
	test_void();
	test_size_colors();
	test_rgb();
}