#pragma once
#include <cmath>
#include <vector>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include "Settings.h"
#include "Pixel.h"


class ImageTransformer
{
public:
	ILuint ID;
	Pixel* data;
	inline Pixel& atPosition(size_t offset_y, size_t offset_x) const
	{
		return *(data + offset_y * Settings::ImageRecognitionWidth + offset_x);
	}
	Pixel averageColour() const
	{
		unsigned long long R_sum = 0;
		unsigned long long G_sum = 0;
		unsigned long long B_sum = 0;

		Pixel tmp;

		for(int offset_y = 0; offset_y < Settings::ImageRecognitionHeight; ++offset_y)
			for (int offset_x = 0; offset_x < Settings::ImageRecognitionWidth; ++offset_x)
			{
				tmp = this->atPosition(offset_y,offset_x);
				R_sum += tmp.R;
				G_sum += tmp.G;
				B_sum += tmp.B;
			}
		return Pixel(std::floor(R_sum / ((unsigned long long)Settings::ImageRecognitionHeight * Settings::ImageRecognitionWidth)),
					 std::floor(G_sum / ((unsigned long long)Settings::ImageRecognitionHeight * Settings::ImageRecognitionWidth)),
					 std::floor(B_sum / ((unsigned long long)Settings::ImageRecognitionHeight * Settings::ImageRecognitionWidth)));
	}
	
	std::vector<bool> Get_Binary_Form() const
	{
		std::vector<bool> result;
		result.reserve(Settings::ImageRecognitionHeight * Settings::ImageRecognitionWidth);

		volume AverageBrightness = averageColour().brightness();
		for (int offset_y = 0; offset_y < Settings::ImageRecognitionHeight; ++offset_y)
			for (int offset_x = 0; offset_x < Settings::ImageRecognitionWidth; ++offset_x)
			{
				if (this->atPosition(offset_y, offset_x).brightness() > AverageBrightness)
					result.push_back(false);
				else
					result.push_back(true);
			}
		return result;
	}
	ImageTransformer(const std::string& FileName)
	{
		//ilInit();
		//iluInit();
		ilGenImages(1, &ID);
		ilBindImage(ID);
		ilLoad(IL_PNG, reinterpret_cast<wchar_t*>(const_cast<char*>(FileName.c_str())));

		bool ImageLoadException = ilGetError();
		if (ImageLoadException)
			throw std::exception(std::string("Image Cant be Loaded: " + FileName).c_str());

		iluContrast(Settings::ContrastFilterPower);
		iluSharpen(Settings::SharpeningLevel, Settings::SharpeningIterationsCount);
		iluScale(Settings::ImageRecognitionWidth, Settings::ImageRecognitionHeight, 8);

		data =  reinterpret_cast<Pixel*>(ilGetData());
	}
	ImageTransformer(ImageTransformer&& source)
		:ID(source.ID)
		,data(source.data)
	{
	}
	ImageTransformer() = delete;
	~ImageTransformer()
	{
		ilDeleteImages(1, &ID);
	}
};

