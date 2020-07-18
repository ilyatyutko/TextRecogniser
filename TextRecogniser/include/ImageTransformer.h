#pragma once
#include <cmath>
#include <vector>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include "Settings.h"

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
			return std::round(((double)R + (double)G + (double)B) / 3 * (double)T / 256);
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
	ILuint ID;
	Pixel* data;
	inline Pixel& at(size_t y, size_t x) const
	{
		return *(data + y * Settings::ImageRecognitionWidth + x);
	}
	Pixel averageColour() const
	{
		unsigned long long R_sum = 0;
		unsigned long long G_sum = 0;
		unsigned long long B_sum = 0;

		Pixel tmp;

		for(int y = 0; y < Settings::ImageRecognitionHeight; ++y)
			for (int x = 0; x < Settings::ImageRecognitionWidth; ++x)
			{
				tmp = this->at(y,x);
				R_sum += tmp.R;
				G_sum += tmp.G;
				B_sum += tmp.B;
			}
		return Pixel(std::floor(R_sum / ((unsigned long long)Settings::ImageRecognitionHeight * Settings::ImageRecognitionWidth)),
					 std::floor(G_sum / ((unsigned long long)Settings::ImageRecognitionHeight * Settings::ImageRecognitionWidth)),
					 std::floor(B_sum / ((unsigned long long)Settings::ImageRecognitionHeight * Settings::ImageRecognitionWidth)));
	}
	void SimplifyTo_Black_And_White_Form()
	{
		volume AverageBrightness = averageColour().brightness();
		for (int y = 0; y < Settings::ImageRecognitionHeight; ++y)
			for (int x = 0; x < Settings::ImageRecognitionWidth; ++x)
			{
				if (this->at(y, x).brightness() > AverageBrightness)
					this->at(y, x) = White;
				else
					this->at(y, x) = Black;
			}
	}
	std::vector<bool> SimplifyTo_Binary_Form() const
	{
		std::vector<bool> result;
		result.reserve(Settings::ImageRecognitionHeight * Settings::ImageRecognitionWidth);

		volume AverageBrightness = averageColour().brightness();
		for (int y = 0; y < Settings::ImageRecognitionHeight; ++y)
			for (int x = 0; x < Settings::ImageRecognitionWidth; ++x)
			{
				if (this->at(y, x).brightness() > AverageBrightness)
					result.push_back(false);
				else
					result.push_back(true);
			}
		return result;
	}
	ImageTransformer(const std::string& FileName)
	{
		ilInit();
		iluInit();

		ILuint	id;
		ilGenImages(1, &id);
		ilBindImage(id);
		ilLoad(IL_PNG, reinterpret_cast<wchar_t*>(const_cast<char*>(FileName.c_str())));

		bool ImageLoadException = ilGetError();
		if (ImageLoadException)
			throw std::exception("Image Cant be Loaded");

		iluContrast(Settings::ContrastFilterPower);
		iluSharpen(Settings::SharpeningLevel, Settings::SharpeningIterationsCount);
		iluScale(Settings::ImageRecognitionWidth, Settings::ImageRecognitionHeight, 8);

		ID = id;
		data =  reinterpret_cast<Pixel*>(ilGetData());
	}
	ImageTransformer() = delete;
	~ImageTransformer()
	{
		ilDeleteImages(1, &ID);
	}
};

