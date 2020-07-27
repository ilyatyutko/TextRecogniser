#pragma once
#include <vector>
#include <IL/il.h>
#include <IL/ilu.h>
#include <iostream>
#include "Pixel.h"
#include "Settings.h"
#include "Filter.h"

class Symbol
{
private:
	ILuint id;

	std::vector<bool> Get_Binary_Form(Pixel* DataPtr, size_t width, size_t height) const
	{
		std::vector<bool> result;
		result.reserve(Settings::ImageRecognitionHeight * Settings::ImageRecognitionWidth);

		volume AverageBrightness = Filter::GetAverageColour(DataPtr, height, width).brightness();

		auto atPosition = [DataPtr, width](size_t offset_x, size_t offset_y)->Pixel& {return DataPtr[offset_x + offset_y * width]; };
		for (size_t offset_y = 0; offset_y < Settings::ImageRecognitionHeight; ++offset_y)
			for (size_t offset_x = 0; offset_x < Settings::ImageRecognitionWidth; ++offset_x)
			{
				if (atPosition(offset_x, offset_y).brightness() > AverageBrightness)
					result.push_back(false);
				else
					result.push_back(true);
			}
		return result;
	}

public:
	size_t offset_x;
	size_t offset_y;

	Symbol(Pixel* DataPtr, size_t width, size_t height, size_t _offset_x, size_t _offset_y)
		: offset_x(_offset_x)
		, offset_y(_offset_y)
	{
		if (!Settings::ILWasINIT)
		{
			ilInit();
			iluInit();
			ilEnable(IL_ORIGIN_SET);
			Settings::ILWasINIT = true;
		}

		ilGenImages(1, &id);
		ilTexImage(width, height, 8, 3, IL_RGBA, IL_UNSIGNED_BYTE, DataPtr);

		iluScale(Settings::ImageRecognitionWidth, Settings::ImageRecognitionHeight, 8);

		Filter::TransformToBlackAndWhiteForm(reinterpret_cast<unsigned char*> (DataPtr), height, width);
		if (Filter::isDarkImage(reinterpret_cast<unsigned char*> (DataPtr), height, width))
			Filter::Negative(reinterpret_cast<unsigned char*> (DataPtr), height, width);


		/////////



		/////////
	}
	~Symbol()
	{
		ilDeleteImages(1, &id);
	}
	friend std::ostream& operator<< (std::ostream& out, const Symbol& source);
};

std::ostream& operator<< (std::ostream& out, const Symbol& source)
{
	source.id;
	if (!Settings::ILWasINIT)
	{
		ilInit();
		iluInit();
		ilEnable(IL_ORIGIN_SET);
		Settings::ILWasINIT = true;
	}
	ilBindImage(source.id);
	size_t width = ilGetInteger(IL_IMAGE_WIDTH);
	size_t height = ilGetInteger(IL_IMAGE_HEIGHT);
	ILubyte* data = ilGetData();
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
			out << (Filter::atPosition(reinterpret_cast<Pixel*>(data), width, x, y).isBlack() ? '#' : ' ');
		out << std::endl;
	}

	return out;
}