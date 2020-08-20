#pragma once
#include <iostream>
#include <list>
#include <string>
#include <functional>
#include <queue>
#include "Filter.h"
#include "Pixel.h"
#include "Figure.h"
#include "Settings.h"

static class InputImageCutter
{
private:
	inline static Figure CatchFigure(const unsigned char const* data, bool** FlagWereLookedArray, const size_t RealHeight, const size_t RealWidth, int offset_x, int offset_y)
	{
		auto AtData = std::bind(Filter::atPoint, reinterpret_cast<const Pixel*>(data), RealWidth, std::placeholders::_1);
		std::queue<Point> ToVisit;
		std::list<Point> ToRemember;

		ToVisit.push(Point(offset_x, offset_y));

		while (!ToVisit.empty())
		{
			auto target = ToVisit.front();
			ToVisit.pop();

			if (target.offset_x > 0)
			{
				if (target.offset_y > 0)
				{
					if (Pixel::colorDifference(AtData(target.UpLeft()), AtData(target))
						< Settings::BorderSeparationColorDifference
						&& !FlagWereLookedArray[target.offset_y - 1][target.offset_x - 1])
					{
						ToVisit.push(target.UpLeft());
						ToRemember.push_back(target.UpLeft());
						FlagWereLookedArray[target.offset_y - 1][target.offset_x - 1] = true;
					}
				}
				///
				{
					if (Pixel::colorDifference(AtData(target.Left()), AtData(target))
						< Settings::BorderSeparationColorDifference
						&& !FlagWereLookedArray[target.offset_y][target.offset_x - 1])
					{
						ToVisit.push(target.Left());
						ToRemember.push_back(target.Left());
						FlagWereLookedArray[target.offset_y][target.offset_x - 1] = true;
					}
				}
				///
				if (target.offset_y < (RealHeight - 1))
				{
					if (Pixel::colorDifference(AtData(target.DownLeft()), AtData(target))
						< Settings::BorderSeparationColorDifference
						&& !FlagWereLookedArray[target.offset_y + 1][target.offset_x - 1])
					{
						ToVisit.push(target.DownLeft());
						ToRemember.push_back(target.DownLeft());
						FlagWereLookedArray[target.offset_y + 1][target.offset_x - 1] = true;
					}
				}
			}
			///
			{
				if (target.offset_y > 0)
				{
					if (Pixel::colorDifference(AtData(target.Up()), AtData(target))
						< Settings::BorderSeparationColorDifference
						&& !FlagWereLookedArray[target.offset_y - 1][target.offset_x])
					{
						ToVisit.push(target.Up());
						ToRemember.push_back(target.Up());
						FlagWereLookedArray[target.offset_y - 1][target.offset_x] = true;
					}
				}
				///
				if (target.offset_y < (RealHeight - 1))
				{
					if (Pixel::colorDifference(AtData(target.Down()), AtData(target))
						< Settings::BorderSeparationColorDifference
						&& !FlagWereLookedArray[target.offset_y + 1][target.offset_x])
					{
						ToVisit.push(target.Down());
						ToRemember.push_back(target.Down());
						FlagWereLookedArray[target.offset_y + 1][target.offset_x] = true;
					}
				}
			}
			///
			if (target.offset_x < (RealWidth - 1))
			{
				if (target.offset_y > 0)
				{
					if (Pixel::colorDifference(AtData(target.UpRight()), AtData(target))
						< Settings::BorderSeparationColorDifference
						&& !FlagWereLookedArray[target.offset_y - 1][target.offset_x + 1])
					{
						ToVisit.push(target.UpRight());
						ToRemember.push_back(target.UpRight());
						FlagWereLookedArray[target.offset_y - 1][target.offset_x + 1] = true;
					}
				}
				///
				if (Pixel::colorDifference(AtData(target.Right()), AtData(target))
					< Settings::BorderSeparationColorDifference
					&& !FlagWereLookedArray[target.offset_y][target.offset_x + 1])
				{
					ToVisit.push(target.Right());
					ToRemember.push_back(target.Right());
					FlagWereLookedArray[target.offset_y][target.offset_x + 1] = true;
				}
				///
				if (target.offset_y < (RealHeight - 1))
				{
					if (Pixel::colorDifference(AtData(target.DownRight()), AtData(target))
						< Settings::BorderSeparationColorDifference
						&& !FlagWereLookedArray[target.offset_y + 1][target.offset_x + 1])
					{
						ToVisit.push(target.DownRight());
						ToRemember.push_back(target.DownRight());
						FlagWereLookedArray[target.offset_y + 1][target.offset_x + 1] = true;
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
		Pixel* SymbolImage_data = new Pixel[size];
		for (int i = 0; i < size; ++i)
			SymbolImage_data[i] = Colour::Transparent;

		auto AtImage = [&SymbolImage_data, width_sym](Point a)->Pixel&
		{return SymbolImage_data[a.offset_x + a.offset_y * width_sym]; };

		Point offset(minX, minY);
		for (auto itr = ToRemember.begin(); itr != ToRemember.end(); ++itr)
			AtImage(*itr - offset) = AtData(*itr);

		return Figure(SymbolImage_data, width_sym, height_sym, minX, minY);
	}
public:
	static std::list<Figure> CutImage(const std::string& FileName)
	{
		Settings::ililuINIT();
		ILuint ID;
		ilGenImages(1, &ID);
		ilBindImage(ID);
		ilLoad(IL_PNG, reinterpret_cast<wchar_t*>(const_cast<char*>(FileName.c_str())));

		bool ImageLoadException = ilGetError();
		if (ImageLoadException)
			throw std::exception(std::string("Image Cant be Loaded: " + FileName).c_str());
		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		auto Height = ilGetInteger(IL_IMAGE_HEIGHT);
		auto Width  = ilGetInteger(IL_IMAGE_WIDTH);
		auto Data   = ilGetData();

		for(int i =0; i < Settings::FiltrationLevel; ++i)
			Filter::AverageFilter(Data
				, Height
				, Width);
		Filter::TransformToBlackAndWhiteForm(Data, Height, Width);
		if (Filter::isDarkImage(Data, Height, Width))
			iluNegative();
		if (Settings::inverseOverY)
			iluFlipImage();
		if (Settings::inverseOverX)
			iluMirror();

		Data = ilGetData();
		bool** FlagWereLookedArray = new bool* [Height];
		for (int i = 0; i < Height; ++i)
			FlagWereLookedArray[i] = new bool[Width];

		for (int offset_y = 0; offset_y < Height; ++offset_y)
			for (int offset_x = 0; offset_x < Width; ++offset_x)
				FlagWereLookedArray[offset_y][offset_x] = false;
	
		std::list<Figure> SymbolList;
		auto AtPosition = [Data, Width](size_t x, size_t y) {return *(reinterpret_cast<Pixel*>(Data) + y * Width + x); };
		auto LocalCatchFigure = std::bind(InputImageCutter::CatchFigure, Data, FlagWereLookedArray, Height, Width, std::placeholders::_1, std::placeholders::_2);
		for (int offset_y = 0; offset_y < Height; ++offset_y)
			for (int offset_x = 0; offset_x < Width; ++offset_x)
				if (FlagWereLookedArray[offset_y][offset_x] == false
					&& AtPosition(offset_x, offset_y) == Colour::Black)
				{
					SymbolList.push_back(LocalCatchFigure(offset_x, offset_y));
				}


		for (int i = 0; i < Height; ++i)
			delete[] FlagWereLookedArray[i];
		delete[] FlagWereLookedArray;
		ilDeleteImages(1, &ID);
		return SymbolList;
	}
};

