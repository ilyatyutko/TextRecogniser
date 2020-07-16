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

class ImageRecogniser
{
private:
	Hopfild<std::string> NeuralNet;
	size_t width = 25;
	size_t height = 25;
	size_t depth = 8;

	const double ContrastFilterPower = 5;
	const double SharpeningLevel = 70;
	const double SharpeningIterationsCount = 5;
public:
	ImageRecogniser(std::list<std::pair<FileName, std::string>> FileList)
	{
		ilInit();
		iluInit();

		if (FileList.size() == 0)
			throw std::exception("Empty Input List");

		std::list<std::pair<std::vector<bool>, std::string>> Images;

		bool firstImage = true;
		for (auto& file : FileList)
		{
			ILuint	id;
			ilGenImages(1, &id);
			ilBindImage(id);

			auto fileNm = file.first.c_str();
			ilLoad(IL_PNG, reinterpret_cast<wchar_t*>(const_cast<char*>(file.first.c_str())));

			bool ImageLoadException = ilGetError();
			if (ImageLoadException)
				throw std::exception("Image Cant be Loaded");
			
			iluContrast(ContrastFilterPower);
			iluSharpen(SharpeningLevel, SharpeningIterationsCount);
			iluScale(width, height, 2);

			int height = ilGetInteger(IL_IMAGE_HEIGHT);
			int width = ilGetInteger(IL_IMAGE_WIDTH);

			ImageTransformer picture(ilGetData()
									,height
									,width);
			picture.SimplifyTo_Black_And_White_Form();

			auto vec = picture.SimplifyTo_Binary_Form();
				/*for (int y = 0; y < height; ++y)
				{
					for (int x = 0; x < width; ++x)

						std::cout << vec[width * y + x];
					std::cout << std::endl;
				}
				std::cout << std::endl;*/
			Images.push_back( 
				std::make_pair(picture.SimplifyTo_Binary_Form()
							   , file.second));
			
			ilDeleteImages(1, &id);
		}

		NeuralNet = Hopfild<std::string>(Images);
	}

	std::string RecognizeImage(FileName file)
	{
		ILuint	id;
		ilGenImages(1, &id);
		ilBindImage(id);
		ilLoad(IL_PNG, reinterpret_cast<wchar_t*>(const_cast<char*>(file.c_str())));

		bool ImageLoadException = ilGetError();
		if (ImageLoadException)
			throw std::exception("Image Cant be Loaded");
		//if (width != ilGetInteger(IL_IMAGE_WIDTH)
		//	|| height != ilGetInteger(IL_IMAGE_HEIGHT))

		
		iluContrast(ContrastFilterPower);
		iluSharpen(SharpeningLevel, SharpeningIterationsCount);
		iluScale(width, height, 8);

		ImageTransformer picture(ilGetData()
			, ilGetInteger(IL_IMAGE_HEIGHT)
			, ilGetInteger(IL_IMAGE_WIDTH));
		picture.SimplifyTo_Black_And_White_Form();

		auto vec = picture.SimplifyTo_Binary_Form();

		/*std::cout << std::endl;
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)

				std::cout << (vec[width * y + x] == 1) ? 1 : 0;
			std::cout << std::endl;
		}*/
		auto answer = NeuralNet.recognition(vec);
		ilDeleteImages(1, &id);
		///////////////////////
		return answer;
	}
};

