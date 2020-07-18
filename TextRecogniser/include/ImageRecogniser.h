#pragma once
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include <list>
#include <string>
#include <iostream>
#include "ImageTransformer.h"
#include "Hopfild.h"

using FileName = std::string;
namespace 
{
	const double ContrastFilterPower = 5;
	const double SharpeningLevel = 700;
	const ILint SharpeningIterationsCount = 5;
}

class ImageRecogniser
{
private:
	Hopfild<std::string> NeuralNet;
	size_t width = 25;
	size_t height = 25;
	size_t depth = 8;
public:
	ImageRecogniser(const std::list<std::pair<FileName, std::string>>& FileList)
	{
		ilInit();
		iluInit();

		if (FileList.size() == 0)
			throw std::exception("Empty Input List");

		std::list<std::pair<std::vector<bool>, std::string>> Images;

		for (auto& file : FileList)
		{
			ILuint	id;
			ilGenImages(1, &id);
			ilBindImage(id);
			ilLoad(IL_PNG, reinterpret_cast<wchar_t*>(const_cast<char*>(file.first.c_str())));

			bool ImageLoadException = ilGetError();
			if (ImageLoadException)
				throw std::exception("Image Cant be Loaded");
			
			iluContrast(ContrastFilterPower);
			iluSharpen(SharpeningLevel, SharpeningIterationsCount);
			iluScale(width, height, 2);

			ImageTransformer picture(ilGetData()
									,height
									,width);
			Images.push_back( 
				std::make_pair(picture.SimplifyTo_Binary_Form()
							   , file.second));
			ilDeleteImages(1, &id);
		}
		NeuralNet = Hopfild<std::string>(Images);
	}

	std::string RecognizeImage(const FileName& file)
	{
		ILuint	id;
		ilGenImages(1, &id);
		ilBindImage(id);
		ilLoad(IL_PNG, reinterpret_cast<wchar_t*>(const_cast<char*>(file.c_str())));

		bool ImageLoadException = ilGetError();
		if (ImageLoadException)
			throw std::exception("Image Cant be Loaded");

		iluContrast(ContrastFilterPower);
		iluSharpen(SharpeningLevel, SharpeningIterationsCount);
		iluScale(width, height, 8);

		ImageTransformer picture(ilGetData()
			, height
			, width);

		auto answer = NeuralNet.recognition(picture.SimplifyTo_Binary_Form());
		ilDeleteImages(1, &id);
		return answer;
	}
};

