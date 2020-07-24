#pragma once
#include <functional>
#include <queue>
#include <list>
#include "ImageTransformer.h"
#include "Settings.h"
#include "Figure.h"
#include "Point.h"
static class Filter
{
private:
	inline static Pixel& atPosition(Pixel* data, size_t width, size_t x, size_t y)
	{
		return *(data + y * width + x);
	}
	inline static Pixel& atPoint(Pixel* data, size_t width, Point a)
	{
		return *(data + a.y * width + a.x);
	}
public:
	static Pixel GetAverageColour(Pixel* data, size_t height, size_t width)
	{
		unsigned long long R_sum = 0;
		unsigned long long G_sum = 0;
		unsigned long long B_sum = 0;

		Pixel tmp;

		for (size_t y = 0; y < height; ++y)
			for (size_t x = 0; x < width; ++x)
			{
				tmp = atPosition(data, width, x, y);
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
		for (size_t y = 0; y < height; ++y)
			for (size_t x = 0; x < width; ++x)
			{
				if (AtThis(x, y).brightness() > AverageBrightness)
					AtThis(x, y) = Color::White;
				else
					AtThis(x, y) = Color::Black;
			}
	}
	static void AverageFilter(unsigned char* data, const size_t height, const size_t width)
	{
		Pixel** array = new Pixel * [height];
		for (int i = 0; i < height; ++i)
			array[i] = new Pixel[width];
		auto minusHeight = height - 1;
		auto minusWidth = width - 1;
		
		auto AtArray =  [&array](int x, int y)->Pixel& {return array[y][x]; };
		auto AtThis = std::bind(atPosition, reinterpret_cast<Pixel*>(data), width, std::placeholders::_1, std::placeholders::_2);
		{
			for (size_t y = 1; y < minusHeight - 1; ++y)
				for (size_t x = 1; x < minusWidth - 1; ++x)
				{
					array[y][x].R = ((unsigned long long)AtThis(x - 1, y - 1).R + AtThis(x, y - 1).R + AtThis(x + 1, y - 1).R
						+ AtThis(x - 1, y).R + AtThis(x, y).R + AtThis(x + 1, y).R
						+ AtThis(x - 1, y + 1).R + AtThis(x, y + 1).R + AtThis(x + 1, y + 1).R) / 9;
					array[y][x].G = ((unsigned long long)AtThis(x - 1, y - 1).G + AtThis(x, y - 1).G + AtThis(x + 1, y - 1).G
						+ AtThis(x - 1, y).G + AtThis(x, y).G + AtThis(x + 1, y).G
						+ AtThis(x - 1, y + 1).G + AtThis(x, y + 1).G + AtThis(x + 1, y + 1).G) / 9;
					array[y][x].B = ((unsigned long long)AtThis(x - 1, y - 1).B + AtThis(x, y - 1).B + AtThis(x + 1, y - 1).B
						+ AtThis(x - 1, y).B + AtThis(x, y).B + AtThis(x + 1, y).B
						+ AtThis(x - 1, y + 1).B + AtThis(x, y + 1).B + AtThis(x + 1, y + 1).B) / 9;
				}
			for (size_t y = 1; y < minusHeight - 1; ++y)
			{
				array[y][0].R = ((unsigned long long)AtThis(0, y - 1).R + AtThis(0 + 1, y - 1).R
					+ AtThis(0, y).R + AtThis(0 + 1, y).R
					+ AtThis(0, y + 1).R + AtThis(0 + 1, y + 1).R) / 9;
				array[y][0].G = ((unsigned long long)AtThis(0, y - 1).G + AtThis(0 + 1, y - 1).G
					+ AtThis(0, y).G + AtThis(0 + 1, y).G
					+ AtThis(0, y + 1).G + AtThis(0 + 1, y + 1).G) / 9;
				array[y][0].B = ((unsigned long long)AtThis(0, y - 1).B + AtThis(0 + 1, y - 1).B
					+ AtThis(0, y).B + AtThis(0 + 1, y).B
					+ AtThis(0, y + 1).B + AtThis(0 + 1, y + 1).B) / 9;
				array[y][minusWidth].R = ((unsigned long long)AtThis(minusWidth - 1, y - 1).R + AtThis(minusWidth, y - 1).R
					+ AtThis(minusWidth - 1, y).R + AtThis(minusWidth, y).R
					+ AtThis(minusWidth - 1, y + 1).R + AtThis(minusWidth, y + 1).R) / 9;
				array[y][minusWidth].G = ((unsigned long long)AtThis(minusWidth - 1, y - 1).G + AtThis(minusWidth, y - 1).G
					+ AtThis(minusWidth - 1, y).G + AtThis(minusWidth, y).G
					+ AtThis(minusWidth - 1, y + 1).G + AtThis(minusWidth, y + 1).G) / 9;
				array[y][minusWidth].B = ((unsigned long long)AtThis(minusWidth - 1, y - 1).B + AtThis(minusWidth, y - 1).B
					+ AtThis(minusWidth - 1, y).B + AtThis(minusWidth, y).B
					+ AtThis(minusWidth - 1, y + 1).B + AtThis(minusWidth, y + 1).B) / 9;
			}
			for (size_t x = 1; x < minusWidth - 1; ++x)
			{
				array[0][x].R = ((unsigned long long)AtThis(x - 1, 0).R + AtThis(x, 0).R + AtThis(x + 1, 0).R
					+ AtThis(x - 1, 0 + 1).R + AtThis(x, 0 + 1).R + AtThis(x + 1, 0 + 1).R) / 9;
				array[0][x].G = ((unsigned long long)AtThis(x - 1, 0).G + AtThis(x, 0).G + AtThis(x + 1, 0).G
					+ AtThis(x - 1, 0 + 1).G + AtThis(x, 0 + 1).G + AtThis(x + 1, 0 + 1).G) / 9;
				array[0][x].B = ((unsigned long long)AtThis(x - 1, 0).B + AtThis(x, 0).B + AtThis(x + 1, 0).B
					+ AtThis(x - 1, 0 + 1).B + AtThis(x, 0 + 1).B + AtThis(x + 1, 0 + 1).B) / 9;
				array[minusHeight][x].R = ((unsigned long long)AtThis(x - 1, minusHeight - 1).R + AtThis(x, minusHeight - 1).R + AtThis(x + 1, minusHeight - 1).R
					+ AtThis(x - 1, minusHeight).R + AtThis(x, minusHeight).R + AtThis(x + 1, minusHeight).R) / 9;
				array[minusHeight][x].G = ((unsigned long long)AtThis(x - 1, minusHeight - 1).G + AtThis(x, minusHeight - 1).G + AtThis(x + 1, minusHeight - 1).G
					+ AtThis(x - 1, minusHeight).G + AtThis(x, minusHeight).G + AtThis(x + 1, minusHeight).G) / 9;
				array[minusHeight][x].B = ((unsigned long long)AtThis(x - 1, minusHeight - 1).B + AtThis(x, minusHeight - 1).B + AtThis(x + 1, minusHeight - 1).B
					+ AtThis(x - 1, minusHeight).B + AtThis(x, minusHeight).B + AtThis(x + 1, minusHeight).B) / 9;
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
			for (size_t y = 1; y < minusHeight - 1; ++y)
				for (size_t x = 1; x < minusWidth - 1; ++x)
				{
					AtThis(x,y).R = ((unsigned long long)AtArray(x - 1, y - 1).R
						+ AtArray(x, y - 1).R
						+ AtArray(x + 1, y - 1).R
						+ AtArray(x - 1, y).R
						+ AtArray(x, y).R
						+ AtArray(x + 1, y).R
						+ AtArray(x - 1, y + 1).R
						+ AtArray(x, y + 1).R
						+ AtArray(x + 1, y + 1).R) / 9;
					AtThis(x, y).G = ((unsigned long long)AtArray(x - 1, y - 1).G + AtArray(x, y - 1).G + AtArray(x + 1, y - 1).G
						+ AtArray(x - 1, y).G + AtArray(x, y).G + AtArray(x + 1, y).G
						+ AtArray(x - 1, y + 1).G + AtArray(x, y + 1).G + AtArray(x + 1, y + 1).G) / 9;
					AtThis(x, y).B = ((unsigned long long)AtArray(x - 1, y - 1).B + AtArray(x, y - 1).B + AtArray(x + 1, y - 1).B
						+ AtArray(x - 1, y).B + AtArray(x, y).B + AtArray(x + 1, y).B
						+ AtArray(x - 1, y + 1).B + AtArray(x, y + 1).B + AtArray(x + 1, y + 1).B) / 9;
				}
			for (size_t y = 1; y < minusHeight - 1; ++y)
			{
				AtThis(0, y).R = ((unsigned long long)AtArray(0, y - 1).R + AtArray(0 + 1, y - 1).R
					+ AtArray(0, y).R + AtArray(0 + 1, y).R
					+ AtArray(0, y + 1).R + AtArray(0 + 1, y + 1).R) / 9;
				AtThis(0, y).G = ((unsigned long long)AtArray(0, y - 1).G + AtArray(0 + 1, y - 1).G
					+ AtArray(0, y).G + AtArray(0 + 1, y).G
					+ AtArray(0, y + 1).G + AtArray(0 + 1, y + 1).G) / 9;
				AtThis(0, y).B = ((unsigned long long)AtArray(0, y - 1).B + AtArray(0 + 1, y - 1).B
					+ AtArray(0, y).B + AtArray(0 + 1, y).B
					+ AtArray(0, y + 1).B + AtArray(0 + 1, y + 1).B) / 9;
				AtThis(minusWidth, y).R = ((unsigned long long)AtArray(minusWidth - 1, y - 1).R + AtArray(minusWidth, y - 1).R
					+ AtArray(minusWidth - 1, y).R + AtArray(minusWidth, y).R
					+ AtArray(minusWidth - 1, y + 1).R + AtArray(minusWidth, y + 1).R) / 9;
				AtThis(minusWidth, y).G = ((unsigned long long)AtArray(minusWidth - 1, y - 1).G + AtArray(minusWidth, y - 1).G
					+ AtArray(minusWidth - 1, y).G + AtArray(minusWidth, y).G
					+ AtArray(minusWidth - 1, y + 1).G + AtArray(minusWidth, y + 1).G) / 9;
				AtThis(minusWidth, y).B = ((unsigned long long)AtArray(minusWidth - 1, y - 1).B + AtArray(minusWidth, y - 1).B
					+ AtArray(minusWidth - 1, y).B + AtArray(minusWidth, y).B
					+ AtArray(minusWidth - 1, y + 1).B + AtArray(minusWidth, y + 1).B) / 9;
			}
			for (size_t x = 1; x < minusWidth - 1; ++x)
			{
				AtThis(x, 0).R = ((unsigned long long)AtArray(x - 1, 0).R + AtArray(x, 0).R + AtArray(x + 1, 0).R
					+ AtArray(x - 1, 0 + 1).R + AtArray(x, 0 + 1).R + AtArray(x + 1, 0 + 1).R) / 9;
				AtThis(x, 0).G = ((unsigned long long)AtArray(x - 1, 0).G + AtArray(x, 0).G + AtArray(x + 1, 0).G
					+ AtArray(x - 1, 0 + 1).G + AtArray(x, 0 + 1).G + AtArray(x + 1, 0 + 1).G) / 9;
				AtThis(x, 0).B = ((unsigned long long)AtArray(x - 1, 0).B + AtArray(x, 0).B + AtArray(x + 1, 0).B
					+ AtArray(x - 1, 0 + 1).B + AtArray(x, 0 + 1).B + AtArray(x + 1, 0 + 1).B) / 9;
				AtThis(x, minusHeight).R = ((unsigned long long)AtArray(x - 1, minusHeight - 1).R + AtArray(x, minusHeight - 1).R + AtArray(x + 1, minusHeight - 1).R
					+ AtArray(x - 1, minusHeight).R + AtArray(x, minusHeight).R + AtArray(x + 1, minusHeight).R) / 9;
				AtThis(x, minusHeight).G = ((unsigned long long)AtArray(x - 1, minusHeight - 1).G + AtArray(x, minusHeight - 1).G + AtArray(x + 1, minusHeight - 1).G
					+ AtArray(x - 1, minusHeight).G + AtArray(x, minusHeight).G + AtArray(x + 1, minusHeight).G) / 9;
				AtThis(x, minusHeight).B = ((unsigned long long)AtArray(x - 1, minusHeight - 1).B + AtArray(x, minusHeight - 1).B + AtArray(x + 1, minusHeight - 1).B
					+ AtArray(x - 1, minusHeight).B + AtArray(x, minusHeight).B + AtArray(x + 1, minusHeight).B) / 9;
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
		for (size_t y = 0; y < height; ++y)
			for (size_t x = 0; x < width; ++x)
				AtThis(x, y).SetNegative();
	}
	inline static bool isDarkImage(unsigned char* data, const size_t height, const size_t width)
	{
		return GetAverageColour(reinterpret_cast<Pixel*>(data), height, width).brightness() < 127;
	}
	inline static bool isBrightImage(unsigned char* data, const size_t height, const size_t width)
	{
		return GetAverageColour(reinterpret_cast<Pixel*>(data), height, width).brightness() >= 127;
	}
	inline static Figure CatchFigure(unsigned char* data, bool** FlagWereLookedArray, const size_t height, const size_t width, int x, int y)
	{
		auto AtData = std::bind(atPoint, reinterpret_cast<Pixel*>(data), width, std::placeholders::_1);
		std::queue<Point> ToVisit;
		std::list<Point> ToRemember;

		ToVisit.push(Point(x,y));

		while (!ToVisit.empty())
		{
			auto target = ToVisit.front();
							ToVisit.pop();

			if (target.x > -1)
			{
				if (target.y > -1)
				{
					if (Pixel::colorDifference(AtData(target.UpLeft()), AtData(target))
						< Settings::BorderSeparationColorDifference
						&& !FlagWereLookedArray[y - 1][x - 1])
					{
						ToVisit.push(target.UpLeft());
						ToRemember.push_back(target.UpLeft());
						FlagWereLookedArray[y - 1][x - 1] = true;
					}
				}
				///
				{	
					if (Pixel::colorDifference(AtData(target.Left()), AtData(target))
						< Settings::BorderSeparationColorDifference
						&& !FlagWereLookedArray[y][x - 1])
					{
						ToVisit.push(target.Left());
						ToRemember.push_back(target.Left());
						FlagWereLookedArray[y][x - 1] = true;
					}
				}
				///
				if (target.y < (height - 1))
				{
					if (Pixel::colorDifference(AtData(target.DownLeft()), AtData(target))
						< Settings::BorderSeparationColorDifference
						&& !FlagWereLookedArray[y + 1][x - 1])
					{
						ToVisit.push(target.DownLeft());
						ToRemember.push_back(target.DownLeft());
						FlagWereLookedArray[y + 1][x - 1] = true;
					}
				}
			}
			///
			{
				if (target.y > -1)
				{
					if (Pixel::colorDifference(AtData(target.Up()), AtData(target))
						< Settings::BorderSeparationColorDifference
						&& !FlagWereLookedArray[y - 1][x])
					{
						ToVisit.push(target.Up());
						ToRemember.push_back(target.Up());
						FlagWereLookedArray[y - 1][x] = true;
					}
				}
				///
				if (target.y < (height - 1))
				{
					if (Pixel::colorDifference(AtData(target.Down()), AtData(target))
						< Settings::BorderSeparationColorDifference
						&& !FlagWereLookedArray[y + 1][x])
					{
						ToVisit.push(target.Down());
						ToRemember.push_back(target.Down());
						FlagWereLookedArray[y + 1][x] = true;
					}
				}
			}
			///
			if (target.x < (width - 1))
			{
				if (target.y > -1)
				{
					if (Pixel::colorDifference(AtData(target.UpRight()), AtData(target))
						< Settings::BorderSeparationColorDifference
						&& !FlagWereLookedArray[y - 1][x + 1])
					{
						ToVisit.push(target.UpRight());
						ToRemember.push_back(target.UpRight());
						FlagWereLookedArray[y - 1][x + 1] = true;
					}
				}
				///
				if (Pixel::colorDifference(AtData(target.Right()), AtData(target))
					< Settings::BorderSeparationColorDifference
					&& !FlagWereLookedArray[y][x + 1])
				{
					ToVisit.push(target.Right());
					ToRemember.push_back(target.Right());
					FlagWereLookedArray[y][x + 1] = true;
				}
				///
				if (target.y < (height - 1))
				{
					if (Pixel::colorDifference(AtData(target.DownRight()), AtData(target))
						< Settings::BorderSeparationColorDifference
						&& !FlagWereLookedArray[y + 1][x + 1])
					{
						ToVisit.push(target.DownRight());
						ToRemember.push_back(target.DownRight());
						FlagWereLookedArray[y + 1][x + 1] = true;
					}
				}
			}
		}

		size_t minX = x;
		size_t maxX = x;
		size_t minY = y;
		size_t maxY = y;

		for (auto itr = ToRemember.begin(); itr != ToRemember.end(); ++itr)
		{
			if (itr->x < minX)
				minX = itr->x;
			else
				if (itr->x > maxX)
					maxX = itr->x;

			if (itr->y < minY)
				minY = itr->y;
			else
				if (itr->y > maxY)
					maxY = itr->y;
		}

		size_t width = maxX - minX + 1;
		size_t height = maxY - minY + 1;

		auto size = width * height;
		Pixel* SymbolImage = new Pixel[width * height];
		for (int i = 0; i < size; ++i)
			SymbolImage[i] = Color::White;

		auto AtImage = [&SymbolImage, width](Point a)->Pixel& 
					{return SymbolImage[a.x + a.y * width]; };
		for (auto itr = ToRemember.begin(); itr != ToRemember.end(); ++itr)
			AtImage(*itr) = Color::Black;



	}
};

