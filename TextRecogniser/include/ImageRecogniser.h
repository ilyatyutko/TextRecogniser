#pragma once
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include <list>
#include <string>
#include <iostream>
#include "ImageTransformer.h"
#include "Hopfild.h"
#include "Settings.h"

using FileName = std::string;
namespace 
{
	
}

class ImageRecogniser
{
private:
	Hopfild<int> NeuralNet;
public:
	ImageRecogniser(const std::list<std::pair<FileName, int>>& FileList)
	{
		if (FileList.size() == 0)
			throw std::exception("Empty Input List");

		std::list<std::pair<std::vector<bool>, int>> Images;

		for (auto& file : FileList)
		{
			ImageTransformer picture(file.first);
			Images.push_back( 
				std::make_pair(picture.Get_Binary_Form()
							   , file.second));
		}

		//there 10 is element, which means impossibility to recognise
		NeuralNet = Hopfild<int>(Images, 10); 
	}
	int RecognizeImage(const ImageTransformer& BinaryImage) const
	{
		return NeuralNet.recognition(BinaryImage.Get_Binary_Form());
	}
	int RecognizeImage(const std::vector<bool>& VectorizedImage) const
	{
		if (VectorizedImage.size() != 
			Settings::ImageRecognitionWidth *  Settings::ImageRecognitionHeight)
			throw std::exception("input VectorImage has wrong size");
			return NeuralNet.recognition(VectorizedImage);
	}
};

