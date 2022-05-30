#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
#include <windows.h>

#pragma warning(disable : 4996)

using namespace std;

string
make_info_text() {
	stringstream buffer;
	
	DWORD info = 0;
	info = GetVersion();

	DWORD mask = 0x000000ff;
	DWORD version_major = info & mask;

	mask = 0x0000ff00;
	DWORD version_minor = info & mask;
	version_minor = version_minor >> 8;

	DWORD platform = info >> 16;
	DWORD build = platform;

	char comp_name[256];
	unsigned long size = 256;

	GetComputerNameA(comp_name, &size);

	buffer << "<tspan x='10' dy='1em'>Windows v" << version_major << "." << version_minor << " (build " << build << ")</tspan>"
		   << "<tspan x='10' dy='1em'>Computer name: " << comp_name << "</tspan>";

	return buffer.str();
}

void
svg_begin(double width, double height)
{
	cout << "<?xml version='1.0' encoding='UTF-08'?>\n";
	cout << "<svg ";
	cout << "width='" << width << "' ";
	cout << "height='" << height << "' ";
	cout << "viewBox='0 0 " << width << " " << height << "' ";
	cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end() {
	cout << "</svg>\n";
}

void
svg_text(double left, double baseline, string text)
{
	cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>\n";
}

void 
svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black")
{
	cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke = '" << stroke << "' fill='" << fill << "'/>\n";
}

void
show_histogram_svg(const vector<size_t>& bins, const vector<string>& fills)
{
	const size_t IMAGE_WIDTH = 400;
	const size_t IMAGE_HEIGHT = 1000;
	const size_t TEXT_LEFT = 20;
	const size_t TEXT_BASELINE = 20;
	const size_t TEXT_WIDTH = 50;
	const size_t BIN_HEIGHT = 30;
	const size_t BLOCK_WIDTH = 10;

	svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);

	const size_t MAX_BIN_WIDTH = IMAGE_WIDTH - TEXT_WIDTH;

	size_t max_bins_width = bins[0];
	for (size_t bin : bins)
	{
		if (bin > max_bins_width)
		{
			max_bins_width = bin;
		}
	}

	max_bins_width = max_bins_width * BLOCK_WIDTH;

	double top = 0;
	for (size_t i = 0; i < bins.size(); i++)
	{
		double bin_width = BLOCK_WIDTH * bins[i];
		if (max_bins_width >= MAX_BIN_WIDTH)
		{
			bin_width = MAX_BIN_WIDTH * (bin_width / max_bins_width) - 1;
		}

		svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bins[i]));
		svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "black", fills[i]);
		top += BIN_HEIGHT;
	}

	svg_text(TEXT_LEFT, top + TEXT_BASELINE, make_info_text());

	svg_end();
}