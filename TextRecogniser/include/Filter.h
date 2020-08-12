#pragma once
#include <functional>
#include <queue>
#include <list>
#include "Settings.h"
#include "Point.h"
#include "Pixel.h"

static class Filter
{
public:
	inline static Pixel& atPosition(const Pixel* data, size_t RealWidth, size_t offset_x, size_t offset_y)
	{
		return *(const_cast<Pixel*>(data) + offset_y * RealWidth + offset_x);
	}
	inline static Pixel& atPoint(const Pixel* data, size_t RealWidth, Point a)
	{
		return *(const_cast<Pixel*>(data) + a.offset_y * RealWidth + a.offset_x);
	}
	static Pixel GetAverageColour(const Pixel* data, size_t RealHeight, size_t RealWidth)
	{
		unsigned long long R_sum = 0;
		unsigned long long G_sum = 0;
		unsigned long long B_sum = 0;

		Pixel tmp;

		for (size_t offset_y = 0; offset_y < RealHeight; ++offset_y)
			for (size_t offset_x = 0; offset_x < RealWidth; ++offset_x)
			{
				tmp = atPosition(data, RealWidth, offset_x, offset_y);
				R_sum += tmp.R;
				G_sum += tmp.G;
				B_sum += tmp.B;
			}
		return Pixel(std::floor(R_sum / ((unsigned long long)RealHeight * RealWidth)),
			std::floor(G_sum / ((unsigned long long)RealHeight * RealWidth)),
			std::floor(B_sum / ((unsigned long long)RealHeight * RealWidth)));
	}
	static void TransformToBlackAndWhiteForm(const unsigned char* data, size_t RealHeight, size_t RealWidth)
	{
		auto AtThis = std::bind(atPosition, reinterpret_cast<const Pixel*>(data), RealWidth, std::placeholders::_1, std::placeholders::_2);
		volume AverageBrightness = GetAverageColour(reinterpret_cast<const Pixel*>(data), RealHeight, RealWidth).brightness();
		for (size_t offset_y = 0; offset_y < RealHeight; ++offset_y)
			for (size_t offset_x = 0; offset_x < RealWidth; ++offset_x)
			{
				if (AtThis(offset_x, offset_y).brightness() > AverageBrightness)
					AtThis(offset_x, offset_y).SetWhiteWithTransparency();
				else
					AtThis(offset_x, offset_y).SetBlackWithTransparency();
			}
	}
	static void AverageFilter(const unsigned char* data, const size_t RealHeight, const size_t RealWidth)
	{
		Pixel** array = new Pixel * [RealHeight];
		for (int i = 0; i < RealHeight; ++i)
			array[i] = new Pixel[RealWidth];
		auto minusHeight = RealHeight - 1;
		auto minusWidth = RealWidth - 1;
		
		auto AtThis = std::bind(atPosition, reinterpret_cast<const Pixel*>(data), RealWidth, std::placeholders::_1, std::placeholders::_2);
		{
			for (size_t offset_y = 1; offset_y < minusHeight - 1; ++offset_y)
				for (size_t offset_x = 1; offset_x < minusWidth - 1; ++offset_x)
				{
					array[offset_y][offset_x].R = ((unsigned long long)AtThis(offset_x - 1, offset_y - 1).R + AtThis(offset_x, offset_y - 1).R + AtThis(offset_x + 1, offset_y - 1).R
						+ AtThis(offset_x - 1, offset_y).R + AtThis(offset_x, offset_y).R + AtThis(offset_x + 1, offset_y).R
						+ AtThis(offset_x - 1, offset_y + 1).R + AtThis(offset_x, offset_y + 1).R + AtThis(offset_x + 1, offset_y + 1).R) / 9;
					array[offset_y][offset_x].G = ((unsigned long long)AtThis(offset_x - 1, offset_y - 1).G + AtThis(offset_x, offset_y - 1).G + AtThis(offset_x + 1, offset_y - 1).G
						+ AtThis(offset_x - 1, offset_y).G + AtThis(offset_x, offset_y).G + AtThis(offset_x + 1, offset_y).G
						+ AtThis(offset_x - 1, offset_y + 1).G + AtThis(offset_x, offset_y + 1).G + AtThis(offset_x + 1, offset_y + 1).G) / 9;
					array[offset_y][offset_x].B = ((unsigned long long)AtThis(offset_x - 1, offset_y - 1).B + AtThis(offset_x, offset_y - 1).B + AtThis(offset_x + 1, offset_y - 1).B
						+ AtThis(offset_x - 1, offset_y).B + AtThis(offset_x, offset_y).B + AtThis(offset_x + 1, offset_y).B
						+ AtThis(offset_x - 1, offset_y + 1).B + AtThis(offset_x, offset_y + 1).B + AtThis(offset_x + 1, offset_y + 1).B) / 9;
				}
			for (size_t offset_y = 1; offset_y < minusHeight - 1; ++offset_y)
			{
				array[offset_y][0].R = ((unsigned long long)AtThis(0, offset_y - 1).R + AtThis(0 + 1, offset_y - 1).R
					+ AtThis(0, offset_y).R + AtThis(0 + 1, offset_y).R
					+ AtThis(0, offset_y + 1).R + AtThis(0 + 1, offset_y + 1).R) / 6;
				array[offset_y][0].G = ((unsigned long long)AtThis(0, offset_y - 1).G + AtThis(0 + 1, offset_y - 1).G
					+ AtThis(0, offset_y).G + AtThis(0 + 1, offset_y).G
					+ AtThis(0, offset_y + 1).G + AtThis(0 + 1, offset_y + 1).G) / 6;
				array[offset_y][0].B = ((unsigned long long)AtThis(0, offset_y - 1).B + AtThis(0 + 1, offset_y - 1).B
					+ AtThis(0, offset_y).B + AtThis(0 + 1, offset_y).B
					+ AtThis(0, offset_y + 1).B + AtThis(0 + 1, offset_y + 1).B) / 6;
				array[offset_y][minusWidth].R = ((unsigned long long)AtThis(minusWidth - 1, offset_y - 1).R + AtThis(minusWidth, offset_y - 1).R
					+ AtThis(minusWidth - 1, offset_y).R + AtThis(minusWidth, offset_y).R
					+ AtThis(minusWidth - 1, offset_y + 1).R + AtThis(minusWidth, offset_y + 1).R) / 6;
				array[offset_y][minusWidth].G = ((unsigned long long)AtThis(minusWidth - 1, offset_y - 1).G + AtThis(minusWidth, offset_y - 1).G
					+ AtThis(minusWidth - 1, offset_y).G + AtThis(minusWidth, offset_y).G
					+ AtThis(minusWidth - 1, offset_y + 1).G + AtThis(minusWidth, offset_y + 1).G) / 6;
				array[offset_y][minusWidth].B = ((unsigned long long)AtThis(minusWidth - 1, offset_y - 1).B + AtThis(minusWidth, offset_y - 1).B
					+ AtThis(minusWidth - 1, offset_y).B + AtThis(minusWidth, offset_y).B
					+ AtThis(minusWidth - 1, offset_y + 1).B + AtThis(minusWidth, offset_y + 1).B) / 6;
			}
			for (size_t offset_x = 1; offset_x < minusWidth - 1; ++offset_x)
			{
				array[0][offset_x].R = ((unsigned long long)AtThis(offset_x - 1, 0).R + AtThis(offset_x, 0).R + AtThis(offset_x + 1, 0).R
					+ AtThis(offset_x - 1, 0 + 1).R + AtThis(offset_x, 0 + 1).R + AtThis(offset_x + 1, 0 + 1).R) / 6;
				array[0][offset_x].G = ((unsigned long long)AtThis(offset_x - 1, 0).G + AtThis(offset_x, 0).G + AtThis(offset_x + 1, 0).G
					+ AtThis(offset_x - 1, 0 + 1).G + AtThis(offset_x, 0 + 1).G + AtThis(offset_x + 1, 0 + 1).G) / 6;
				array[0][offset_x].B = ((unsigned long long)AtThis(offset_x - 1, 0).B + AtThis(offset_x, 0).B + AtThis(offset_x + 1, 0).B
					+ AtThis(offset_x - 1, 0 + 1).B + AtThis(offset_x, 0 + 1).B + AtThis(offset_x + 1, 0 + 1).B) / 6;
				array[minusHeight][offset_x].R = ((unsigned long long)AtThis(offset_x - 1, minusHeight - 1).R + AtThis(offset_x, minusHeight - 1).R + AtThis(offset_x + 1, minusHeight - 1).R
					+ AtThis(offset_x - 1, minusHeight).R + AtThis(offset_x, minusHeight).R + AtThis(offset_x + 1, minusHeight).R) / 6;
				array[minusHeight][offset_x].G = ((unsigned long long)AtThis(offset_x - 1, minusHeight - 1).G + AtThis(offset_x, minusHeight - 1).G + AtThis(offset_x + 1, minusHeight - 1).G
					+ AtThis(offset_x - 1, minusHeight).G + AtThis(offset_x, minusHeight).G + AtThis(offset_x + 1, minusHeight).G) / 6;
				array[minusHeight][offset_x].B = ((unsigned long long)AtThis(offset_x - 1, minusHeight - 1).B + AtThis(offset_x, minusHeight - 1).B + AtThis(offset_x + 1, minusHeight - 1).B
					+ AtThis(offset_x - 1, minusHeight).B + AtThis(offset_x, minusHeight).B + AtThis(offset_x + 1, minusHeight).B) / 6;
			}
			array[0][0].R = ((unsigned long long)AtThis(0, 0).R + AtThis(0, 1).R
				+ AtThis(1, 0).R + AtThis(1, 1).R) / 4;
			array[minusHeight][0].R = ((unsigned long long)AtThis(0, minusHeight).R + AtThis(1, minusHeight).R
				+ AtThis(0, minusHeight - 1).R + AtThis(1, minusHeight - 1).R) / 4;
			array[0][minusWidth].R = ((unsigned long long)AtThis(minusWidth, 0).R + AtThis(minusWidth - 1, 0).R
				+ AtThis(minusWidth, 1).R + AtThis(minusWidth - 1, 1).R) / 4;
			array[minusHeight][minusWidth].R = ((unsigned long long)AtThis(minusWidth, minusHeight).R + AtThis(minusWidth, minusHeight - 1).R
				+ AtThis(minusWidth - 1, minusHeight).R + AtThis(minusWidth - 1, minusHeight - 1).R) / 4;

			array[0][0].G = ((unsigned long long)AtThis(0, 0).G + AtThis(0, 1).G
				+ AtThis(1, 0).G + AtThis(1, 1).G) / 4;
			array[minusHeight][0].G = ((unsigned long long)AtThis(0, minusHeight).G + AtThis(1, minusHeight).G
				+ AtThis(0, minusHeight - 1).G + AtThis(1, minusHeight - 1).G) / 4;
			array[0][minusWidth].G = ((unsigned long long)AtThis(minusWidth, 0).G + AtThis(minusWidth - 1, 0).G
				+ AtThis(minusWidth, 1).G + AtThis(minusWidth - 1, 1).G) / 4;
			array[minusHeight][minusWidth].G = ((unsigned long long)AtThis(minusWidth, minusHeight).G + AtThis(minusWidth, minusHeight - 1).G
				+ AtThis(minusWidth - 1, minusHeight).G + AtThis(minusWidth - 1, minusHeight - 1).G) / 4;

			array[0][0].B = ((unsigned long long)AtThis(0, 0).B + AtThis(0, 1).B
				+ AtThis(1, 0).B + AtThis(1, 1).B) / 4;
			array[minusHeight][0].B = ((unsigned long long)AtThis(0, minusHeight).B + AtThis(1, minusHeight).B
				+ AtThis(0, minusHeight - 1).B + AtThis(1, minusHeight - 1).B) / 4;
			array[0][minusWidth].B = ((unsigned long long)AtThis(minusWidth, 0).B + AtThis(minusWidth - 1, 0).B
				+ AtThis(minusWidth, 1).B + AtThis(minusWidth - 1, 1).B) / 4;
			array[minusHeight][minusWidth].B = ((unsigned long long)AtThis(minusWidth, minusHeight).B + AtThis(minusWidth, minusHeight - 1).B
				+ AtThis(minusWidth - 1, minusHeight).B + AtThis(minusWidth - 1, minusHeight - 1).B) / 4;
		}
		{
			auto AtArray = [&array](int offset_x, int offset_y)->Pixel& {return array[offset_y][offset_x]; };

			auto i = AtArray(2,2);
			for (size_t offset_y = 1; offset_y < minusHeight - 1; ++offset_y)
				for (size_t offset_x = 1; offset_x < minusWidth - 1; ++offset_x)
				{
					AtThis(offset_x, offset_y) = AtArray(offset_x, offset_y);
					/*AtThis(offset_x,offset_y).R = ((unsigned long long)AtArray(offset_x - 1, offset_y - 1).R + AtArray(offset_x, offset_y - 1).R + AtArray(offset_x + 1, offset_y - 1).R
						+ AtArray(offset_x - 1, offset_y).R	+ AtArray(offset_x, offset_y).R	+ AtArray(offset_x + 1, offset_y).R	
						+ AtArray(offset_x - 1, offset_y + 1).R	+ AtArray(offset_x, offset_y + 1).R	+ AtArray(offset_x + 1, offset_y + 1).R) / 9;
					AtThis(offset_x, offset_y).G = ((unsigned long long)AtArray(offset_x - 1, offset_y - 1).G + AtArray(offset_x, offset_y - 1).G + AtArray(offset_x + 1, offset_y - 1).G
						+ AtArray(offset_x - 1, offset_y).G + AtArray(offset_x, offset_y).G + AtArray(offset_x + 1, offset_y).G
						+ AtArray(offset_x - 1, offset_y + 1).G + AtArray(offset_x, offset_y + 1).G + AtArray(offset_x + 1, offset_y + 1).G) / 9;
					AtThis(offset_x, offset_y).B = ((unsigned long long)AtArray(offset_x - 1, offset_y - 1).B + AtArray(offset_x, offset_y - 1).B + AtArray(offset_x + 1, offset_y - 1).B
						+ AtArray(offset_x - 1, offset_y).B + AtArray(offset_x, offset_y).B + AtArray(offset_x + 1, offset_y).B
						+ AtArray(offset_x - 1, offset_y + 1).B + AtArray(offset_x, offset_y + 1).B + AtArray(offset_x + 1, offset_y + 1).B) / 9;*/
				}
			for (size_t offset_y = 1; offset_y < minusHeight - 1; ++offset_y)
			{
				AtThis(0, offset_y) = AtArray(0, offset_y);
				AtThis(minusWidth, offset_y) = AtArray(minusWidth, offset_y);
				/*AtThis(0, offset_y).R = ((unsigned long long)AtArray(0, offset_y - 1).R + AtArray(0 + 1, offset_y - 1).R
					+ AtArray(0, offset_y).R + AtArray(0 + 1, offset_y).R
					+ AtArray(0, offset_y + 1).R + AtArray(0 + 1, offset_y + 1).R) / 6;
				AtThis(0, offset_y).G = ((unsigned long long)AtArray(0, offset_y - 1).G + AtArray(0 + 1, offset_y - 1).G
					+ AtArray(0, offset_y).G + AtArray(0 + 1, offset_y).G
					+ AtArray(0, offset_y + 1).G + AtArray(0 + 1, offset_y + 1).G) / 6;
				AtThis(0, offset_y).B = ((unsigned long long)AtArray(0, offset_y - 1).B + AtArray(0 + 1, offset_y - 1).B
					+ AtArray(0, offset_y).B + AtArray(0 + 1, offset_y).B
					+ AtArray(0, offset_y + 1).B + AtArray(0 + 1, offset_y + 1).B) / 6;
				AtThis(minusWidth, offset_y).R = ((unsigned long long)AtArray(minusWidth - 1, offset_y - 1).R + AtArray(minusWidth, offset_y - 1).R
					+ AtArray(minusWidth - 1, offset_y).R + AtArray(minusWidth, offset_y).R
					+ AtArray(minusWidth - 1, offset_y + 1).R + AtArray(minusWidth, offset_y + 1).R) / 6;
				AtThis(minusWidth, offset_y).G = ((unsigned long long)AtArray(minusWidth - 1, offset_y - 1).G + AtArray(minusWidth, offset_y - 1).G
					+ AtArray(minusWidth - 1, offset_y).G + AtArray(minusWidth, offset_y).G
					+ AtArray(minusWidth - 1, offset_y + 1).G + AtArray(minusWidth, offset_y + 1).G) / 6;
				AtThis(minusWidth, offset_y).B = ((unsigned long long)AtArray(minusWidth - 1, offset_y - 1).B + AtArray(minusWidth, offset_y - 1).B
					+ AtArray(minusWidth - 1, offset_y).B + AtArray(minusWidth, offset_y).B
					+ AtArray(minusWidth - 1, offset_y + 1).B + AtArray(minusWidth, offset_y + 1).B) /6;*/
			}
			for (size_t offset_x = 1; offset_x < minusWidth - 1; ++offset_x)
			{
				AtThis(offset_x, 0) = AtArray(offset_x, 0);
				AtThis(offset_x, minusHeight) = AtArray(offset_x, minusHeight);
				/*AtThis(offset_x, 0).R = ((unsigned long long)AtArray(offset_x - 1, 0).R + AtArray(offset_x, 0).R + AtArray(offset_x + 1, 0).R
					+ AtArray(offset_x - 1, 0 + 1).R + AtArray(offset_x, 0 + 1).R + AtArray(offset_x + 1, 0 + 1).R) / 6;
				AtThis(offset_x, 0).G = ((unsigned long long)AtArray(offset_x - 1, 0).G + AtArray(offset_x, 0).G + AtArray(offset_x + 1, 0).G
					+ AtArray(offset_x - 1, 0 + 1).G + AtArray(offset_x, 0 + 1).G + AtArray(offset_x + 1, 0 + 1).G) / 6;
				AtThis(offset_x, 0).B = ((unsigned long long)AtArray(offset_x - 1, 0).B + AtArray(offset_x, 0).B + AtArray(offset_x + 1, 0).B
					+ AtArray(offset_x - 1, 0 + 1).B + AtArray(offset_x, 0 + 1).B + AtArray(offset_x + 1, 0 + 1).B) / 6;
				AtThis(offset_x, minusHeight).R = ((unsigned long long)AtArray(offset_x - 1, minusHeight - 1).R + AtArray(offset_x, minusHeight - 1).R + AtArray(offset_x + 1, minusHeight - 1).R
					+ AtArray(offset_x - 1, minusHeight).R + AtArray(offset_x, minusHeight).R + AtArray(offset_x + 1, minusHeight).R) / 6;
				AtThis(offset_x, minusHeight).G = ((unsigned long long)AtArray(offset_x - 1, minusHeight - 1).G + AtArray(offset_x, minusHeight - 1).G + AtArray(offset_x + 1, minusHeight - 1).G
					+ AtArray(offset_x - 1, minusHeight).G + AtArray(offset_x, minusHeight).G + AtArray(offset_x + 1, minusHeight).G) / 6;
				AtThis(offset_x, minusHeight).B = ((unsigned long long)AtArray(offset_x - 1, minusHeight - 1).B + AtArray(offset_x, minusHeight - 1).B + AtArray(offset_x + 1, minusHeight - 1).B
					+ AtArray(offset_x - 1, minusHeight).B + AtArray(offset_x, minusHeight).B + AtArray(offset_x + 1, minusHeight).B) / 6;*/
			}
			AtThis(0, 0) = AtArray(0,0);
			AtThis(0, minusHeight) = AtArray(0, minusHeight);
			AtThis(minusWidth, 0) = AtArray(minusWidth, 0);
			AtThis(minusWidth, minusHeight) = AtArray(minusWidth, minusHeight);
			/*AtThis(0, 0).R = ((unsigned long long)AtArray(0, 0).R + AtArray(0, 1).R
				+ AtArray(1, 0).R + AtArray(1, 1).R) / 4;
			AtThis(0, minusHeight).R = ((unsigned long long)AtArray(0, minusHeight).R + AtArray(1, minusHeight).R
				+ AtArray(0, minusHeight - 1).R + AtArray(1, minusHeight - 1).R) / 4;
			AtThis(minusWidth, 0).R = ((unsigned long long)AtArray(minusWidth, 0).R + AtArray(minusWidth - 1, 0).R
				+ AtArray(minusWidth, 1).R + AtArray(minusWidth - 1, 1).R) / 4;
			AtThis(minusWidth, minusHeight).R = ((unsigned long long)AtArray(minusWidth, minusHeight).R + AtArray(minusWidth, minusHeight - 1).R
				+ AtArray(minusWidth - 1, minusHeight).R + AtArray(minusWidth - 1, minusHeight - 1).R) / 4;

			AtThis(0, 0).G = ((unsigned long long)AtArray(0, 0).G + AtArray(0, 1).G
				+ AtArray(1, 0).G + AtArray(1, 1).G) / 4;
			AtThis(0, minusHeight).G = ((unsigned long long)AtArray(0, minusHeight).G + AtArray(1, minusHeight).G
				+ AtArray(0, minusHeight - 1).G + AtArray(1, minusHeight - 1).G) / 4;
			AtThis(minusWidth, 0).G = ((unsigned long long)AtArray(minusWidth, 0).G + AtArray(minusWidth - 1, 0).G
				+ AtArray(minusWidth, 1).G + AtArray(minusWidth - 1, 1).G) / 4;
			AtThis(minusWidth, minusHeight).G = ((unsigned long long)AtArray(minusWidth, minusHeight).G + AtArray(minusWidth, minusHeight - 1).G
				+ AtArray(minusWidth - 1, minusHeight).G + AtArray(minusWidth - 1, minusHeight - 1).G) / 4;

			AtThis(0, 0).B = ((unsigned long long)AtArray(0, 0).B + AtArray(0, 1).B
				+ AtArray(1, 0).B + AtArray(1, 1).B) / 4;
			AtThis(0, minusHeight).B = ((unsigned long long)AtArray(0, minusHeight).B + AtArray(1, minusHeight).B
				+ AtArray(0, minusHeight - 1).B + AtArray(1, minusHeight - 1).B) / 4;
			AtThis(minusWidth, 0).B = ((unsigned long long)AtArray(minusWidth, 0).B + AtArray(minusWidth - 1, 0).B
				+ AtArray(minusWidth, 1).B + AtArray(minusWidth - 1, 1).B) / 4;
			AtThis(minusWidth, minusHeight).B = ((unsigned long long)AtArray(minusWidth, minusHeight).B + AtArray(minusWidth, minusHeight - 1).B
				+ AtArray(minusWidth - 1, minusHeight).B + AtArray(minusWidth - 1, minusHeight - 1).B) / 4;*/

		}
				
		for (int i = 0; i < RealHeight; ++i)
			delete[] array[i];
		delete[] array;
	}
	inline static void Negative(const unsigned char* data, const size_t RealHeight, const size_t RealWidth)
	{
		auto AtThis = std::bind(atPosition, reinterpret_cast<const Pixel*>(data), RealWidth, std::placeholders::_1, std::placeholders::_2);
		for (size_t offset_y = 0; offset_y < RealHeight; ++offset_y)
			for (size_t offset_x = 0; offset_x < RealWidth; ++offset_x)
				AtThis(offset_x, offset_y).SetNegative();
	}
	inline static bool isDarkImage(const unsigned char* data, const size_t RealHeight, const size_t RealWidth)
	{
		return GetAverageColour(reinterpret_cast<const Pixel*>(data), RealHeight, RealWidth).brightness() < 127;
	}
	inline static bool isBrightImage(const unsigned char* data, const size_t RealHeight, const size_t RealWidth)
	{
		return GetAverageColour(reinterpret_cast<const Pixel*>(data), RealHeight, RealWidth).brightness() >= 127;
	}
};

