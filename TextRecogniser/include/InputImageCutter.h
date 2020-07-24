#pragma once
#include <list>
#include <string>
#include "ImageTransformer.h"
#include "Filter.h"
#include "Settings.h"

static class InputImageCutter
{
public:
	std::list<ImageTransformer> CutImage(const std::string& FileName)
	{
		if (!Settings::ILWasINIT)
		{
			ilInit();
			iluInit();
			ilEnable(IL_ORIGIN_SET);
			Settings::ILWasINIT = true;
		}
			ILuint ID;
			ilGenImages(1, &ID);
			ilBindImage(ID);
			ilLoad(IL_PNG, reinterpret_cast<wchar_t*>(const_cast<char*>(FileName.c_str())));

			bool ImageLoadException = ilGetError();
			if (ImageLoadException)
				throw std::exception(std::string("Image Cant be Loaded: " + FileName).c_str());

			auto Height = ilGetInteger(IL_IMAGE_HEIGHT);
			auto Width  = ilGetInteger(IL_IMAGE_WIDTH);
			auto Data   = ilGetData();

			for(int i =0; i < Settings::FiltrationLevel; ++i)
				Filter::AverageFilter(Data
					, Height
					, Width);

			Filter::TransformToBlackAndWhiteForm(Data
				, Height
				, Width);

			if (Filter::isDarkImage(Data
				, Height
				, Width))
				Filter::Negative(Data
					, Height
					, Width);


			bool** FlagWereLookedArray = new bool* [Height];
			for (int i = 0; i < Height; ++i)
				FlagWereLookedArray[i] = new bool[Width];

			for (int y = 0; y < Height; ++y)
				for (int x = 0; x < Width; ++x)
					FlagWereLookedArray[y][x] = false;





			ilDeleteImages(1, &ID);
	}
};

