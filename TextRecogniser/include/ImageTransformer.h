#pragma once
#include <cmath>
#include <vector>
#include <iostream>
#include <iomanip>

using volume = unsigned char;
namespace
{
	struct Pixel
	{
		volume R;
		volume G;
		volume B;
		volume T = 255;

		inline volume brightness() const
		{
			return std::round((double)(R + G + B) / 3 * T / 256);
		}

		Pixel(volume R_set, volume G_set, volume B_set)
			:R(R_set)
			,G(G_set)
			,B(B_set)
		{}
		Pixel()
			:R(0)
			,G(0)
			,B(0)
		{}
	};
	Pixel Black = Pixel(0,0,0);
	Pixel White = Pixel(255,255,255);
}
class ImageTransformer
{
public:
	size_t width;
	size_t height;
	Pixel* data;
	inline Pixel& at(size_t y, size_t x) const
	{
		return *(data + y * width + x);
	}
	Pixel averageColour() const
	{
		unsigned long long R_sum = 0;
		unsigned long long G_sum = 0;
		unsigned long long B_sum = 0;

		Pixel tmp;

		for(int y = 0; y < height; ++y)
			for (int x = 0; x < width; ++x)
			{
				tmp = this->at(y,x);
				R_sum += tmp.R;
				G_sum += tmp.G;
				B_sum += tmp.B;
			}
		return Pixel(std::round(R_sum / ((unsigned long long)height * width)),
					 std::round(G_sum / ((unsigned long long)height * width)),
					 std::round(B_sum / ((unsigned long long)height * width)));
	}
	void SimplifyTo_Black_And_White_Form()
	{
		volume AverageBrightness = averageColour().brightness();
		for (int y = 0; y < height; ++y)
			for (int x = 0; x < width; ++x)
			{
				if (this->at(y, x).brightness() > AverageBrightness)
					this->at(y, x) =  White;
				else
					this->at(y, x) = Black;
			}
	}
	std::vector<bool> SimplifyTo_Binary_Form() const
	{
		std::vector<bool> result;
		result.reserve(height * width);

		volume AverageBrightness = averageColour().brightness();
		for (int y = 0; y < height; ++y)
			for (int x = 0; x < width; ++x)
			{
				if (this->at(y, x).brightness() > AverageBrightness)
					result.push_back(false);
				else
					result.push_back(true);
			}
		return result;
	}
	void JustCoolFilter(volume FilterPower)
	{
		volume AverageBrightness = averageColour().brightness();
		for (int y = 0; y < height; ++y)
			for (int x = 0; x < width; ++x)
				this->at(y, x) = Pixel(   (y % 256) * FilterPower / 256   * this->at(y, x).R % 256
										, (x % 256) * FilterPower / 256   * this->at(y, x).G % 256
										,((y + x) % 256) * FilterPower / 256 * this->at(y, x).R % 256);
	}

	ImageTransformer(unsigned char* data_set, size_t height_set, size_t width_set)
		:data(reinterpret_cast<Pixel*>(data_set))
		, height(height_set)
		, width(width_set)
	{}
	ImageTransformer() = delete;
};

