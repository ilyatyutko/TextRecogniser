#pragma once
#include <functional>
#include <queue>
#include <list>
#include "ImageTransformer.h"
#include "Settings.h"
#include "Figure.h"
#include "Point.h"
class Symbol;
static class Filter
{
private:
	inline static Pixel& atPosition(Pixel* data, size_t width, size_t offset_x, size_t offset_y)
	{
		return *(data + offset_y * width + offset_x);
	}
	inline static Pixel& atPoint(Pixel* data, size_t width, Point a)
	{
		return *(data + a.offset_y * width + a.offset_x);
	}
	friend class Symbol;
	friend std::ostream& operator<< (std::ostream& out, const Symbol& source);
public:
	static Pixel GetAverageColour(Pixel* data, size_t height, size_t width)
	{
		unsigned long long R_sum = 0;
		unsigned long long G_sum = 0;
		unsigned long long B_sum = 0;

		Pixel tmp;

		for (size_t offset_y = 0; offset_y < height; ++offset_y)
			for (size_t offset_x = 0; offset_x < width; ++offset_x)
			{
				tmp = atPosition(data, width, offset_x, offset_y);
				R_sum += tmp.R;
				G_sum += tmp.G;
				B_sum += tmp.B;
			}
		return Pixel(std::floor(R_sum / ((unsigned long long)height * width)),
			std::floor(G_sum / ((unsigned long long)height * width)),
			std::floor(B_sum / ((unsigned long long)height * width)));
	}
	static void TransformToBlackAndWhiteForm(unsigned char* data, size_t height, size_t width)
	{
		auto AtThis = std::bind(atPosition, reinterpret_cast<Pixel*>(data), width, std::placeholders::_1, std::placeholders::_2);
		volume AverageBrightness = GetAverageColour(reinterpret_cast<Pixel*>(data), height, width).brightness();
		for (size_t offset_y = 0; offset_y < height; ++offset_y)
			for (size_t offset_x = 0; offset_x < width; ++offset_x)
			{
				if (AtThis(offset_x, offset_y).brightness() > AverageBrightness)
					AtThis(offset_x, offset_y) = Color::White;
				else
					AtThis(offset_x, offset_y) = Color::Black;
			}
	}
	static void AverageFilter(unsigned char* data, const size_t height, const size_t width)
	{
		Pixel** array = new Pixel * [height];
		for (int i = 0; i < height; ++i)
			array[i] = new Pixel[width];
		auto minusHeight = height - 1;
		auto minusWidth = width - 1;
		
		auto AtArray =  [&array](int offset_x, int offset_y)->Pixel& {return array[offset_y][offset_x]; };
		auto AtThis = std::bind(atPosition, reinterpret_cast<Pixel*>(data), width, std::placeholders::_1, std::placeholders::_2);
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
					+ AtThis(0, offset_y + 1).R + AtThis(0 + 1, offset_y + 1).R) / 9;
				array[offset_y][0].G = ((unsigned long long)AtThis(0, offset_y - 1).G + AtThis(0 + 1, offset_y - 1).G
					+ AtThis(0, offset_y).G + AtThis(0 + 1, offset_y).G
					+ AtThis(0, offset_y + 1).G + AtThis(0 + 1, offset_y + 1).G) / 9;
				array[offset_y][0].B = ((unsigned long long)AtThis(0, offset_y - 1).B + AtThis(0 + 1, offset_y - 1).B
					+ AtThis(0, offset_y).B + AtThis(0 + 1, offset_y).B
					+ AtThis(0, offset_y + 1).B + AtThis(0 + 1, offset_y + 1).B) / 9;
				array[offset_y][minusWidth].R = ((unsigned long long)AtThis(minusWidth - 1, offset_y - 1).R + AtThis(minusWidth, offset_y - 1).R
					+ AtThis(minusWidth - 1, offset_y).R + AtThis(minusWidth, offset_y).R
					+ AtThis(minusWidth - 1, offset_y + 1).R + AtThis(minusWidth, offset_y + 1).R) / 9;
				array[offset_y][minusWidth].G = ((unsigned long long)AtThis(minusWidth - 1, offset_y - 1).G + AtThis(minusWidth, offset_y - 1).G
					+ AtThis(minusWidth - 1, offset_y).G + AtThis(minusWidth, offset_y).G
					+ AtThis(minusWidth - 1, offset_y + 1).G + AtThis(minusWidth, offset_y + 1).G) / 9;
				array[offset_y][minusWidth].B = ((unsigned long long)AtThis(minusWidth - 1, offset_y - 1).B + AtThis(minusWidth, offset_y - 1).B
					+ AtThis(minusWidth - 1, offset_y).B + AtThis(minusWidth, offset_y).B
					+ AtThis(minusWidth - 1, offset_y + 1).B + AtThis(minusWidth, offset_y + 1).B) / 9;
			}
			for (size_t offset_x = 1; offset_x < minusWidth - 1; ++offset_x)
			{
				array[0][offset_x].R = ((unsigned long long)AtThis(offset_x - 1, 0).R + AtThis(offset_x, 0).R + AtThis(offset_x + 1, 0).R
					+ AtThis(offset_x - 1, 0 + 1).R + AtThis(offset_x, 0 + 1).R + AtThis(offset_x + 1, 0 + 1).R) / 9;
				array[0][offset_x].G = ((unsigned long long)AtThis(offset_x - 1, 0).G + AtThis(offset_x, 0).G + AtThis(offset_x + 1, 0).G
					+ AtThis(offset_x - 1, 0 + 1).G + AtThis(offset_x, 0 + 1).G + AtThis(offset_x + 1, 0 + 1).G) / 9;
				array[0][offset_x].B = ((unsigned long long)AtThis(offset_x - 1, 0).B + AtThis(offset_x, 0).B + AtThis(offset_x + 1, 0).B
					+ AtThis(offset_x - 1, 0 + 1).B + AtThis(offset_x, 0 + 1).B + AtThis(offset_x + 1, 0 + 1).B) / 9;
				array[minusHeight][offset_x].R = ((unsigned long long)AtThis(offset_x - 1, minusHeight - 1).R + AtThis(offset_x, minusHeight - 1).R + AtThis(offset_x + 1, minusHeight - 1).R
					+ AtThis(offset_x - 1, minusHeight).R + AtThis(offset_x, minusHeight).R + AtThis(offset_x + 1, minusHeight).R) / 9;
				array[minusHeight][offset_x].G = ((unsigned long long)AtThis(offset_x - 1, minusHeight - 1).G + AtThis(offset_x, minusHeight - 1).G + AtThis(offset_x + 1, minusHeight - 1).G
					+ AtThis(offset_x - 1, minusHeight).G + AtThis(offset_x, minusHeight).G + AtThis(offset_x + 1, minusHeight).G) / 9;
				array[minusHeight][offset_x].B = ((unsigned long long)AtThis(offset_x - 1, minusHeight - 1).B + AtThis(offset_x, minusHeight - 1).B + AtThis(offset_x + 1, minusHeight - 1).B
					+ AtThis(offset_x - 1, minusHeight).B + AtThis(offset_x, minusHeight).B + AtThis(offset_x + 1, minusHeight).B) / 9;
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
			for (size_t offset_y = 1; offset_y < minusHeight - 1; ++offset_y)
				for (size_t offset_x = 1; offset_x < minusWidth - 1; ++offset_x)
				{
					AtThis(offset_x,offset_y).R = ((unsigned long long)AtArray(offset_x - 1, offset_y - 1).R
						+ AtArray(offset_x, offset_y - 1).R
						+ AtArray(offset_x + 1, offset_y - 1).R
						+ AtArray(offset_x - 1, offset_y).R
						+ AtArray(offset_x, offset_y).R
						+ AtArray(offset_x + 1, offset_y).R
						+ AtArray(offset_x - 1, offset_y + 1).R
						+ AtArray(offset_x, offset_y + 1).R
						+ AtArray(offset_x + 1, offset_y + 1).R) / 9;
					AtThis(offset_x, offset_y).G = ((unsigned long long)AtArray(offset_x - 1, offset_y - 1).G + AtArray(offset_x, offset_y - 1).G + AtArray(offset_x + 1, offset_y - 1).G
						+ AtArray(offset_x - 1, offset_y).G + AtArray(offset_x, offset_y).G + AtArray(offset_x + 1, offset_y).G
						+ AtArray(offset_x - 1, offset_y + 1).G + AtArray(offset_x, offset_y + 1).G + AtArray(offset_x + 1, offset_y + 1).G) / 9;
					AtThis(offset_x, offset_y).B = ((unsigned long long)AtArray(offset_x - 1, offset_y - 1).B + AtArray(offset_x, offset_y - 1).B + AtArray(offset_x + 1, offset_y - 1).B
						+ AtArray(offset_x - 1, offset_y).B + AtArray(offset_x, offset_y).B + AtArray(offset_x + 1, offset_y).B
						+ AtArray(offset_x - 1, offset_y + 1).B + AtArray(offset_x, offset_y + 1).B + AtArray(offset_x + 1, offset_y + 1).B) / 9;
				}
			for (size_t offset_y = 1; offset_y < minusHeight - 1; ++offset_y)
			{
				AtThis(0, offset_y).R = ((unsigned long long)AtArray(0, offset_y - 1).R + AtArray(0 + 1, offset_y - 1).R
					+ AtArray(0, offset_y).R + AtArray(0 + 1, offset_y).R
					+ AtArray(0, offset_y + 1).R + AtArray(0 + 1, offset_y + 1).R) / 9;
				AtThis(0, offset_y).G = ((unsigned long long)AtArray(0, offset_y - 1).G + AtArray(0 + 1, offset_y - 1).G
					+ AtArray(0, offset_y).G + AtArray(0 + 1, offset_y).G
					+ AtArray(0, offset_y + 1).G + AtArray(0 + 1, offset_y + 1).G) / 9;
				AtThis(0, offset_y).B = ((unsigned long long)AtArray(0, offset_y - 1).B + AtArray(0 + 1, offset_y - 1).B
					+ AtArray(0, offset_y).B + AtArray(0 + 1, offset_y).B
					+ AtArray(0, offset_y + 1).B + AtArray(0 + 1, offset_y + 1).B) / 9;
				AtThis(minusWidth, offset_y).R = ((unsigned long long)AtArray(minusWidth - 1, offset_y - 1).R + AtArray(minusWidth, offset_y - 1).R
					+ AtArray(minusWidth - 1, offset_y).R + AtArray(minusWidth, offset_y).R
					+ AtArray(minusWidth - 1, offset_y + 1).R + AtArray(minusWidth, offset_y + 1).R) / 9;
				AtThis(minusWidth, offset_y).G = ((unsigned long long)AtArray(minusWidth - 1, offset_y - 1).G + AtArray(minusWidth, offset_y - 1).G
					+ AtArray(minusWidth - 1, offset_y).G + AtArray(minusWidth, offset_y).G
					+ AtArray(minusWidth - 1, offset_y + 1).G + AtArray(minusWidth, offset_y + 1).G) / 9;
				AtThis(minusWidth, offset_y).B = ((unsigned long long)AtArray(minusWidth - 1, offset_y - 1).B + AtArray(minusWidth, offset_y - 1).B
					+ AtArray(minusWidth - 1, offset_y).B + AtArray(minusWidth, offset_y).B
					+ AtArray(minusWidth - 1, offset_y + 1).B + AtArray(minusWidth, offset_y + 1).B) / 9;
			}
			for (size_t offset_x = 1; offset_x < minusWidth - 1; ++offset_x)
			{
				AtThis(offset_x, 0).R = ((unsigned long long)AtArray(offset_x - 1, 0).R + AtArray(offset_x, 0).R + AtArray(offset_x + 1, 0).R
					+ AtArray(offset_x - 1, 0 + 1).R + AtArray(offset_x, 0 + 1).R + AtArray(offset_x + 1, 0 + 1).R) / 9;
				AtThis(offset_x, 0).G = ((unsigned long long)AtArray(offset_x - 1, 0).G + AtArray(offset_x, 0).G + AtArray(offset_x + 1, 0).G
					+ AtArray(offset_x - 1, 0 + 1).G + AtArray(offset_x, 0 + 1).G + AtArray(offset_x + 1, 0 + 1).G) / 9;
				AtThis(offset_x, 0).B = ((unsigned long long)AtArray(offset_x - 1, 0).B + AtArray(offset_x, 0).B + AtArray(offset_x + 1, 0).B
					+ AtArray(offset_x - 1, 0 + 1).B + AtArray(offset_x, 0 + 1).B + AtArray(offset_x + 1, 0 + 1).B) / 9;
				AtThis(offset_x, minusHeight).R = ((unsigned long long)AtArray(offset_x - 1, minusHeight - 1).R + AtArray(offset_x, minusHeight - 1).R + AtArray(offset_x + 1, minusHeight - 1).R
					+ AtArray(offset_x - 1, minusHeight).R + AtArray(offset_x, minusHeight).R + AtArray(offset_x + 1, minusHeight).R) / 9;
				AtThis(offset_x, minusHeight).G = ((unsigned long long)AtArray(offset_x - 1, minusHeight - 1).G + AtArray(offset_x, minusHeight - 1).G + AtArray(offset_x + 1, minusHeight - 1).G
					+ AtArray(offset_x - 1, minusHeight).G + AtArray(offset_x, minusHeight).G + AtArray(offset_x + 1, minusHeight).G) / 9;
				AtThis(offset_x, minusHeight).B = ((unsigned long long)AtArray(offset_x - 1, minusHeight - 1).B + AtArray(offset_x, minusHeight - 1).B + AtArray(offset_x + 1, minusHeight - 1).B
					+ AtArray(offset_x - 1, minusHeight).B + AtArray(offset_x, minusHeight).B + AtArray(offset_x + 1, minusHeight).B) / 9;
			}
			AtThis(0, 0).R = ((unsigned long long)AtArray(0, 0).R + AtArray(0, 1).R
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
				+ AtArray(minusWidth - 1, minusHeight).B + AtArray(minusWidth - 1, minusHeight - 1).B) / 4;

		}
				
	}
	inline static void Negative(unsigned char* data, const size_t height, const size_t width)
	{
		auto AtThis = std::bind(atPosition, reinterpret_cast<Pixel*>(data), width, std::placeholders::_1, std::placeholders::_2);
		for (size_t offset_y = 0; offset_y < height; ++offset_y)
			for (size_t offset_x = 0; offset_x < width; ++offset_x)
				AtThis(offset_x, offset_y).SetNegative();
	}
	inline static bool isDarkImage(unsigned char* data, const size_t height, const size_t width)
	{
		return GetAverageColour(reinterpret_cast<Pixel*>(data), height, width).brightness() < 127;
	}
	inline static bool isBrightImage(unsigned char* data, const size_t height, const size_t width)
	{
		return GetAverageColour(reinterpret_cast<Pixel*>(data), height, width).brightness() >= 127;
	}
	inline static Figure CatchFigure(unsigned char* data, bool** FlagWereLookedArray, const size_t height, const size_t width, int offset_x, int offset_y)
	{
		auto AtData = std::bind(atPoint, reinterpret_cast<Pixel*>(data), width, std::placeholders::_1);
		std::queue<Point> ToVisit;
		std::list<Point> ToRemember;

		ToVisit.push(Point(offset_x,offset_y));

		while (!ToVisit.empty())
		{
			auto target = ToVisit.front();
							ToVisit.pop();

			if (target.offset_x > -1)
			{
				if (target.offset_y > -1)
				{
					if (Pixel::colorDifference(AtData(target.UpLeft()), AtData(target))
						< Settings::BorderSeparationColorDifference
						&& !FlagWereLookedArray[offset_y - 1][offset_x - 1])
					{
						ToVisit.push(target.UpLeft());
						ToRemember.push_back(target.UpLeft());
						FlagWereLookedArray[offset_y - 1][offset_x - 1] = true;
					}
				}
				///
				{	
					if (Pixel::colorDifference(AtData(target.Left()), AtData(target))
						< Settings::BorderSeparationColorDifference
						&& !FlagWereLookedArray[offset_y][offset_x - 1])
					{
						ToVisit.push(target.Left());
						ToRemember.push_back(target.Left());
						FlagWereLookedArray[offset_y][offset_x - 1] = true;
					}
				}
				///
				if (target.offset_y < (height - 1))
				{
					if (Pixel::colorDifference(AtData(target.DownLeft()), AtData(target))
						< Settings::BorderSeparationColorDifference
						&& !FlagWereLookedArray[offset_y + 1][offset_x - 1])
					{
						ToVisit.push(target.DownLeft());
						ToRemember.push_back(target.DownLeft());
						FlagWereLookedArray[offset_y + 1][offset_x - 1] = true;
					}
				}
			}
			///
			{
				if (target.offset_y > -1)
				{
					if (Pixel::colorDifference(AtData(target.Up()), AtData(target))
						< Settings::BorderSeparationColorDifference
						&& !FlagWereLookedArray[offset_y - 1][offset_x])
					{
						ToVisit.push(target.Up());
						ToRemember.push_back(target.Up());
						FlagWereLookedArray[offset_y - 1][offset_x] = true;
					}
				}
				///
				if (target.offset_y < (height - 1))
				{
					if (Pixel::colorDifference(AtData(target.Down()), AtData(target))
						< Settings::BorderSeparationColorDifference
						&& !FlagWereLookedArray[offset_y + 1][offset_x])
					{
						ToVisit.push(target.Down());
						ToRemember.push_back(target.Down());
						FlagWereLookedArray[offset_y + 1][offset_x] = true;
					}
				}
			}
			///
			if (target.offset_x < (width - 1))
			{
				if (target.offset_y > -1)
				{
					if (Pixel::colorDifference(AtData(target.UpRight()), AtData(target))
						< Settings::BorderSeparationColorDifference
						&& !FlagWereLookedArray[offset_y - 1][offset_x + 1])
					{
						ToVisit.push(target.UpRight());
						ToRemember.push_back(target.UpRight());
						FlagWereLookedArray[offset_y - 1][offset_x + 1] = true;
					}
				}
				///
				if (Pixel::colorDifference(AtData(target.Right()), AtData(target))
					< Settings::BorderSeparationColorDifference
					&& !FlagWereLookedArray[offset_y][offset_x + 1])
				{
					ToVisit.push(target.Right());
					ToRemember.push_back(target.Right());
					FlagWereLookedArray[offset_y][offset_x + 1] = true;
				}
				///
				if (target.offset_y < (height - 1))
				{
					if (Pixel::colorDifference(AtData(target.DownRight()), AtData(target))
						< Settings::BorderSeparationColorDifference
						&& !FlagWereLookedArray[offset_y + 1][offset_x + 1])
					{
						ToVisit.push(target.DownRight());
						ToRemember.push_back(target.DownRight());
						FlagWereLookedArray[offset_y + 1][offset_x + 1] = true;
					}
				}
			}
		}

		size_t minX = offset_x;
		size_t maxX = offset_x;
		size_t minY = offset_y;
		size_t maxY = offset_y;

		for (auto itr = ToRemember.begin(); itr != ToRemember.end(); ++itr)
		{
			if (itr->offset_x < minX)
				minX = itr->offset_x;
			else
				if (itr->offset_x > maxX)
					maxX = itr->offset_x;

			if (itr->offset_y < minY)
				minY = itr->offset_y;
			else
				if (itr->offset_y > maxY)
					maxY = itr->offset_y;
		}

		size_t width_sym = maxX - minX + 1;
		size_t height_sym = maxY - minY + 1;

		auto size = width_sym * height_sym;
		Pixel* SymbolImage = new Pixel[size];
		for (int i = 0; i < size; ++i)
			SymbolImage[i] = Color::White;

		auto AtImage = [&SymbolImage, width_sym](Point a)->Pixel&
					{return SymbolImage[a.offset_x + a.offset_y * width_sym]; };
		for (auto itr = ToRemember.begin(); itr != ToRemember.end(); ++itr)
			AtImage(*itr) = Color::Black;



	}
};

