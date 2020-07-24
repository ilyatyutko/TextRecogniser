#pragma once
#include <vector>
#include <IL/il.h>
#include <IL/ilu.h>
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

		auto atPosition = [DataPtr, width](size_t x, size_t y)->Pixel& {return DataPtr[x + y * width]; };
		for (size_t y = 0; y < Settings::ImageRecognitionHeight; ++y)
			for (size_t x = 0; x < Settings::ImageRecognitionWidth; ++x)
			{
				if (atPosition(x, y).brightness() > AverageBrightness)
					result.push_back(false);
				else
					result.push_back(true);
			}
		return result;
	}

public:
	size_t x;
	size_t y;
	char value;

	Symbol(Pixel* DataPtr, size_t width, size_t height, size_t _x, size_t _y)
		: x(_x)
		, y(_y)
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
		ilDeleteImages(1, &id);
	}

};
