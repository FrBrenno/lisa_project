#pragma once

#include <vector>

class Image{
	std::vector<std::vector<unsigned int>> pixels;

public:
	Image(int width, int height);
	~Image();

	void setPixel(int x, int y, unsigned char greyLevel);
	void save(const char* filename);
};
